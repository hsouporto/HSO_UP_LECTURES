#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    printf("hello ");
    if (fork() == 0) {
        printf("from child\n");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    printf("from parent\n");
    exit(EXIT_SUCCESS);
}