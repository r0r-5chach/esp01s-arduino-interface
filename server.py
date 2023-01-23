import socket

port = 420

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("", port))

while True:
    print("Running")
    data, addr = sock.recvfrom(1024)
    print(f"Message recieved: {data.decode()}")