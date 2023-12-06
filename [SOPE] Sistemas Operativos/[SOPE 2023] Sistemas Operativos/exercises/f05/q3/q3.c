#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// STATUS: TESTED

int main(int argc, char *argv[]){
    pid_t pid;
    int value = 0;

    if ((pid = fork()) == -1){
        perror("fork");
        return EXIT_FAILURE;
    }

    else if (pid == 0){
        /* child process */
        value = 1;
        printf("CHILD: value = %d, addr = %p\n", value, &value);
        
        return EXIT_SUCCESS;
    
    }else{
        /* parent process */
        if (waitpid(pid, NULL, 0) == -1){       // parent waits child (pid=0) to finish
            perror("wait");
            return EXIT_FAILURE;
        }
        printf("PARENT: value = %d, addr = %p\n", value, &value);
        return EXIT_SUCCESS;
    }

}
/* BRIEF EXPLAINATION

Just as recap on what is inherited by child processs after fork:
- Real and effective user and group IDs
- Environment settings
- Signal handling settings
- Attached shared memory segments
- Memory mapped segments
- Process group ID
- Current working directory
- File mode creation mask
- Controlling terminal
nice value

Brief explanation:

* there are created two copies of value (physical and virtual memory), inherithed original value, 

* only child is changing is value, parent copy maintais original value

* address are the same!, well fork creates a copy in the virtual memory space, with same address

* There is a disconnect between physical memory and the virtual address space of a process.

* So, while it may seem that two processes have the same address for a variable, that's 
only the virtual address acting.

* Parent waits for child (0) to end execution using wait (pid, Null, 0)

*/