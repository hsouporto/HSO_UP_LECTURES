#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <fcntl.h>


#define BUF_SIZE 128


int main(int argc, char *argv[]){
    char *myfifo = "/tmp/myfifo";
    int rv = mkfifo(myfifo, 0666);
    if (rv == -1){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    int fd = open(myfifo, O_WRONLY);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1){
        char text[BUF_SIZE];
        fgets(text, BUF_SIZE, stdin);
        write(fd, text, strlen(text) + 1);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}