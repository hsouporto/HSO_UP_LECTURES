#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_HISTORY_SIZE 10

char* history[MAX_HISTORY_SIZE];
int historyCount = 0;

void executeCommand(char *command) {
    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char *token;
        char *args[MAX_COMMAND_LENGTH];
        int argCount = 0;

        // Tokenize the command string
        token = strtok(command, " ");
        while (token != NULL) {
            args[argCount++] = token;
            token = strtok(NULL, " ");
        }

        // Null-terminate the argument list
        args[argCount] = NULL;

        // Execute the command
        execvp(args[0], args);

        // execvp only returns if there is an error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Wait for the child to complete
        wait(NULL);

        // Store the command in history
        if (historyCount < MAX_HISTORY_SIZE) {
            history[historyCount] = strdup(command);
            historyCount++;
        } else {
            // Shift the history to make space for the new command
            free(history[0]);
            for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
                history[i] = history[i + 1];
            }
            history[MAX_HISTORY_SIZE - 1] = strdup(command);
        }
    }
}

void printHistory(int n) {
    if (n > historyCount) {
        n = historyCount;
    }

    for (int i = historyCount - n; i < historyCount; i++) {
        printf("%s\n", history[i]);
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from input
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "myhistory") == 0) {
            // Special command to print history
            int n;
            printf("Enter the number of commands to display: ");
            scanf("%d", &n);
            getchar(); // Consume the newline character left by scanf
            printHistory(n);
        } else {
            // Execute the command
            executeCommand(input);
        }
    }

    return 0;
}