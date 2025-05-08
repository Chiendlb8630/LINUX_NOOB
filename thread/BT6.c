#include<stdio.h> 
#include<pthread.h> 
#include<stdlib.h> 

int arr[1000000];
static long sum;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t threads[4];

typedef struct{
    int start; 
    int end;
    int thread_Id;
} ThreadData; 

void * sum_array(void* arg){
    ThreadData* data = (ThreadData*) arg;
    pthread_mutex_lock(&lock);
    for(int i = data-> start;i< data-> end;i++){
        sum+= arr[i];
    }

    printf("Total sum of arr : %ld is calculated by thread : %d\n",sum, data->thread_Id);
    pthread_mutex_unlock(&lock);
}

void main(){
    ThreadData thread_data[4];
    for(int i = 0;i<1000000;i++){
        arr[i] = 1;
    }

    for(int i = 0;i< 4;i++){
    thread_data[i].start = i*(1000000/4);
    thread_data[i].end = thread_data[i].start + (1000000/4);
    thread_data[i].thread_Id = i;

    pthread_create( &threads[i] ,NULL, sum_array , (void*) &thread_data[i]);
    }

    for(int i = 0;i < 4; i++ ){
        pthread_join(threads[i],NULL);
    }
}


