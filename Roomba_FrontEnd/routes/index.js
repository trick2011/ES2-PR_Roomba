var express = require('express');
var router = express.Router();
var cookieParser = require('cookie-parser');

// body should

router.get('/roomba_info',function(req, res){
	res.render('roomba_info.ejs',{body: 'some kind of body body', title: 'Roomba\'s info', Language: req.cookies.LanguageCookie}); 
});

router.get('/project_info',function(req, res){
	res.render('roomba_project_info.ejs',{title: 'Roomba\'s Home', Language: req.cookies.LanguageCookie}); 
});

router.get('/control',function(req, res){
	res.render('roomba_control.ejs',{body: 'some kind of body body', title: 'Roomba\'s control', Language: req.cookies.LanguageCookie, Network: "ws://192.168.20.230:25565"});
});

router.get('/blog',function(req, res){
	res.render('roomba_blog.ejs',{body: 'somebody', title: 'Roomba\'s blog', Language: req.cookies.LanguageCookie});
});

// redirect to default route
router.get('/', function(req, res) {
// 	To Read a Cookie
//  var cookies = parseCookies(request);
// 	To Write a Cookie
//	response.writeHead(200, {
//   'Set-Cookie': 'mycookie=test',
//   'Content-Type': 'text/plain'
// });
	res.setHeader('Set-Cookie','LanguageCookie=NL');
	res.redirect('/project_info'); 
});

module.exports = router;
