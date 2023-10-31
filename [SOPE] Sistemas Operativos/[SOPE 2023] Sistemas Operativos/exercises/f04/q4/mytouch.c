#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>

// STATUS: TESTED

int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc != 2) {
        printf("usage: touch filename\n");
        return EXIT_FAILURE;
    }

    FILE *fptr = fopen(argv[1], "rb+"); // tries to create file, fail execute twice
    if(fptr == NULL){ //if file does not exist, create it
        fptr = fopen(argv[1], "wb");

        // alternatively
        //open(argv[1], O_RDWR|O_CREAT, 0644);
    }

    // update time of modification
    utime(argv[1], NULL);


    return EXIT_SUCCESS;
}

