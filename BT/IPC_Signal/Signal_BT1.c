#include<stdio.h> 
#include<signal.h>
#include<stdlib.h>


int cnt = 0;

void handle_sig(int sig){
    cnt++;
    if(cnt < 3) printf(" received SIGINT %d time", cnt);
    else if( cnt == 3 ) {
        printf("Received SIGINT 3 time, process exit");
        exit(0);
    }
}


int main(){
    signal(SIGINT,handle_sig);
    while(1){
        
    }

}