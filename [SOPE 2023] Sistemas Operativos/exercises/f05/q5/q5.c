#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// STATUS: TESTED

int main(int argc, char *argv[]){
    char buf[1024];
    char *command;
    pid_t pid;
    /* do this until you get a ^C or a ^D */
    for (;;){
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "$ ");
        if ((command = fgets(buf, sizeof(buf), stdin)) == NULL)
            break;


        command[strlen(buf) - 1] = '\0';        // here set last to terminate 

        /* call fork and check return value */
        if ((pid = fork()) == -1){
            fprintf(stderr, "%s: can’t fork command: %s\n", argv[0], strerror(errno));
            continue;
        }

        else if (pid == 0){
            /* child */
            execlp(command, command, (char *)0);
            //execlp(command, command, "-l", (char *)0);
            

            /* if I get here "execlp" failed */
            fprintf(stderr, "%s: couldn’t exec %s: %s\n", argv[0], buf, strerror(errno));

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

A: Why can’t you execute commands with arguments, ls -l ou uname -n with this code
R: The variable name command is only "ls -l", and no command with this name exist

To work we should do the system call like:
execlp("ls", "ls", "-l", (char *)NULL);

* First is the argument of the program to be executed
* The remainder are the argument to be passed to the program

NOTE: Remeber the first argv[0] is the executable ./ls this should be used like this
NOTE: The end of the list should be set to NULL (dont forget to cast to char*) check man pages on execlp

*/