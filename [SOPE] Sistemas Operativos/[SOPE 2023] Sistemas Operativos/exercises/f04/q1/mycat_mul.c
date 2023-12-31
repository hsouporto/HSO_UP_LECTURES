#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// STATUS: TESTED


#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2) {
        printf("usage: cat filename\n");
        return EXIT_FAILURE;
    }

    /* loop in the number of files and argv */
    int n_files = argc;
    char buffer[BUFFER_SIZE];
    int bytesin;

    for (int i=1; i <n_files; i++){
        /* check if file can be opened and is readable */
        int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                printf("error: cannot open %s\n", argv[1]);
                continue;
            }

        /* print the contents in blocks */
        while ((bytesin = read(fd, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytesin);
        }
        /* close file */
        close(fd); 
    }  
    return EXIT_SUCCESS;
}

