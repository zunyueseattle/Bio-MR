import binascii
import socket
import sys
import struct


values = (2863311530, 1.0)
packer = struct.Struct('I f')
packed_data = packer.pack(*values)
 
print(packed_data);

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 60221)
sock.connect(server_address)

sock.sendall(packed_data)
