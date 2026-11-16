#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    if (access(filename, F_OK) == 0) {
        struct timeval times[2];
        gettimeofday(&times[0], NULL);
        times[1] = times[0];
        
        if (utimes(filename, times) != 0) {
            perror("Error updating file times");
            exit(EXIT_FAILURE);
        }

        
    } else {

        mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;  
        int fd = open(filename, O_CREAT | O_WRONLY, perms);
        
        if (fd == -1) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
        
        close(fd);
    }

    return EXIT_SUCCESS;
}