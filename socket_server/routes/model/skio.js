var app  = require('../../app');
var http = require('http').Server(app);
var io   = require('socket.io').listen(http);

function skio() {
  http.listen(app.get('port'), function() {
    console.log('Start listening...');
    console.log('port: ' + app.get('port'));
  });

  io.on('connection', function(socket) {
    socket.on('hello', function(data) {
      console.log('message: ' + data.value);
      socket.emit('hello', { value : data.value});
    });
  });
}

module.exports = skio;
