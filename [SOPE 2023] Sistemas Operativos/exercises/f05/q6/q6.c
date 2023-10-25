#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// STATUS: TESTED

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

            printf("Command executed\n");
            // ivoque te program   "ls  -l"     "ls" "ls" "-l" 
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

/* BRIEF EXPLAINATION

* execvp allows the execution of system call using as input an array of strings (this facilitates things)
* We just need to parse the input string fetched by fgets and convert tokens into a set array of strings 
and set last one to NULL and thats all

Be aware that stritok changes original string, perhaps strcpy should be used is want to reuse original!
*/

