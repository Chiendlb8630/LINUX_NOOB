#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LISTEN_NUM 10

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int portnum;
    if (argc >= 2) {
        portnum = atoi(argv[1]);  
    }

    int server_fd, new_socket_fd;
    struct sockaddr_in serv_addr, client_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // syscall socket()
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) handle_error("socket()");

    // init information
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // binding()
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");

    // syscall listen()
    if (listen(server_fd, LISTEN_NUM) == -1)
        handle_error("listen()");

    socklen_t len = sizeof(client_addr);
    while (1) {
        printf("Server is waiting on port %d\n", portnum);
        new_socket_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
        if (new_socket_fd == -1) handle_error("accept()");

        printf("New client connected!\n");
        write(new_socket_fd,"hello\n", sizeof("hello\n"));
        close(new_socket_fd);
    }

    close(server_fd);
    return 0;
}
