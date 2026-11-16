#include <stdio.h>
#include <pthread.h>
int count = 0;

void *inc(void *arg){
    for (int i = 0; i < 1000000; i++)
        count++;
    return NULL;
}

int main(){
    printf("Start: %d\n", count);
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, inc, NULL);
    pthread_create(&tid2, NULL, inc, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("End: %d\n", count);
}

/* BRIEF EXPLAINATION

* count is global
* Two threadsa are launched in main with pthread_create
* The threads do not receive any entry argument (last argument)
* Threads will execute the function inc
* The thread identifiers are stored in variables tid1 and tid2
* The main thread does not do any further computation, so it has to wait for the threads to terminate pthread_join(id, NULL)
* If the main thread did return or exit, both threads tid1 and tid2 would terminate immediately
* Hence, it calls pthread_join on both threads
* Looking at the function inc
* Each thread performs a loop with 10^6 iterations and increment the global variable count

The problem:
 - If you run the program multiple times, you will get varying outputs. 
 - The problem is that we have two threads writing to the same variable without any synchronisation.

 - Altough count++ looks like an atomic operation, it is not. 
 - But even if it was, imagine that both threads are perfectly running in parallel,
  on different CPU cores. At some time instant, count is 500, and both threads execute count++.
   What is the final result? 501, when it should be 502.

Nonetheless, count++ is not an atomic operation. 


*/