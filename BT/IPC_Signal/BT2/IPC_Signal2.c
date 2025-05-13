#include<stdio.h> 
#include<signal.h>
#include<stdlib.h>

void sig_hanlder( int num){
    

}


int main(){
    signal(SIGALRM,sig_hanlder);
}