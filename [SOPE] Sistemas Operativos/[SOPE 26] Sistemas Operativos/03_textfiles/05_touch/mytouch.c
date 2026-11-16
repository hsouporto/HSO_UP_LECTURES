
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Check whether the file exists */
    if (access(argv[1], F_OK) == 0) {
        /* File exists: update its modification time */
        if (utime(argv[1], NULL) == -1) {
            perror("utime");
            return EXIT_FAILURE;
        }
        
    } else {
        /* File does not exist: create it with permissions 644 */
        mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

        int fd = open(argv[1], O_CREAT | O_WRONLY | O_EXCL, perms);
        if (fd == -1) {
            perror("open");
            return EXIT_FAILURE;
        }

        if (close(fd) == -1) {
            perror("close");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}