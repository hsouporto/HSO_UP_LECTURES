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
    int fd = open(myfifo, O_RDONLY);

    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }


    while (1){
        char text[BUF_SIZE];
        read(fd, text, BUF_SIZE);
        printf("%s", text);
    }


    close(fd);
    exit(EXIT_SUCCESS);
}