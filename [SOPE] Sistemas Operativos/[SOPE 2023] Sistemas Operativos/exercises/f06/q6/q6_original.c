#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
static void handler1() { printf("received SIGUSR1\n"); }
static void handler2() { printf("received SIGUSR2\n"); }
static void handler3() { printf("received SIGHUP\n"); }



int main(int argc, char *argv[]){
    printf("My PID is %d\n", getpid());

    if (signal(SIGUSR1, handler1) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGUSR1: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, handler2) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGUSR2: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGHUP, handler3) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGHUP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* stick around ... */
    for (;;)
        pause();
}

/* BRIEF EXPLAINATION

* Here we are capturiing the signals and rediect to the proper handler

To replicate open a new shell and issue:

$ kill -USR1 PID
$ kill -USR2 PID
$ kill -HUP PID


*/