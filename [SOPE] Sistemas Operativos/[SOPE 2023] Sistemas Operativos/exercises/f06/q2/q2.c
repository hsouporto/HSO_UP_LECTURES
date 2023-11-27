#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

// STATUS: TESTED

#define READ_END 0
#define WRITE_END 1

char *cmd1[] = {"ls", "-l", NULL};  // list files
char *cmd2[] = {"wc", "-l", NULL};  // count number of lines

int main(int argc, char *argv[]){
    int fd_pipe[2];
    pid_t pid;
    if (pipe(fd_pipe) < 0){
        /* pipe error */        // added
        fprintf(stderr, "Cannot pipe: %s\n", strerror(errno));
        return EXIT_FAILURE;

    }

    if ((pid = fork()) < 0){
        /* fork error */        // added
        fprintf(stderr, "Cannot fork: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (pid > 0){ // parent
        close(fd_pipe[READ_END]);
        dup2(fd_pipe[WRITE_END], STDOUT_FILENO); // stdout to pipe
        close(fd_pipe[WRITE_END]);
        // parent writes to the pipe
        if (execvp(cmd1[0], cmd1) < 0) {
            /* exec error */    // added
            fprintf(stderr, "[Parent] Failed to exec '%s': %s\n", cmd1[0], strerror(errno));
            return EXIT_FAILURE;
        }
    }
    else{   // child
        close(fd_pipe[WRITE_END]);
        dup2(fd_pipe[READ_END], STDIN_FILENO); // stdin from pipe
        close(fd_pipe[READ_END]);
        if (execvp(cmd2[0], cmd2) < 0) {
            /* exec error */    // added
            fprintf(stderr, "[Child] Failed to exec '%s': %s\n", cmd1[0], strerror(errno));
            return EXIT_FAILURE;
        }
    }
}


/* BREIF EXPLAINATION

* execvp allows to execute progras with string as arguments (facilitates things)
* In this case, the command  to be executed are preset as arrays of strings (dont forget NULL last!)

NOTE: execvp wants something like"./ls ls -l", so we need to put first argv[0] in execvp first argument 
to knows whats is being executed, and then the string commands to execute

* Parent issues an list all files (ls -l)
* Child receives the output on pipe and counts number of files (wc -l)


*/