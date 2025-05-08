#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){

    pid_t pid_zom = fork();

    if(pid_zom < 0 ){
        perror("create child process failed");
    }else if( pid_zom == 0){
        printf("I'm zombie process with PID : %d\n",getpid());
        exit(0);
    }

    pid_t pid_or = fork();

    if(pid_or < 0){
        perror("create orphan process failed\n");
    } else if(pid_or == 0){
        sleep(20);
        printf("I'm orphan process with PID: %d and Parent PID: %d\n",getpid(),getppid()); 
        exit(0);
    }

    printf("I'm parent process with PID : %d\n", getpid());
    sleep(5); 
    exit(0);

    
}
