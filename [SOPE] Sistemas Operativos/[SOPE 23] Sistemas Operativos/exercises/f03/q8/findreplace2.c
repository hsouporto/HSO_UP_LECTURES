#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

void findAndReplace(char *find_word, char *repl_word, char *text) {
    char *pos = text;
    int find_word_len = strlen(find_word);
    int repl_word_len = strlen(repl_word);
    while ((pos = strstr(pos, find_word)) != NULL) {
        if ((pos == text || *(pos - 1) == ' ') && (pos[find_word_len] == ' ' || pos[find_word_len] == '\0' || pos[find_word_len] == ',' || pos[find_word_len] == '.' || pos[find_word_len] == '\n')) {
            printf("%.*s%s", (int)(pos - text), text, repl_word);
            text = pos + find_word_len;
        } else {
            printf("%.*s", (int)(pos - text + 1), text);
            text = pos + 1;
        }
        pos += find_word_len;
    }
    printf("%s", text);
}

int main(int argc, char *argv[]) {
    if (argc < 4 || (argc - 1) % 2 != 0) {
        printf("Usage: %s <file_name> findword1 replword1 [findword2 replword2] ...", argv[0]);
        return 1;
    }

    char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *text = (char *)malloc((file_size + 1) * sizeof(char));
    fread(text, file_size, 1, file);
    text[file_size] = '\0';

    fclose(file);

    for (int i = 2; i < argc; i += 2) {
        char *find_word = argv[i];
        char *repl_word = argv[i + 1];
        findAndReplace(find_word, repl_word, text);
        strcpy(text, "");
    }

    free(text);

    return 0;
}