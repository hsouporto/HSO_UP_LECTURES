#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/errno.h>
static int param; /* program parameter */
void read_parameter(){
    FILE *fp = fopen(".config", "r");
    fscanf(fp, "param: %d\n", &param);
    fclose(fp);
}

void write_parameter(){
    printf("param: %d\n", param);
}

void handler(int signum){
    read_parameter();
    write_parameter();
}

int main(int argc, char *argv[]){
    if (signal(SIGHUP, handler) == SIG_ERR){
        fprintf(stderr, "Can’t catch SIGHUP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("my PID is %d\n", getpid());
    read_parameter();
    printf("waiting...");

    
    for (;;)
        pause();
}