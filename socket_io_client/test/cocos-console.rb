#!/usr/bin/ruby

require "socket"

if ARGV[0] == nil then
  return;
end

sock = TCPSocket.open("localhost", 6010)

command = "hello #{ARGV[0]}\n"

sock.write(command)

sock.close
