#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: cat filename1 [filename2 ...]\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            printf("error: cannot open %s\n", argv[i]);
            continue; 
        }

        int nbytes;
        while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, nbytes);
        }

        close(fd);
    }

    exit(EXIT_SUCCESS);
}