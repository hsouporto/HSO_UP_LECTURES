#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define HISTORY_FILE ".command_history"

void add_to_history(const char *command) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file) {
        fprintf(file, "%s\n", command);
        fclose(file);
    } else {
        perror("fopen");
    }
}




void handle_myhistory(const char *arg) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
  
        if (arg == NULL) {
            fprintf(stderr, "Usage: myhistory <n>\n");
            exit(EXIT_FAILURE);
        }
        execlp("tail", "tail", "-n", arg, HISTORY_FILE, (char *)0);
        /* If execlp fails */
        perror("execlp");
        exit(EXIT_FAILURE);
    }


    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    for (;;) {
        /* Give prompt, read command, and null terminate it */
        fprintf(stdout, "$ ");
        char buf[1024];
        char* command = fgets(buf, sizeof(buf), stdin);

        if (command == NULL) {
            break; // Exit on EOF (Ctrl+D)
        }

        /* Remove the trailing newline character */
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        /* Ignore empty commands */
        if (strlen(buf) == 0) {
            continue;
        }

        /* Add the command to the history */
        add_to_history(buf);

       
        if (strncmp(buf, "myhistory", 9) == 0) {
            char *arg = strtok(buf + 9, " ");
            handle_myhistory(arg);
            continue;
        }

        /* Call fork and check return value */
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
    
            execlp(buf, buf, (char *)0);
            /* If execlp fails */
            perror("execlp");
            exit(EXIT_FAILURE);
        }

        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
