#!/usr/bin/ruby

require "socket"

if ARGV[0] == nil then
  return;
end

# 127.0.0.1(localhost)の20000番へ接続
sock = TCPSocket.open("localhost", 6010)

sock.write("hello #{ARGV[0]}\n")

# 送信が終わったらソケットを閉じる
sock.close
