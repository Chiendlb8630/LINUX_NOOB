#include<stdio.h> 
#include<pthread.h> 
#include<stdlib.h> 

static int data = 8630;
pthread_t T1,T2,T3,T4,T5;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* Read_thread(void* arg){

    const char * name = (const char*) arg;  
    pthread_rwlock_rdlock(&rwlock);
    printf("data : %d is read by thread : %s \n",data,name);
    pthread_rwlock_unlock(&rwlock);
}

void* Write_thread(void* arg){
    const char * name = (const char*) arg; 
    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("data : %d is written by thread : %s \n",data,name);
    pthread_rwlock_unlock(&rwlock);

}



void main(){

    pthread_create(&T1,NULL,&Read_thread,(void *)"thread 1");
    pthread_create(&T2,NULL,&Read_thread,(void *) "thread 2");
    pthread_create(&T3,NULL,&Read_thread,(void *)"thread 3");
    pthread_create(&T4,NULL,&Write_thread,(void *) "thread 4");
    pthread_create(&T5,NULL,&Write_thread,(void *) "thread 5");

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);
    pthread_join(T3,NULL);
    pthread_join(T4,NULL);
    pthread_join(T5,NULL);

}