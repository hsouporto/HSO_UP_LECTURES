#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// STATUS: TESTED

static void handler_usr1()  { printf("received SIGUSR1\n"); }
static void handler_usr2()  { printf("received SIGUSR2\n"); }
static void handler_hup()   { printf("received SIGHUP\n"); }
static void handler_stp()   { printf("received SIGSTP\n"); }
static void handler_INT()   { printf("received SIGINT\n"); }
static void handler_KILL()   { printf("received SIGKILL\n"); }




int main(int argc, char *argv[]){
    printf("My PID is %d\n", getpid());

    if (signal(SIGUSR1, handler_usr1) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGUSR1: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, handler_usr2) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGUSR2: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGHUP, handler_hup) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGHUP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTSTP, handler_stp) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGSTP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, handler_INT) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGINT: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGKILL, handler_KILL) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGKILL: %s", strerror(errno));
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

You cannot SIGKILL, at least not for the process being killed.

*/