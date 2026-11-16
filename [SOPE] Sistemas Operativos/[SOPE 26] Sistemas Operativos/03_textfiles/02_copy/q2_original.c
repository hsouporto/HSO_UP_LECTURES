#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    /* Check if you have the right number of arguments */
    if (argc != 3) {
        printf("usage: %s string1 string2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Compare argv[1] and argv[2] using lexicographic order */
    int result = strcmp(argv[1], argv[2]);
    if (result == 0) {
        printf("the strings are the same\n");
    } else if (result < 0) {
        printf("%s < %s\n", argv[1], argv[2]);
    } else {
        printf("%s > %s\n", argv[1], argv[2]);
    }

    /* Create a copy of argv[1] and argv[2] using strdup */
    char *p1 = strdup(argv[1]);
    char *p2 = strdup(argv[2]);
    printf("p1 holds: %s\n", p1);
    printf("p2 holds: %s\n", p2);

    /* Another way of copying strings using malloc and strcpy */
    char* p3 = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));
    char* p4 = (char*)malloc((strlen(argv[2]) + 1) * sizeof(char));
    strcpy(p3, argv[1]);
    strcpy(p4, argv[2]);
    printf("p3 holds: %s\n", p3);
    printf("p4 holds: %s\n", p4);

    /* Concatenate both strings, allocating space for:
       - all chars of argv[1]
       - all chars of argv[2]
       - the final '\0' */
    char* p5 = (char*)malloc((strlen(argv[1]) + strlen(argv[2]) + 1) * sizeof(char));
    strcpy(p5, p1);
    strcat(p5, p2);
    printf("p5 holds: %s\n", p5);

    /* Free allocated memory from malloc and strdup */
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);

    exit(EXIT_SUCCESS);
}
