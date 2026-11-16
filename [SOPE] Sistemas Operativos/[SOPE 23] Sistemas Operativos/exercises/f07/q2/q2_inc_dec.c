#include <stdio.h>
#include <pthread.h>

//STATUS: TESTED

int count = 0;
pthread_mutex_t lock;

void *inc(void *arg){
    

    for (int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&lock);
        count++;
        if(count<0)printf(".");
        pthread_mutex_unlock(&lock);

    }
       
    return NULL;
}

void *dec(void *arg){
    

    for (int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&lock);
        count--;
        if(count<0)printf(".");
        pthread_mutex_unlock(&lock);

    }
       
    return NULL;
}

int main(){
    printf("Start: %d\n", count);

    // start the mutex
    pthread_mutex_init(&lock, NULL);

    // threads identifiers
    pthread_t tid1, tid2;

    // cretae the threads (no arguments passed)
    pthread_create(&tid1, NULL, inc, NULL);
    pthread_create(&tid2, NULL, dec, NULL);

    // wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // destoy the mutex
    pthread_mutex_destroy(&lock);

    printf("End: %d\n", count);

    return 1;

}