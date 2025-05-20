#include "network.h"
#include "peer_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_PENDING 10

static int listening_port = 0;

void print_my_ip() {
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;

    gethostname(hostbuffer, sizeof(hostbuffer));
    host_entry = gethostbyname(hostbuffer);
    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

    printf("Local IP: %s\n", IPbuffer);
}

void print_my_port() {
    printf("Listening on port: %d\n", listening_port);
}

void connect_to_peer(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in peer_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return;
    }

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &peer_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&peer_addr, sizeof(peer_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return;
    }

    int id = add_peer(sockfd, &peer_addr);
    if (id >= 0) {
        printf("Connected to %s:%d with ID %d\n", ip, port, id);
    } else {
        printf("Peer list is full. Connection refused.\n");
        close(sockfd);
    }
}

void send_message(int peer_id, const char *msg) {
    Peer *peer = get_peer_by_id(peer_id);
    if (!peer) {
        printf("Peer ID not found.\n");
        return;
    }

    if (send(peer->socket_fd, msg, strlen(msg), 0) < 0) {
        perror("Send failed");
    } else {
        printf("Message sent to peer %d\n", peer_id);
    }
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    getpeername(client_socket, (struct sockaddr *)&addr, &len);

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(addr.sin_port);

    int id = add_peer(client_socket, &addr);
    printf("New connection from IP: %s with port: %d (ID: %d)\n", client_ip, client_port, id);

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        printf("Received from %s:%d: %s\n", client_ip, client_port, buffer);
    }

    printf("Connection closed from %s:%d\n", client_ip, client_port);
    remove_peer_by_id(id);
    close(client_socket);
    return NULL;
}

static void *server_thread(void *arg) {
    int port = *(int *)arg;
    free(arg);
    start_server(port);
    return NULL;
}

void start_server_async(int port) {
    listening_port = port;
    pthread_t tid;
    int *port_arg = malloc(sizeof(int));
    *port_arg = port;

    if (pthread_create(&tid, NULL, server_thread, port_arg) != 0) {
        perror("Failed to start server thread");
        free(port_arg);
        exit(1);
    }
    pthread_detach(tid);
}

void start_server(int port) {
    int server_socket;
    struct sockaddr_in server_addr;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Create a socket failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, MAX_PENDING) < 0) {
        perror("Listen failed");
        close(server_socket);
    }

    printf("Server is listening on port %d\n", port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *client_socket = malloc(sizeof(int));
        if ((*client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("Accept failed");
            free(client_socket);
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_socket);
        pthread_detach(tid);
    }

    close(server_socket);
}
