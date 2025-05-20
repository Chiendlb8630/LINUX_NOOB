#ifndef NETWORK_H
#define NETWORK_H

void start_server(int port);
void print_my_ip();
void print_my_port();
void connect_to_peer(const char *ip, int port);
void send_message(int peer_id, const char *msg);
void start_server_async(int port);


#endif