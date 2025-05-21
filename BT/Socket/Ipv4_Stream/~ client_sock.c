#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void handle_error(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *server_ip = argv[1];
    int portnum = atoi(argv[2]);
    const char *msg = "Hello from client!";
    
    int client_fd;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        handle_error("inet_pton()");
    }

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        handle_error("socket()");
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        handle_error("connect()");
    }

    send(client_fd, msg, strlen(msg), 0);
    printf("Message sent to server: %s\n", msg);

    close(client_fd);
    return 0;
}
