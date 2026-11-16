#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    // Check arguments
    if (argc != 2) {
        printf("ERROR -> Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Allocate memory and copy the input string
    char *str = malloc(strlen(argv[1]) + 1);

    if (str == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    strcpy(str, argv[1]);

    // Split the string into words
    char *word = strtok(str, " \t\n");

    while (word != NULL) {
        printf("%s\n", word);
        word = strtok(NULL, " \t\n");
    }

    // Free allocated memory
    free(str);

    return EXIT_SUCCESS;
}