#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// STATUS: TESTED

int main(int argc, char *argv[]){

    int counter =0;
    for (int i = 0; i < 4; i++){
        counter++;
        printf("For loop controled by proccess pid: %d\n", getpid());

        if(fork()==0){  // child
            printf("Come inside child process with pid: %d\n", getpid());
            counter =0;

        }else           // parent
             printf("Come inside parent process with pid: %d\n", getpid());
            
    }
    printf("We are out of for loop with process pid: %d\n", getpid());
    printf("process Pid: %d forked %d process\n", getpid(), counter);

    return EXIT_SUCCESS;
}

/* BRIEF EXPLAINATION

* Here we create 16 process.
* NOTE: Each process has its own copy of i 

    * main makes 4 forks
        *child(i==0) makes 3 forks
            *child(i==1) makes 2 forks
                *child(i==2) makes 1 fork
                    *child(i==3) makes 0 fork

                *child(i==3) makes 0 forks

            *child(i==2) makes 1 forks

            *child(i==3) makes 0 forks 

        *child(i==1) makes 2 forks
            *child(i==2) makes 1 forks
                *child(i==3) makes 0 forks

            *child(i==3) makes 0 forks

        *child(i==2) makes 1 forks
            *child(i==3) makes 0 forks

        *child(i==3) makes 0 forks
*/
