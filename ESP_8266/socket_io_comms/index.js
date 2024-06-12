var app = require('express')(); // express framwork for a basic http server
var http = require('http').createServer(app); // create the http server
var io = require('socket.io')(3005); // require the socket.io and bind it to a port 

io.attach(http, {
    pingInterval: 10000,
    pingTimeout: 5000,
    cookie: false
   });

io.on('connection', function (socket) 
{
    console.log('user connected');
  
    socket.on('disconnect', function () 
    {
      console.log('user disconnected');
    });
    socket.on('message', function (msg) 
    {
     console.log("message: "+msg);
    });
    timeout();
});
  
function timeout() 
{
    setTimeout(function () 
    {
        io.emit('reply',"A message from server");
        timeout();
    }, 5000);
}

http.listen();
