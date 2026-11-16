
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Reads one line from fd into line.
 * Returns the number of characters read,
 * 0 at EOF, or -1 on error.
 */
int readln(int fd, char *line, int maxlen) {
    int n = 0;
    char c;
    ssize_t r;

    while (n < maxlen) {
        r = read(fd, &c, 1);

        if (r == -1)
            return -1;

        if (r == 0)
            break;  /* EOF */

        line[n++] = c;

        if (c == '\n')
            break;
    }

    return n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    char line[1024];
    int n;
    int line_number = 1;

    while ((n = readln(fd, line, sizeof line)) > 0) {
        printf("%4d ", line_number++);
        fwrite(line, 1, n, stdout);
    }

    if (n == -1) {
        perror("readln");
        close(fd);
        return EXIT_FAILURE;
    }

    if (close(fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}