//import
var express = require('express')
var app = express()
var ejs = require('ejs')
var mysql = require('mysql')
var db = { host: '35.227.55.154', database: 'lab', user: 'test', password: 'lab' }
var body = require('body-parser').urlencoded({ extended: true })
var pool = mysql.createPool(db)
var cookie = require('cookie-parser')()
var fs = require('fs')

//public var
var dataUser = { user: 'No data', id: 0 }

app.engine('html', ejs.renderFile)
app.listen(2000)
app.get('/login', showhome)
app.post('/login', body, checkLogIn2)
app.get('/check', check)
app.get('/invalidpw', showInvalidpw)
app.get('/profile', showProfile)
app.get('/picture/:image',showphoto)

app.use(errorfunc)


function showhome(req, res) {
    res.render('home.html')
}
/*
function checkLogIn(req,res){
    console.log('pass')
    console.log(req.body.user + req.body.password )
    pool.query("select * from test where user = ? and password =?",
    [req.body.user, req.body.password],
        (error,data)=>{
            console.log(data)
            
            if(data.length == 1){
                dataUser = data[0].user
                console.log('pass')
                res.redirect('/profile')
            }else{
                console.log('fail')
                res.redirect('/invalidpw')

            }
            
        })
}*/

function checkLogIn2(req, res) {
    pool.query("select * from test3 where user = ? and password = sha2(?,256)",
        [req.body.user, req.body.password],
        (error, data) => {
            console.log(data)

            if (data.length == 1) {
                dataUser = data[0]
                console.log('pass')
                res.redirect('/profile')
            } else {
                console.log('fail')
                res.redirect('/invalidpw')

            }

        })
}




function check(req, res) {
    pool.query('select * from test where user= "yong" and password = "1234"',
        (error, data) => {
            res.send(data)
        })
}
function showProfile(req, res) {
    res.render('profile.html', { user: dataUser.user, id: dataUser.id })
}
function goto(req, res) {
    res.redirect('/login')

}
function errorfunc(req, res) {
    res.status(404).render('error.html')
}
function showInvalidpw(req, res) {
    res.render('invalidpw.html')

}

function showphoto(req,res){
    var name = req.params.image
    var fileToLoad = fs.readFileSync('views/picture/'+name);
    res.writeHead(200, {'Content-Type':  'image/jpg'});
    res.end(fileToLoad, 'binary');

}
