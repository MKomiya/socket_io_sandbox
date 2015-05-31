#!/usr/bin/ruby

require "socket"
sock = TCPSocket.open("localhost", 6010)

while msg = STDIN.gets
  print("you writed: #{msg}")
  sock.write(msg)

  sock.each_line { |line|
    puts line
  }
end

sock.close
