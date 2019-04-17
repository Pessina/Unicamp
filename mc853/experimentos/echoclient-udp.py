# Echo client UDP program
# Sends a datagram to server and receives echo from server
# Repeats every 4 seconds

from time import sleep
import socket
import sys
import time

HOST = 'xaveco.lab.ic.unicamp.br'        # The remote host
PORT = 8000              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # IP4, datagram socket object
echofile=sys.argv[1]
f=open(echofile, 'r') #  abre para leitura
start = time.time()
lines = 0
while 1:
    line=f.readline() # le uma linha
    if (not line):    # se fim do arquivo,
        break          #  sai do laco
    s.sendto(line, (HOST, PORT))
    data =s.recv(1255)
    print(data)
    lines = lines + 1
end = time.time()
print end - start
print lines
s.close()
