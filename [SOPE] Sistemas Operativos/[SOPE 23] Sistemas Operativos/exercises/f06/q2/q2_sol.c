#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h> 

// STATUS: FINISH FINAL BLOCK ON RECEIVE
// NOTES: THE Reading operation by default is blocking, however we can define a timout to release from read operation

#define BUFFERSIZE 1024

#define CHANNEL0 0
#define CHANNEL1 1




int main(int argc, char *argv[]){
    int sockets[2];
    char buffer[BUFFERSIZE];
    pid_t pid;

    // LINUX TIMOUT RECEIVE (CHECK)
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    //setsockopt(sockets, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    // create a pair of connected sockets
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0){
        perror("opening stream socket pair");
        exit(1);
    }

    // try to fork
    if ((pid = fork()) < 0){
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0){
        /* this is the child */
        close(sockets[CHANNEL0]);       // close the socked 
        int n_bytesread=0;
       
        // try to read something from socket (blocking)
        while ((n_bytesread= read(sockets[CHANNEL1], buffer, sizeof(buffer))) > 0){
            write(STDOUT_FILENO, buffer, n_bytesread); // write to STDOUT

            // convert and send it back
            for (int i=0; i < n_bytesread; i++) buffer[i] = toupper(buffer[i]);

            if (write(sockets[CHANNEL1], buffer, strlen(buffer)) < 0)
            perror("writing stream message");

        }
            
        // we completed our round
        close(sockets[CHANNEL1]);

        /* leave gracefully */
        return EXIT_SUCCESS;

    }
    else{
        /* this is the parent */
        close(sockets[CHANNEL1]);

        // try to read file
        printf("File to opened %s\n", argv[1]);
        
        int fd_file = open(argv[1], O_RDONLY);
        if (fd_file == -1){
            printf("Error reading file\n\r");
            close(sockets[CHANNEL1]);
            return EXIT_FAILURE;
        }

        
        // read the file and send
        int n_bytesread; 
        while ((n_bytesread = read(fd_file, buffer, BUFFERSIZE)) > 0){
            // try to write the block to socket (blocking)
            if (write(sockets[CHANNEL0], buffer, n_bytesread) < 0){

                // if we have an error proceed accordinly
                fprintf(stderr, "Unable to write to socket: %s\n", strerror(errno));
                close(sockets[CHANNEL1]);
                close(fd_file);
                return EXIT_FAILURE;
            }
        }

        // now receive it
        printf("Trying to Receive Back (Parent)\n");
        while ((n_bytesread = read(sockets[CHANNEL0], buffer, sizeof(buffer))) > 0) {
            printf("Received back (Parent): \n");
            // dump it to stdout
            write(STDOUT_FILENO, buffer, n_bytesread); // write to STDOUT
        }

        // close channel
        close(sockets[CHANNEL0]);

        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0){
            perror("did not catch child exiting");
            return EXIT_FAILURE;
        }
        
        return EXIT_SUCCESS;
    }
}