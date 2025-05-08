#include<stdio.h> 
#include<pthread.h> 



pthread_t id1, id2, id3;

static int cnt = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_handle(void * arg){
    char * thread_name = (char *) arg;
    pthread_mutex_lock(&lock); 
    while(1){
        if( cnt> 1000000){
        break;
        pthread_mutex_unlock(&lock);
        }

    cnt++;
    printf(" cnt increase to : %d by %s\n",cnt,thread_name);
    pthread_mutex_unlock(&lock);
    }
}



void main(){

    pthread_create(&id1, NULL, thread_handle, "thread 1");
    pthread_create(&id2, NULL, thread_handle, "thread 2");
    pthread_create(&id3, NULL, thread_handle, "thread 3");

    printf("lastest value : %d \n", cnt);


    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
}
