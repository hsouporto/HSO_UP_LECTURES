#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// STATUS: TESTED

int main(int argc, char *argv[]){
    pid_t pid;
    /* fork a child process */
    if ((pid = fork()) == -1){
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0){
        /* child process */
        if (execlp(argv[1], argv[1], NULL) == -1){
            perror("execlp");
            return EXIT_FAILURE;
        }
        printf("Child Executed\n");
        return EXIT_SUCCESS;
    }
    else{
        /* parent process */
        if (waitpid(pid, NULL, 0) == -1){       // parent wait child to terminate (waitpid by default blocks)
            perror("waitpid");
            return EXIT_FAILURE;
        }
        printf("child exited\n");
    }
    return EXIT_SUCCESS;
}

/* BRIEF EXPLAINATION

* The child process (0) is only executed when the execlp call gives error. 
* Otherwise: the child process is totaly redraw by executing execlp call

* If EXECLP sucess, will not execute the code specified in the file \n 
* but those dictated by the command with the porcess totall redraw while manintaining same PID

* Parent waits for child to end execution, waitpid 


Some Stackoverflow explaination: 

The exec family of functions shall replace the current process image with a new process image.
The new image shall be constructed from a regular, executable file called the new process image file.
There shall be no return from a successful exec, because the calling process image is overlaid by 
the new process image.

If one of the exec functions returns to the calling process image, 
an error has occurred; the return value shall be -1, and errno shall be set to 
indicate the error.

Source: https://stackoverflow.com/questions/7156338/fork-and-execlp

#include<stdio.h>
main()
{
    int pid,j=10,fd;
    pid=fork();
    if(pid==0)
    {
        printf("\nI am the child\n");
        execlp("/bin/ls","ls",NULL);
        printf("\nStill I am the child\n");

    }
    else if (pid > 0)
    {
        printf("\n I am the parent\n");
        wait();
    } 
}
// The "Still Im the child" is not printed

*/

