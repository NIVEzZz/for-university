import socket

HOST = "127.0.0.1"
PORT = 5514

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind((HOST, PORT))
    print(f"Syslog-приёмник слушает {HOST}:{PORT} по UDP")

    while True:
        data, sender = server.recvfrom(8192)
        print(f"От {sender}: {data.decode('utf-8', errors='replace')}")
