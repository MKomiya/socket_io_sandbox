#!/usr/bin/ruby

require "socket"
sock = TCPSocket.open("localhost", 6010)

loop do
  msg = STDIN.gets.strip
  next if msg.empty?

  break if msg == "exit"

  sock.write(msg)
end

sock.close
