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
    new_socket_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
    if (new_socket_fd == -1) handle_error("accept()");

    printf("New client connected!\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));  // Xóa buffer

    ssize_t bytes_received = read(new_socket_fd, buffer, sizeof(buffer) - 1);
    if (bytes_received < 0) {
        perror("read()");
    } else if (bytes_received == 0) {
        printf("Client closed the connection.\n");
    } else {
        printf("Message from client: %s\n", buffer);
    }

    write(new_socket_fd, "hello\n", strlen("hello\n"));

    close(new_socket_fd);
}

    

    close(server_fd);
    return 0;
}
