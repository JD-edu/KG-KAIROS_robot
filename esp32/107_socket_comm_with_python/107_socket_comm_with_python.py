import socket

print("Creating server...")
s = socket.socket()
s.bind(('0.0.0.0', 10000))
s.listen(0)

while True:
    client, addr = s.accept()
    while True:
        content = client.recv(6)
        if len(content) == 0:
            client.send("uga".encode())
            break
        else:
            print(content.decode())
    #print("Closing connection")
    client.close()
