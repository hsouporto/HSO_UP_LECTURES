#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: backwards filename\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("error: cannot open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // set to the end of of file file
    off_t position = lseek(fd, 0, SEEK_END);
    if (position == -1) {
        printf("error: could not seek in %s\n", argv[1]);
        close(fd);
        exit(EXIT_FAILURE);
    }

    char ch;
    while (position > 0) {
        position = lseek(fd, -1, SEEK_CUR); // Move one back
        if (read(fd, &ch, 1) == 1) {
            write(STDOUT_FILENO, &ch, 1); // Write to stdout
        }
        position = lseek(fd, -1, SEEK_CUR); // Move character back
    }

    close(fd);
    exit(EXIT_SUCCESS);
}


// gcc -Wall backwards.c -o backwards



