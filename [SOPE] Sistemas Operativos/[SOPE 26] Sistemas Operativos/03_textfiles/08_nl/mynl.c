
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t capacity = 0;
    ssize_t nread;
    int line_number = 1;

    while ((nread = getline(&line, &capacity, fp)) != -1) {
        printf("%4d ", line_number++);
        fwrite(line, 1, (size_t)nread, stdout);
    }

    if (ferror(fp)) {
        perror("getline");
        free(line);
        fclose(fp);
        return EXIT_FAILURE;
    }

    free(line);

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}