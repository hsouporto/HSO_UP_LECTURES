#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// STATUS: TESTED
// NOTES: check book for undestand pipes ends

#define READ_END 0
#define WRITE_END 1
#define LINESIZE 256

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage: ./prog file\n\r");
        return EXIT_FAILURE;
    }

    int fd_pipe[2];   // array to attach to the pipe
    pid_t pid;

    // try to attach the pipe
    if (pipe(fd_pipe) < 0){                  
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    // try to fork the process
    if ((pid = fork()) < 0){            
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    // Parent zone
    if (pid > 0){                   
        /* parent */
        /* close pipe reading end */
        close(fd_pipe[READ_END]);

        //printf("Parent process with pid %d\n", getpid());
        //printf("Lets try to read the file (pid %d):\n", pid);

        // local buffer to read
        char buffer[LINESIZE];
        printf("File to opened %s\n", argv[1]);
        
        // try to open the file
        int fd_file = open(argv[1], O_RDONLY);
        if (fd_file == -1){
            printf("Error reading file\n\r");
            close(fd_pipe[WRITE_END]);
            return EXIT_FAILURE;
        }
        
        // temporaty counters
        int n_bytesread; 

        // lets try to read and send it 
        while ((n_bytesread = read(fd_file, buffer, LINESIZE)) > 0){
            // try to write to the pipe
            printf("Trying to Send (Parent)\n\r");
            if (write(fd_pipe[WRITE_END], buffer, n_bytesread) == -1){
                // if we have an error proceed accordinly
                fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
                close(fd_pipe[WRITE_END]);
                close(fd_file);
                return EXIT_FAILURE;
            }

        
        } 
        // catch the error on opening file
        if (n_bytesread == -1) { // handle errors while reading file
            fprintf(stderr, "Error while reading '%s'. Cause: %s\n", argv[1], strerror(errno));
            close(fd_file);
            close(fd_pipe[WRITE_END]);
            return EXIT_FAILURE;
        }

        /* close pipe and file descriptor */
        close(fd_pipe[WRITE_END]);
        close(fd_file);
        
        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0) {    // block on child to complete
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;

    } // end parent


    // child zone
    else{
        /* child */

        // close the unused pipe end
        close(fd_pipe[WRITE_END]);                             
        //printf("Child process with pid %d\n", getpid());
        //printf("Receiving message from parent (pid %d):\n", getppid());

        // try to read the content of the pype 
        char buffer[LINESIZE];
        int n_bytesread = 0;

        printf("Trying to Receive (Child)\n");
        while ((n_bytesread = read(fd_pipe[READ_END], buffer, LINESIZE)) > 0) {
            printf("Child received: \n");
            write(STDOUT_FILENO, buffer, n_bytesread); // write to STDOUT
        }

        if (n_bytesread == -1) { // handle errors while reading from pipe
            fprintf(stderr, "Error while reading from pipe. Cause: %s\n", strerror(errno));
            close(fd_pipe[READ_END]);
            return EXIT_FAILURE;
        }

          /* close pipe */
        close(fd_pipe[READ_END]);
        return EXIT_SUCCESS;
  
    }// end of child
}

/* BRIEF EXPLAINATION

* fd_pipe[0] for reading
* fd_pipe[1] for writing

Each process should close the pipe, to signal the kernel
Note kernel knows who has the references for the pipe

NOTES: The first thing to do in both process is to close the pipe interface 

*/