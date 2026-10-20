import socket

HOST = "127.0.0.1"
PORT = 5515

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen()

    print(f"TCP-приёмник слушает {HOST}:{PORT}")

    while True:
        connection, sender = server.accept()

        with connection:
            stream = connection.makefile("r", encoding="utf-8")
            for line in stream:
                print(f"От {sender}: {line.rstrip()}")
