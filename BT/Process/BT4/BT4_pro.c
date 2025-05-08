#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h> 

int main( int argc , char* argv[0] ){
    pid_t pid = fork();

    if( pid < 0){
        perror(" Create child process failed");
    }
    else if( pid == 0){
        printf("I'm child process with id : %d\n", getpid());
        while(1){
            printf("I'm gonna exit in 5 second\n ");
            sleep(5);
            exit(5);
        }
    }
    else{
        printf("I'm father process, waiting for child_process exit\n");
        int status; 
        wait(& status);
        if(WIFEXITED(status)){
            int rv = WEXITSTATUS(status);
            printf(" child process exit with status : %d\n", rv);
        }else{
            printf("Child process did not exit normally.\n");
        }
    }
}
