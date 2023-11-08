#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    /* Child */
    if (pid == 0)
        exit(0);                // enforce exit child

    /* Parent */
    sleep(100);                 // we need some time to observe zombie (100 seconds)

    pid = wait(&status);        // parent waits
    if (WIFEXITED(status))
        fprintf(stderr, "\n\t[%d]\tProcess %d exited with status %d.\n", (int) getpid(), pid, WEXITSTATUS(status));

    return 0;
}

/* BRIEF EXPLAINATION

* ps -ef | grep prog.out

*/