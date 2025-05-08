#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


static int data; 
static int available = 0; 


pthread_t conId, proId;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* pro_thread(void* arg){
    while(1){
    srand(time(NULL));
    sleep(1); 
    pthread_mutex_lock(&lock);
    data = rand() % 9 + 1;
    printf(" data is created by producer : %d\n", data);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}
}

void* con_thread(void * arg){
    while(1){
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond, &lock);
        printf("%d\n", data);
        pthread_mutex_unlock(&lock);
    }
}
void main(){
    pthread_create(&conId,NULL,con_thread,NULL);
    pthread_create(&proId,NULL,pro_thread,NULL);

    pthread_join(conId,NULL);
    pthread_join(proId,NULL);

}