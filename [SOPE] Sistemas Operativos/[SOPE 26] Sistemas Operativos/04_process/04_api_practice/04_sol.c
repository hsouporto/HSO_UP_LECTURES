#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    /* Part A: zombie */
    pid_t z = fork();
    if (z == 0)
        exit(0);                            /* child ends immediately */
    printf("zombie child: %d -- run: ps -o pid,stat,cmd -p %d\n", z, z);
    fflush(stdout);
    sleep(10);                              /* parent has not waited yet */
    waitpid(z, NULL, 0);                    /* now the zombie disappears */
    printf("zombie reaped\n");
    fflush(stdout);                         /* don't copy the buffer into the next child */

    /* Part B: orphan */
    pid_t o = fork();
    if (o == 0) {
        printf("orphan: my parent is %d\n", getppid());
        sleep(2);                           /* parent exits meanwhile */
        printf("orphan: my parent is now %d\n", getppid());
        exit(0);
    }
    sleep(1);
    printf("parent %d exits without waiting\n", getpid());
    return 0;
}