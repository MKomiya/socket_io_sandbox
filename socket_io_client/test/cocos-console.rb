#!/usr/bin/ruby

require "socket"
sock = TCPSocket.open("localhost", 6010)

puts("Listen command.")
#print("> ")

th = Thread.new {
  while ret = sock.gets
    puts ret
  end
}

while msg = STDIN.gets
  puts("sending #{msg}")
  sock.write(msg)
end

th.join

sock.close
