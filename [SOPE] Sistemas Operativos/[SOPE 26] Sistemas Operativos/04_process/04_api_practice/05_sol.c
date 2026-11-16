#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./timeit cmd [args...] */


int main(int argc, char *argv[])
{
    if (argc < 2) { fprintf(stderr, "Usage: %s cmd [args...]\n", argv[0]); return 1; }

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        execvp(argv[1], &argv[1]);          /* argv[1..] is already NULL-terminated */
        perror("execvp");
        exit(127);
    }

    int status;
    waitpid(pid, &status, 0);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double secs = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    fprintf(stderr, "[timeit] %s: %.3f s, exit code %d\n",
            argv[1], secs, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}