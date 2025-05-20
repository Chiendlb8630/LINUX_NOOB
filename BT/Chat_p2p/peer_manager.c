#include "peer_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         
#include <arpa/inet.h>      

static Peer peer_list[MAX_PEERS];
static int peer_count = 0;
static int next_id = 1;

void init_peer_manager() {
    memset(peer_list, 0, sizeof(peer_list));
    peer_count = 0;
    next_id = 1;
}

int add_peer(int socket_fd, struct sockaddr_in *addr) {
    if (peer_count >= MAX_PEERS) return -1;

    Peer *p = &peer_list[peer_count++];
    p->id = next_id++;
    p->socket_fd = socket_fd;
    memcpy(&p->addr, addr, sizeof(struct sockaddr_in));
    return p->id;
}

int remove_peer_by_id(int id) {
    for (int i = 0; i < peer_count; i++) {
        if (peer_list[i].id == id) {
            close(peer_list[i].socket_fd);
            peer_list[i] = peer_list[peer_count - 1];  
            peer_count--;
            return 0;
        }
    }
    return -1;
}

Peer* get_peer_by_id(int id) {
    for (int i = 0; i < peer_count; i++) {
        if (peer_list[i].id == id) {
            return &peer_list[i];
        }
    }
    return NULL;
}

void list_peers() {
    printf("ID\tIP\t\tPORT\n");
    for (int i = 0; i < peer_count; i++) {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(peer_list[i].addr.sin_addr), ip, INET_ADDRSTRLEN);
        int port = ntohs(peer_list[i].addr.sin_port);
        printf("%d\t%s\t%d\n", peer_list[i].id, ip, port);
    }
}

void cleanup_peers() {
    for (int i = 0; i < peer_count; i++) {
        close(peer_list[i].socket_fd);
    }
    peer_count = 0;
}
