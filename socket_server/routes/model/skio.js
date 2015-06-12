var app  = require('../../app');
var http = require('http').Server(app);
var io   = require('socket.io').listen(http);

var userlist = {};

function skio() {
  http.listen(app.get('port'), function() {
    console.log('Start listening...');
    console.log('port: ' + app.get('port'));
  });

  io.on('connection', function(socket) {

    socket.on('hello', function(data) {
      console.log('message: ' + data.value);
      socket.emit('hello', { value : data.value + " : " + socket.setRoomInfo });
    });

    socket.on('join', function(data) {
      socket.setRoomInfo = data.room;
      socket.join(data.room);
      socket.join(socket.id);

      console.log(data.room + " join");
      console.log("user_id: " + socket.id);

      socket.emit('joined_room', { id : socket.id });
    });

    socket.on('battle_proposal', function(data) {
      var battle_id = Math.floor(Math.random() * 2147483647);
      socket.to(data.to).emit('battle_proposal', {from: socket.id, to: data.to, battle_id: battle_id});
      start_battle(battle_id);
    });

    socket.on('get_rooms', function(data) {
      socket.emit('get_rooms', { rooms : socket.manager.rooms });
    });

    socket.on('msg_post', function(data) {
      socket.to(socket.setRoomInfo).emit("hello", data.msg);
    });

    socket.on('move', function(data) {
      console.log('moved: (' + data.x + ', ' + data.y + ')');
      socket.to.(socket.setRoomInfo).emit('move', { x : data.x, y : data.y });
    });

    socket.on("disconnect", function() {
      console.log("disconnected");
    });

    // 接続の確立をクライアントに通知
    socket.emit('connected', { id : socket.id });

    // バトル開始
    start_battle(battle_id);
  });
}

function start_battle(battle_id) {
  var battle = io.of('/battle/', + battle_id).on('connection', function(socket) {
    socket.on('game_start', function() {
      console.log('started game');
      socket.emit('game_start', {});
    })
  })
}

module.exports = skio;
