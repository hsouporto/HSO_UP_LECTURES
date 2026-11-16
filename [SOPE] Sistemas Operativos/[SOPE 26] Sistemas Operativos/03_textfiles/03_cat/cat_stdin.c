
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    size_t n_read;

    /* Read from stdin and write to stdout in blocks */
    while ((n_read = fread(buffer, 1, sizeof buffer, stdin)) > 0) {
        fwrite(buffer, 1, n_read, stdout);
    }

    if (ferror(stdin)) {
        perror("Error reading stdin");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}