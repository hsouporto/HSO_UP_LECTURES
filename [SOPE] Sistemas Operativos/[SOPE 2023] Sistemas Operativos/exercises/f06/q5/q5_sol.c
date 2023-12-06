#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int flag = 1;

void handle_sigint(int signum) {
    if (signum == SIGINT) {
        printf("\nReceived SIGINT. Exiting gracefully.\n");
        flag = 0;
    }
}

int main(int argc, char* argv[]) {
    printf("My PID is %d\n", getpid());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);

    

    while (flag)
        pause();

    exit(EXIT_SUCCESS);
}