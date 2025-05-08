#include<stdio.h> 
#include<pthread.h> 
#include<stdlib.h> 
pthread_t id1, id2; 


void *thread1_handler(void* arg){
        pthread_t tid1 = pthread_self();
        printf("Hello from thread 1 with ID : (%lu)\n",tid1);
}

void *thread2_handler(void* arg){
        pthread_t tid2 = pthread_self();
        printf("Hello from thread 2 with ID : (%lu)\n", tid2);
}

void main(){
        pthread_create(&id1, NULL, thread1_handler, NULL);
        pthread_create(&id2, NULL, thread2_handler, NULL);

        pthread_join(id1, NULL);
        pthread_join(id2, NULL);
}