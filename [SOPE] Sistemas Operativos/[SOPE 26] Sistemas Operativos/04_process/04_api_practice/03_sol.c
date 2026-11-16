#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Usage: ./ex03 N   -> child exits with N; ./ex03 abort -> child crashes */
int main(int argc, char *argv[])
{
    if (argc != 2) { fprintf(stderr, "Usage: %s N|abort\n", argv[0]); return 1; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        if (strcmp(argv[1], "abort") == 0)
            abort();                       /* killed by SIGABRT */
            
        exit(atoi(argv[1]));
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        printf("child %d exited with code %d\n", pid, WEXITSTATUS(status));

    else if (WIFSIGNALED(status))
        printf("child %d killed by signal %d (%s)\n",
               pid, WTERMSIG(status), strsignal(WTERMSIG(status)));

    return 0;
}