//QUESTION PART B (a)
//THIS IS SERVER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MIN_R 50000
#define MAX_R 80000

int generate_random_num() {
    return (rand() % (MAX_R - MIN_R + 1)) + MIN_R;
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in addrss;
    int opt = 1;
    int addrlen = sizeof(addrss);
    char buffer[1024] = {0};
    char response[1024] = {0};
    int random_num;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    addrss.sin_family = AF_INET;
    addrss.sin_addr.s_addr = INADDR_ANY;
    addrss.sin_port = htons(PORT);

    // Bind the socket to specified IP address and port
    if (bind(server_fd, (struct sockaddr *)&addrss, sizeof(addrss)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&addrss, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }


    random_num = generate_random_num();


    snprintf(response, sizeof(response), "%d", random_num);

   
    send(new_socket, response, strlen(response), 0);
    printf("Random number sent: %d\n", random_num);

    return 0;
}
