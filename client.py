import socket               # Import socket module

s = socket.socket()         # Create a socket object
s.connect(('localhost', 8000))
s.sendall("Hello from client".encode())

msg = s.recv(19)
print(msg.decode())

s.close()                     # Close the socket when done