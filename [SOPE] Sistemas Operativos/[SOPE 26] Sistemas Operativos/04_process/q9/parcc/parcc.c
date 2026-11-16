/*
 * parcc - compile a C program made of several source files in parallel.
 *
 * Usage: parcc -o prog prog1.c prog2.c ... progn.c
 *
 * 1. For each source file, create a child process that runs
 *        gcc -Wall -c progX.c
 * 2. Wait until all children have finished.
 * 3. Link everything with
 *        gcc prog1.o ... progn.o -o prog
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    /* argv: parcc -o prog file1.c file2.c ... */
    if (argc < 4 || strcmp(argv[1], "-o") != 0) {
        fprintf(stderr, "Usage: %s -o prog prog1.c ... progn.c\n", argv[0]);
        return 1;
    }
    char *prog = argv[2];
    char **files = &argv[3];
    int n = argc - 3;

    /* Step 1: start one compiler process per source file. */
    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("[pid:%d] compiling %s ...\n", getpid(), files[i]);
            fflush(stdout);
            execlp("gcc", "gcc", "-Wall", "-c", files[i], NULL);
            perror("exec");            /* reached only if exec fails */
            exit(1);
        }
    }

    /* Step 2: wait for all of them; remember if any failed. */
    int errors = 0;
    for (int i = 0; i < n; i++) {
        int status;
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
            errors++;
    }
    if (errors > 0) {
        fprintf(stderr, "parcc: %d file(s) failed to compile, not linking\n", errors);
        return 1;
    }

    /* Step 3: build "gcc prog1.o ... progn.o -o prog" and run it. */
    char *cmd[n + 4];
    cmd[0] = "gcc";
    for (int i = 0; i < n; i++) {
        cmd[i + 1] = strdup(files[i]);
        cmd[i + 1][strlen(files[i]) - 1] = 'o';   /* prog.c -> prog.o */
    }
    cmd[n + 1] = "-o";
    cmd[n + 2] = prog;
    cmd[n + 3] = NULL;

    if (fork() == 0) {
        execvp("gcc", cmd);
        perror("exec");
        exit(1);
    }

    int status;
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "parcc: linking failed\n");
        return 1;
    }
    return 0;
}
