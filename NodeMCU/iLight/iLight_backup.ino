//#include<SoftwareSerial.h>
//
//#include <MicroGear.h>
//#include <ESP8266WiFi.h>
//
//#define APPID   "iLight"
//#define KEY     "Q3XUy22q0cgxB9R"
//#define SECRET  "LgJmdco46P1GzPEslEhJBQ7il"
//
//const char* ssid     = "Aphires";
//const char* password = "AllHearsMe";
//
//#define ALIAS   "iLight_NodeMCU"
//#define TargetWeb "HTML_web_test"
//
//SoftwareSerial STMSerial(5, 4); // D1, D2
//
//WiFiClient client;
//MicroGear microgear(client);
//
//int test_count;
//
//void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
//{
//  Serial.print("Incoming message --> ");
//  msg[msglen] = '\0';
//  Serial.println((char *) msg);
//  STMSerial.print('[');
//  STMSerial.print((char *) msg);
//  STMSerial.print(']');
//}
//
//
//void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
//{
//  Serial.println("Connected to NETPIE...");
//  microgear.setAlias(ALIAS);
//}
//
//void setup() 
//{
//   /* Event listener */
//  microgear.on(MESSAGE, onMsghandler);
//  microgear.on(CONNECTED, onConnected);
//  
//  Serial.begin(9600);
//  Serial.println("Starting...");
//  
//  STMSerial.begin(9600);
//  
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) 
//  {
//    delay(250);
//    Serial.print(".");
//  }
//  
//  Serial.print("Connected to WiFi: ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//  
//  microgear.init(KEY,SECRET,ALIAS);
//  microgear.connect(APPID);
//}
//
//void loop() 
//{
//  if (microgear.connected())
//  {
//    microgear.loop();
////    Serial.println("connected");
//    char msg[128];
//    int i = 0;
//    while(STMSerial.available() > 0)
//    {
//      msg[i++] = STMSerial.read();
//      delay(1);
//    }
//    msg[i] = '\0';
//    if(i > 0)
//    {
//      Serial.print("Message received: ");    
//      Serial.println(msg);
//      microgear.chat(TargetWeb, msg);
//    }
//  }
//  else 
//  {
//    Serial.println("connection lost, reconnect...");
//    microgear.connect(APPID);
//  }
//  delay(1000);
//}
