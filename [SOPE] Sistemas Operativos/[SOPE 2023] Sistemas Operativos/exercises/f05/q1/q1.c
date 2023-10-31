#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// STATUS: TESTED


int main(int argc, char *argv[]){
    /* fork a child process */
    fork();
    printf("Fork 01: my PID (Child) is PID: %d. My Parent is PID: %d\n", getpid(), getppid());

    /* fork another child process */
    fork();
    printf("Fork 02: my PID (Child) is PID: %d. My Parent is PID: %d\n", getpid(), getppid());

    /* and fork another */
    fork();
    printf("Fork 03: my PID (Child) is PID: %d. My Parent is PID: %d\n", getpid(), getppid());

    
    return EXIT_SUCCESS;
}


/* BRIEF EXPLAINATION

// From geekforgeeks
//fork ();   // Line 1
//fork ();   // Line 2
//fork ();   // Line 3

// 8 process are created
// the procees parent dont wait their child to end

//       L1         // There will be 1 child process  // created by line 1.
//     /     \     
//   L2      L2    // There will be 2 child processes //  created by line 2
//  /  \    /  \   
// L3  L3  L3  L3  // There will be 4 child processes // created by line 3

*/