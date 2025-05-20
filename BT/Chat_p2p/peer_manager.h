
#ifndef PEER_MANAGER_H
#define PEER_MANAGER_H

#include <netinet/in.h>

#define MAX_PEERS 10
typedef struct {
    int id;                     
    int socket_fd;           
    struct sockaddr_in addr;    
} Peer;

void init_peer_manager();
int add_peer(int socket_fd, struct sockaddr_in *addr);
int remove_peer_by_id(int id);
Peer* get_peer_by_id(int id);
void list_peers();
void cleanup_peers();

#endif
