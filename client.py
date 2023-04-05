import socket               # Import socket module

s = socket.socket()         # Create a socket object
s.connect(('localhost', 8000))
s.sendall("Hello from client".encode())
s.close()                     # Close the socket when done