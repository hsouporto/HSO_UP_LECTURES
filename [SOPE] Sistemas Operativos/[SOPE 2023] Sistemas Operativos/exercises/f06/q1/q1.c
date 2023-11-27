#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define LINESIZE 256

int main(int argc, char *argv[]){
    int nbytes; 
    int fd[2];                          // array to attarcat to the pipe

    pid_t pid;
    char line[LINESIZE];

    if (pipe(fd) < 0){                  // try to attach the pipe
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){            // try to fork the process
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    else if (pid > 0){                          // paper executions
        /* parent */
        close(fd[READ_END]);                    // close the pipe
        printf("Parent process with pid %d\n", getpid());
        printf("Messaging the child process (pid %d):\n", pid);

        snprintf(line, LINESIZE, "Hello! I’m your parent pid %d!\n", getpid()); 
        //Composes a string with the same text that would be printed if format was
        //used on printf, but instead of being printed, the content is stored as a C 
        //string in the buffer pointed by s (taking n as the maximum buffer capacity to fill).

        
        // try to write the content to the pipe
        if ((nbytes = write(fd[WRITE_END], line, strlen(line))) < 0){
            fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
        }
        close(fd[WRITE_END]);

        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0){
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
        }
        exit(EXIT_SUCCESS);
    }
    else{
        /* child */
        close(fd[WRITE_END]);                   // close - delete the descriptor
        printf("Child process with pid %d\n", getpid());
        printf("Receiving message from parent (pid %d):\n", getppid());

        // try to read the contest rom the pype (return number of bytes read)
        if ((nbytes = read(fd[READ_END], line, LINESIZE)) < 0){
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }
        close(fd[READ_END]);

        /* write message from parent */
        write(STDOUT_FILENO, line, nbytes);

        /* exit gracefully */
        exit(EXIT_SUCCESS);
    }
}
