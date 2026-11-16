#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    if (fork() && fork())
        fork();
    printf("pid=%d ppid=%d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}
