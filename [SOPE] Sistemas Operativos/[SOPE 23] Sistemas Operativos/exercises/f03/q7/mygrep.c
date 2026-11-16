#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

void find_occurrences(char *string, FILE *file) {
    char line[MAX_LENGTH];
    int line_number = 1;

    while (fgets(line, MAX_LENGTH, file) != NULL) {
        char *position = line;
        int column = 1;
        while ((position = strstr(position, string)) != NULL) {
            printf("Found '%s' at Line %d, Column %d\n", string, line_number, (int)(position - line) + column);
            position++; // Move to the next character
            column = (int)(position - line) + 1;
        }
        line_number++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string_to_find> <filename>\n", argv[0]);
        return 1;
    }

    char *string_to_find = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    find_occurrences(string_to_find, file);
    fclose(file);
    return 0;
}