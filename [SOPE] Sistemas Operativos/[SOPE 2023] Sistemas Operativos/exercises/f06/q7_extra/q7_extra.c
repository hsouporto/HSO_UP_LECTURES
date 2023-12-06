#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>


#define READ_END 0
#define WRITE_END 1

char *cmd1[] = {"ls", "-l", NULL};
char *cmd2[] = {"wc", "-l", NULL};


int main(int argc, char *argv[]){
    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }


    if (pid > 0){
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO); // stdout to pipe
        close(fd[WRITE_END]);


        // parent writes to the pipe
        if (execvp(cmd1[0], cmd1) < 0){
            fprintf(stderr, "Failed to exec '%s': %s\n", "exec", strerror(errno));
            return EXIT_FAILURE;
        }
    }

    else{ // child
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO); // stdin from pipe
        close(fd[READ_END]);
        if (execvp(cmd2[0], cmd2) < 0){
            fprintf(stderr, "Failed to exec '%s': %s\n", "exec", strerror(errno));
            return EXIT_FAILURE;
        }
    }
}