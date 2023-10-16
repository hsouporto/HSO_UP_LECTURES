#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// STATUS: TESTED

int cp(const char *src_filename, const char *dest_filename){
    // open both files with second + 
    FILE *fpsrc = fopen(src_filename, "r");
    FILE *fpdest = fopen(dest_filename, "w+"); // create if not exist


    // read the file in chuncks of 'BUFFER_SIZE' characters
    #define BUFFER_SIZE 256
    char buffer[BUFFER_SIZE] ;

    size_t count; // store number of characters read by 'fread'
    while ((count = fread(buffer, 1, BUFFER_SIZE, fpsrc))){
        // write to dest file
        fwrite(buffer, sizeof(char), count, fpdest);
        
    }

    return EXIT_SUCCESS;
}


int main(int argc, char const *argv[]){

    /* check if exactly one argument is present */
    if (argc < 3) {
        printf("ERROR -> usage: %s <source_filename> <dest_filename> \n\r", argv[0]);
        return EXIT_FAILURE;
    }

    // copy the files
    cp(argv[1], argv[2]);
    return EXIT_SUCCESS;

}
