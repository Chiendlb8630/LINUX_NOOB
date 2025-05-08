#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h>
#include<string.h> 


int main(int argc, char *argv[]){
    
    pid_t pid;
    pid = fork();
    char * cmd = getenv("CMD");

    if(pid < 0){
        perror("create child process failed");
    }
    else if( pid == 0){
        printf(" I'm child_process, my PID is %d\n", getpid());
        if(strcmp(cmd, "1")== 0 ){
        execlp("ls", "ls", NULL);    
        }
        else if(strcmp(cmd,"2")== 0){ 
           execlp("date","date",NULL); 
        }
    }
    else{
        printf("I'm Father process, my PID is %d\n", getpid());
    }

}
