import socket

HOST = '10.48.103.180'
PORT = 65432
string = input("Escribe el mensaje para Neri: ")
mess = bytes(string, 'utf-8')
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(mess)
    data = s.recv(1024)

print('Received ', data.decode('utf8'))