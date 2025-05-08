#include<stdio.h> 
#include<stdlib.h> 
#include<signal.h>
#include<unistd.h> 
#include<sys/wait.h>

void handle_sigusr1(int sig){
    printf("Child process recieved signal from father process : %d\n",sig);
}

int main( int argc, char *argv[0]){
    pid_t pid; 
    pid = fork();

    if(pid < 0){
        printf(" create child process failed");
    }else if( pid == 0){
        printf("I'm child_process %d\n ", getpid());
        signal(SIGUSR1, handle_sigusr1);
        pause();

    }else{
        printf("I'm father_process %d\n", getpid());
        printf("I'm gonna send a signal to my child_process %d\n", pid);
        sleep(1); 
        kill(pid,SIGUSR1);
        wait(NULL);
    }
}
