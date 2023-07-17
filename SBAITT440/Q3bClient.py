#QUESTION PART C (b)
# THIS IS CLIENT 
import socket

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Define the server address and port
server_addrss = ('127.0.0.1', 8080)

# Get the number from the user
num = int(input('Enter a number: '))

# Send the number to the server
client_socket.sendto(str(num).encode(), server_addrss)

# Receive the result from the server
data, _ = client_socket.recvfrom(1024)
result = data.decode()

# Print the result
if result == 'True':

    print(f'{num} is a prime number.')
else:
    print(f'{num} is not a prime number.')

# Close the socket
client_socket.close()
