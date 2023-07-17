import socket

def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Define the server address and port
server_address = ('127.0.0.1', 8080)

# Bind the socket to the server address
server_socket.bind(server_address)

print('Server listening on {}:{}'.format(*server_address))

while True:
    # Receive the number from the client
    data, client_address = server_socket.recvfrom(1024)
    number = int(data.decode())

    # Check if the number is prime
    result = is_prime(number)

    # Send the result back to the client
    server_socket.sendto(str(result).encode(), client_address)

