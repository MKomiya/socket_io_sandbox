// create socket io's server
var io = require('socket.io')(8080);

io.on('connection', function(socket) {
  // send connect notification for client
  io.emit("sendMessageToClient", {value: "Entered one person."});

  // setting recieve event by client
  socket.on("sendMessageToServer", function(data) {
    io.emit("sendMessageToClient", {value: data.value});
  });

  // setting disconnect event
  socket.on("disconnect", function() {
    io.emit("sendMessageToClient", {value: "Withdraw one person."});
  });
});
