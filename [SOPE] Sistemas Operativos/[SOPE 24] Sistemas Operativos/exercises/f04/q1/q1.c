#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: cat filename\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("error: cannot open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int nbytes = read(fd, buffer, BUFFER_SIZE);
    
    while (nbytes > 0) {
        write(STDOUT_FILENO, buffer, nbytes);
        nbytes = read(fd, buffer, BUFFER_SIZE);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
