// create socket io's server
var server = require('http').Server();
var socketIO = require('socket.io');
var io = socketIO.listen(server);

var player_list = [];

io.on('connection', function(socket) {
  console.log("connected");

  var player_id = Math.floor(Math.random() * 2147483647);
  player_list.push(player_id);

  console.log("player_list:");
  console.log(player_list);

  // setting chat command
  socket.on('hello', function(data) {
    console.log("hello : " + data.value);
    io.sockets.emit('hello', { value: data.value });
  });

  // setting disconnect event
  socket.on("disconnect", function() {
    console.log("disconnected");
  });

  io.sockets.emit('hello', { value: "welcome" });
});
server.listen(3000);
