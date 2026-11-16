#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./race 3 1 2  -> each child sleeps N seconds; print finishing order */
int main(int argc, char *argv[])
{
    int n = argc - 1;
    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            sleep(atoi(argv[i + 1]));
            exit(i + 1);                    /* exit code = position in argv */
        }
    }

    for (int place = 1; place <= n; place++) {
        int status;
        pid_t who = wait(&status);          /* returns whichever child ends first */
        int idx = WEXITSTATUS(status);
        printf("%d. child %d (slept %s s)\n", place, who, argv[idx]);
    }
    return 0;
}