# Echo client program
import socket
import time

#HOST = '192.168.0.8'        # The remote host
HOST = 'localhost'        # The remote host
PORT = 50007              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
print "\nConnected to " + HOST
ct=0
while 1:
    s.send("Hello, world "+ str(ct) + "\n")
    ct=ct+1
    time.sleep(1)
    if ct >= 8: break
s.close()
print ("Closed connection. Sent messages=", ct)
