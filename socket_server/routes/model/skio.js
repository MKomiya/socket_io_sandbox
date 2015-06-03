var app  = require('../../app');
var http = require('http').Server(app);
var io   = require('socket.io').listen(http);

var player_list = [];

function skio() {
  http.listen(app.get('port'), function() {
    console.log('Start listening...');
    console.log('port: ' + app.get('port'));
  });

  io.on('connection', function(socket) {
    var player_id = Math.floor(Math.random() * 2147483647);
    player_list.push(player_id);

    console.log("player_list:");
    console.log(player_list);

    socket.on('hello', function(data) {
      console.log('message: ' + data.value);
      socket.emit('hello', { value : data.value});
    });

    socket.on('init', function(data) {
      socket.setRoomInfo = data.room;
      socket.join(data.room);
      socket.join(socket.id);

      console.log(data.room + " join");
    });

    socket.on('msg_post', function(data) {
      socket.to(socket.setRoomInfo).emit("hello", data.msg);
    })

    socket.on('move', function(data) {
      console.log('moved: (' + data.x + ', ' + data.y + ')');
      socket.emit('move', { x : data.x, y : data.y });
    });

    socket.on("disconnect", function() {
      player_list.pop();
      console.log("disconnected");
    });
  });
}

module.exports = skio;
