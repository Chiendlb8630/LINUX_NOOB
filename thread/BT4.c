#include<stdio.h> 
#include<stdlib.h> 
#include<pthread.h> 
#include <time.h>

int num[100]; 
int even, odd;
pthread_t evenId, oddId;

void* even_thread(void* arg){
    for(int i = 0;i<100;i++){
        if(num[i] % 2 == 0){
            even++;
        }
    }
    printf("The number of even numbers is : %d\n",even);
}

void* odd_thread(void* arg){
    for(int i = 0;i<100;i++){
        if(num[i] % 2 != 0){
            odd++;
        }
    }
    printf("The number of odd numbers is : %d\n",odd );
}

void main(){
    srand(time(NULL));

    for( int i = 0;i<100;i++){
        num[i] = rand() %100 +1;
    }

    pthread_create(&evenId,NULL,&even_thread, NULL);
    pthread_create(&oddId,NULL,&odd_thread,NULL);

    pthread_join(evenId, NULL);
    pthread_join(oddId,NULL);
}

