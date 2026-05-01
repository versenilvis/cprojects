/*
TCP Server
==========
Flow:
socket()     -> creates a socket fd
bind()       -> binds the fd to the IP address and port
listen()     -> tells the OS "I am ready to receive a connection"
accept()     -> waits for and accepts a connection -> returns a new fd
read()       -> reads data from the client
write()      -> sends data to the client
close()      -> closes the connection
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET; // ipv4
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY; // any address

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    // max 10 connections
    if (listen(server_fd, 10) < 0) {
        perror("Error listening on socket");
        return 1;
    }

    printf("TCP Server is listening on port 8080\n");

    int client_fd = accept(server_fd, NULL, NULL); // accept 1 connection

    // read data from client
    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    // send data to client
    char *msg = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 12\r\n"
                "\r\n"
                "Hello World!";
    write(client_fd, msg, strlen(msg));

    close(client_fd);
    close(server_fd);
    return 0;
}
