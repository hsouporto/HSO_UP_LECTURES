#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//STATUS: TESTED
// NOTE: USE as : ./q3_sol "cat test.txt | grep HI | wc -l"

#define PIPE_READ 0
#define PIPE_WRITE 1


// parse the string command (unique without pipe)
char **parse_string(char *cmd_string){

    char **res = NULL;
    char *p = strtok(cmd_string, " ");
    int n_spaces = 0, i;

    /* split string and append tokens to 'res' */
    while (p){
        res = realloc(res, sizeof(char *) * ++n_spaces);

        if (res == NULL)
            exit(-1); /* memory allocation failed */

        res[n_spaces - 1] = p;

        p = strtok(NULL, " ");
    }

    /* realloc one extra element for the last NULL */
    res = realloc(res, sizeof(char *) * (n_spaces + 1));
    res[n_spaces] = 0;

    /* print the result for Debug */
    for (i = 0; i < (n_spaces + 1); ++i)
        printf("res[%d] = %s\n", i, res[i]);

    return res;
}

// execute command
int run_cmd(char **args){
    if (execvp(args[0], args) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_FAILURE);

}


// this will be called recursevely
void next_pipe(char *piped_cmds) {
    // split the comnand piece up to "|" symbol
    char *curr_piped_cmd = strtok(piped_cmds, "|");

    // get the remainder list of piped commands, e.g., `grep printf | wc -l`
    char *next_piped_cmds = strtok(NULL, "");

    if (next_piped_cmds != NULL) {
        // if there is more piped commands, then create a pipe
        int pipe_fds[2];
        if (pipe(pipe_fds) == -1) {
            fprintf(stderr, "Failed to create pipe: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        // fork
        pid_t pid;
        if ((pid = fork()) == -1) { // error
            fprintf(stderr, "Failed to fork: %s", strerror(errno));
            exit(EXIT_FAILURE);

        } else if (pid > 0) { // parent process remanider | tokens

            // close unused pipe end
            close(pipe_fds[PIPE_WRITE]);

            // set stdin to referece the pipe's read end
            dup2(pipe_fds[PIPE_READ], STDIN_FILENO);
            close(pipe_fds[PIPE_READ]);

            // recursevely split the remainder command and call
            next_pipe(next_piped_cmds);

        } else if (pid == 0) {      // child executes current parsed | command

            // close unused pipe end
            close(pipe_fds[PIPE_READ]);
            
            // make the stdout file descriptor point to pipes write end
            dup2(pipe_fds[PIPE_WRITE], STDOUT_FILENO);
            close(pipe_fds[PIPE_WRITE]);

            // parse and run
            char ** cmd = parse_string(curr_piped_cmd);
            run_cmd(cmd);
        }

    } else {
        // simply execute the last command of the input string (no more pipes)
        char ** cmd = parse_string(curr_piped_cmd);
        run_cmd(cmd);
    }
}


int main(int argc, char const *argv[]) {
    // sanyty checks
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"cmd_1 | cmd_2 -a | ... | cmd_n\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // copy original to avoid strange things
    char *cmd = malloc(sizeof(char) * (strlen(argv[1]) + 1));
    if (cmd == NULL) {
        fprintf(stderr, "Failed to allocate memory for command string\n");
        exit(EXIT_FAILURE);
    }

    strcpy(cmd, argv[1]);

    // 
    next_pipe(cmd);
    return 0;
}

