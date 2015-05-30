#!/usr/bin/ruby

require "socket"
sock = TCPSocket.open("localhost", 6010)

while msg = STDIN.gets
  print("you writed: #{msg}")
  sock.write(msg)
  while ret = sock.gets
    print("#{ret}")
  end
end

sock.close
