#include <stdio.h>
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
    if (argc < 2 || argc % 2 != 0) {
        printf("Usage: %s findword-replword [findword-replword ...]\n", argv[0]);
        return 1;
    }

    char text[MAX_LENGTH];
    while (fgets(text, MAX_LENGTH, stdin) != NULL) {
        for (int i = 1; i < argc; i += 2) {
            char *find_word = strtok(argv[i], "-");
            char *repl_word = strtok(argv[i + 1], "-");
            findAndReplace(find_word, repl_word, text);
            strcpy(text, "");
        }
    }

    return 0;
}