#include<SoftwareSerial.h>

#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>

#define APPID   "iLight"
#define KEY     "Q3XUy22q0cgxB9R"
#define SECRET  "LgJmdco46P1GzPEslEhJBQ7il"

#define ALIAS   "iLight_NodeMCU"
#define TargetWeb "HTML_web_test"

SoftwareSerial STMSerial(5, 4); // D1, D2

ESP8266WiFiMulti wifiMulti;

WiFiClient client;
MicroGear microgear(client);

StaticJsonBuffer<256> jsonBuffer;

int test_count;

void addWiFi()
{
  wifiMulti.addAP("Aphires", "AllHearsMe");
  wifiMulti.addAP("yong", "bcd28c3d35ff");
//  wifiMulti.addAP("ssid", "password");
//  wifiMulti.addAP("ssid", "password");
//  wifiMulti.addAP("ssid", "password");
}

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
  Serial.print("Message from NETPIE: ");
  msg[msglen] = '\0';
  Serial.println((char *) msg);
//  Serial.printf("[%s]\n", msg);
//  STMSerial.print('[');
//  STMSerial.print((char *) msg);
//  STMSerial.print(']');
//  STMSerial.printf("[%s]", msg);
//  STMSerial.printf("%s\r", msg);
  
  JsonObject& root = jsonBuffer.parseObject((char *) msg);
  int distance = root["distance"];
  int ldr = root["ldr"];
  int sw = root["switch"];
  
//  STMSerial.print('[');
  STMSerial.print(distance); STMSerial.print(';');
  STMSerial.print(ldr); STMSerial.print(';');
  STMSerial.print(sw); STMSerial.print(';');
  STMSerial.print('\r');
}


void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
  Serial.println("Connected to NETPIE.");
  microgear.setAlias(ALIAS);
}

void ensureWiFi()
{
  if (wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print("Looking for WiFi");
    while(wifiMulti.run() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(250);
    }
    Serial.println();
    Serial.print("Connected to: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void setup() 
{
   /* Event listener */
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);
  
  Serial.begin(9600);
  Serial.println("Starting...");
  
  STMSerial.begin(9600);

  addWiFi();
  ensureWiFi();
  
  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);
}

void loop() 
{
  ensureWiFi();
  if (microgear.connected())
  {
    microgear.loop();
//    Serial.println("connected");
    char msg[128];
    int i = 0;
    while(STMSerial.available() > 0)
    {
      msg[i++] = STMSerial.read();
      delay(1);
    }
    msg[i] = '\0';
    if(i > 0)
    {
      Serial.print("Message from STM32: ");    
      Serial.println(msg);

      JsonObject& root = jsonBuffer.createObject();
      JsonArray& lights = root.createNestedArray("lights");
      int j;
      for(j=0; j<6; j++) lights.add((int) (msg[i] - '0'));
      root.printTo(msg, 128);
      
      microgear.chat(TargetWeb, msg);
    }
  }
  else 
  {
    Serial.println("Reconnecting to NETPIE...");
    microgear.connect(APPID);
  }
  delay(1000);
}
