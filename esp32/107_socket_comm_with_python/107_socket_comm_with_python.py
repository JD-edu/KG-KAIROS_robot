import socket  
import time              

sock = socket.socket()

host = "172.30.1.75" #ESP32 IP in local network
port = 80             #ESP32 Server Port    

sock.connect((host, port))



while True:
    message = b"Hello World"
    sock.send(message)
    time.sleep(1)
data = ""     



#while len(data) < len(message):
#    data += sock.recv(1)

print(data)

sock.close()
