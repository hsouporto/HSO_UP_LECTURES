#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// STATUS: TESTED
// NOTE: USING FREAD AND FWRITE

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2) {
        printf("ERROR -> usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* loop in the number of files and argv */
    char buffer[BUFFER_SIZE];
    FILE *fp= NULL;
    int n_read;

    for (int i=1; i <argc; i++){
        /* check if file can be opened and is readable */
        fp = fopen(argv[i], "rt");  // r for read only, t for text mode
            if (fp == NULL) {
                printf("error: cannot open %s\n", argv[i]);
                break;
            }

        /* print the contents in blocks */
         while ((n_read = fread(buffer, 1, sizeof buffer, fp)) > 0) // while we have something to read
            fwrite(buffer, 1, n_read, stdout);
            printf("%s\n", buffer);

        /* close file */
        fclose(fp); 
    }  
    return EXIT_SUCCESS;
}


