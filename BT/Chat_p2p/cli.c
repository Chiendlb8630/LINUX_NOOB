#include "network.h"
#include "peer_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define CMD_LEN 1000

void print_help() {
    printf("Available commands:\n");
    printf("help                : Show this help message\n");
    printf("myip                : Display this process's IP address\n");
    printf("myport              : Display the port on which this process is listening\n");
    printf("connect <ip> <port> : Connect to a peer\n");
    printf("list                : List all active connections\n");
    printf("terminate <id>      : Terminate connection by ID\n");
    printf("send <id> <msg>     : Send message to connection ID\n");
    printf("exit                : Close all connections and exit\n");
}


void handle_command(char *cmd_line) {
    char cmd_copy[CMD_LEN];
    strncpy(cmd_copy, cmd_line, CMD_LEN);  // copy content of cmd
    cmd_copy[CMD_LEN - 1] = '\0'; // avoid buffer overflow

    char *args[3];
    char *token = strtok(cmd_copy, " \n");
    int i = 0;
    while (token != NULL && i < 3) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }

    if (i == 0) return;

    if (strcmp(args[0], "help") == 0) {
        print_help();
    }

    else if (strcmp(args[0], "myip") == 0) {
        print_my_ip();     
    }

    else if (strcmp(args[0], "myport") == 0) {
        print_my_port(); 
    }

    else if (strcmp(args[0], "connect") == 0 && i == 3) {
        char *ip = args[1];
        int port = atoi(args[2]);
        connect_to_peer(ip, port); // from network.h
    }

    else if (strcmp(args[0], "list") == 0) {
        list_peers();
    }

    else if (strcmp(args[0], "terminate") == 0 && i == 2) {
        int id = atoi(args[1]);
        if (remove_peer_by_id(id) == 0)
            printf("Connection %d terminated\n", id);
        else
            printf("Invalid connection ID\n");
    }

    else if (strncmp(cmd_line, "send", 4) == 0) {  // fix segmentation faults ??????
        char *saveptr; 
        char *cmd = strtok_r(cmd_line, " ", &saveptr);
        char *id_str = strtok_r(NULL, " ", &saveptr);

        if (id_str == NULL) {
            printf("Usage: send <id> <message>\n");
            return;
        }

        int id = atoi(id_str);

        char *msg = strtok_r(NULL, "\n", &saveptr);
        if (msg == NULL || strlen(msg) == 0) {
            printf("No message to send.\n");
            return;
        }

        send_message(id, msg);
    }

    else if (strcmp(args[0], "exit") == 0) {
        cleanup_peers();
        exit(0);
    }
    else {
        printf("Invalid command. Type 'help' for list of commands.\n");
    }
}


int main(int argc, char *argv[]) {

    system("clear");

    printf("*********************************************************************************************************\n");
    printf("*************************************    Chat Application P2P    ******************************************\n");
    printf("*********************************************************************************************************\n\n");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <listening_port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);

    init_peer_manager();
    start_server_async(port);  

    char cmd_line[CMD_LEN];
    while (1) {
        printf("<<-.->> ");
        fflush(stdout);
        if (fgets(cmd_line, CMD_LEN, stdin) != NULL) {
            handle_command(cmd_line);
        }
    }

    return 0;
}
