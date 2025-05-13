#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char* atgv[]){

    struct sockaddr_t  client_addr;
    memset(&client_addr, 0, sizeof(client_addr));

    int client_fd, new_client_fd;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client == -1) hanlde_error("socket()");

    

}