#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("hello ");          /* no '\n': stays in the stdio buffer */
    /* fflush(stdout); */      /* uncomment to print "hello" only once */
    if (fork() == 0) {
        printf("from child\n");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    printf("from parent\n");
    exit(EXIT_SUCCESS);
}
