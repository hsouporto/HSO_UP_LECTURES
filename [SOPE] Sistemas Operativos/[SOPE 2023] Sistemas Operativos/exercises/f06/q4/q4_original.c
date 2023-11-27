#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// STATUS: TESTED

#define BUFFERSIZE 1024

#define CHANNEL0 0
#define CHANNEL1 1

#define DATA0 "In every walk with nature..."
#define DATA1 "...one receives far more than he seeks."

/* by John Muir */
int main(int argc, char *argv[]){
    int sockets[2];
    char buffer[BUFFERSIZE];
    pid_t pid;

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

        // try to read something from socket (blocking)
        if (read(sockets[CHANNEL1], buffer, sizeof(buffer)) < 0)
            perror("reading stream message");

        printf("message from %d-->%s\n", getppid(), buffer);

        // write to the socket different message (blocking)
        if (write(sockets[CHANNEL1], DATA1, sizeof(DATA1)) < 0)
            perror("writing stream message");

        // we completed our round
        close(sockets[CHANNEL1]);

        /* leave gracefully */
        return EXIT_SUCCESS;
    }
    else{
        /* this is the parent */
        close(sockets[CHANNEL1]);

        // try to write something to socket (blocking)
        if (write(sockets[CHANNEL0], DATA0, sizeof(DATA0)) < 0)
            perror("writing stream message");

        // try to receive something  (blocking)
        if (read(sockets[CHANNEL0], buffer, sizeof(buffer)) < 0)
            perror("reading stream message");

        // print the received message
        printf("message from %d-->%s\n", pid, buffer);

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