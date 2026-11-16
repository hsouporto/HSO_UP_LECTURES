#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_HISTORY_SIZE 10

char* history[MAX_HISTORY_SIZE];
int history_index = 0;

void execute_command(char* command) {
    // Split the command into tokens
    char* args[MAX_INPUT_LENGTH];
    int arg_count = 0;

    char* token = strtok(command, " ");
    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    // Execute the command
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);

        // Store the command in history
        if (history_index < MAX_HISTORY_SIZE) {
            history[history_index] = strdup(command);
            history_index++;
        } else {
            // Remove the oldest command to make space for the new one
            free(history[0]);
            for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
                history[i] = history[i + 1];
            }
            history[MAX_HISTORY_SIZE - 1] = strdup(command);
        }
    } else {
        perror("Error forking process");
    }
}

void print_history(int n) {
    int start = (history_index > n) ? history_index - n : 0;
    for (int i = start; i < history_index; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        // Get user input
        printf("Enter command: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle Ctrl+D (EOF)
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Check for the myhistory command
        if (strncmp(input, "myhistory", 9) == 0) {
            int n;
            if (sscanf(input + 9, "%d", &n) == 1) {
                print_history(n);
            } else {
                printf("Invalid myhistory command\n");
            }
        } else {
            // Execute the command
            execute_command(input);
        }
    }

    // Free history entries
    for (int i = 0; i < history_index; i++) {
        free(history[i]);
    }

    return 0;
}
