#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main( int argc, char const argv[]){
    pid_t pid = fork();

    if(pid < 0){
        perror("create child_process failed");

    }else if(pid == 0){
        printf(" From child_process: My PID is %d\n",getpid());
    }else 
    printf("From father_process : My child_PID is %d\n",pid);
}