#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// STATUS: TESTED

#define BUFFERSIZE 128

// save the evoqued command and arguments to file
int append_file(char *args, char *filename){

    // open with append
    FILE *fd_file = fopen(filename, "a+");
    if(fd_file == NULL){
        perror("Error opening file.");
        return EXIT_FAILURE;
    }

    // print to the file
    fprintf(fd_file, "%s", args);

    // save to file
    fclose(fd_file);
    return EXIT_SUCCESS;

}

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


int main(int argc, char *argv[]){
    char buf[1024];
    char *command;
    pid_t pid;

    /* do this until you get a ^C or a ^D */
    for (;;){
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "$ ");

        // fetch the comand
        if ((command = fgets(buf, sizeof(buf), stdin)) == NULL)
            break;

        command[strlen(buf) - 1] = '\0';

        /* call fork and check return value */
        if ((pid = fork()) == -1){
            fprintf(stderr, "%s: can't fork command: %s\n", argv[0], strerror(errno));
            continue;
        }
        else if (pid == 0){ // child
            
            // parser the command string
            char ** args = parse_string(command);

            append_file(command, "cmd_history.txt" );
            // ivoque te program
            execvp(command, args);

            /* if I get here "execlp" failed */
            fprintf(stderr, "%s: couldn't exec %s: %s\n", argv[0], buf, strerror(errno));

            /* terminate with error to be caught by parent */
            exit(EXIT_FAILURE);
        }
        /* shell waits for command to finish before giving prompt again */
        if ((pid = waitpid(pid, NULL, 0)) < 0)
            fprintf(stderr, "%s: waitpid error: %s\n", argv[0], strerror(errno));
    }
    exit(EXIT_SUCCESS);
}



