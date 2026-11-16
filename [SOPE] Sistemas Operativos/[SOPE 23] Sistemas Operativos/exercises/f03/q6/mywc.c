#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// STATUS: TESTED

#define N_CHARS 1
#define N_WORDS 2
#define N_LINES 3


// Note, this is no to effience, you should use Fread
unsigned long count_file(const char *fname, int mode){

    char ch;
    unsigned long count=0;
    
    // try open file in read mode
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        return 0;

    
    while ((ch = fgetc(fp)) != EOF) {
        // decode de mode
        switch (mode){
            case N_CHARS:
                    count++;
                break;

            case N_LINES:
                      if (ch == '\n' || ch == '\0')count++;
                break;
            
            case N_WORDS:
                      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')count++;
                break;

            default:
                return 0;
                break;
        }
    }

    // close file
    fclose(fp);

    return count;
}




int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2 || argc > 3) {
        printf("ERROR -> usage: %s <filename> or %s <-c or -w> <filename>  \n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    // by default
    int mode = N_CHARS;

    // test number of arguments
    if(argc == 3){
        
        // decode the 2 argument
        if (strcmp("-c", argv[1]) == 0) {
            mode = N_CHARS;
        }
        else if(strcmp("-w", argv[1]) == 0) {
            mode = N_WORDS;
            }
        else if(strcmp("-l", argv[1]) == 0) {
             mode = N_LINES;
            }
    }

    unsigned long count=0;

    // handle positional arguments 
    if(argc == 2)
       count = count_file(argv[1], mode);
    else
       count = count_file(argv[2], mode);


    // present our data accordingly
    switch (mode){
    case N_CHARS:
            printf("Files has %lu CHARS \n\r", count);

        break;

    case N_WORDS:
            printf("Files has %lu WORDS \n\r", count);
        break;

    case N_LINES:
            printf("Files has %lu LINES \n\r", count);
        break;
    default:

        break;
    }   


    return EXIT_SUCCESS;

}