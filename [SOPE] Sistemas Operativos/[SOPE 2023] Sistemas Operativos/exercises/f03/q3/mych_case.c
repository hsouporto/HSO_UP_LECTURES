#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// STATUS: TESTED


#define ORIGINAL 1
#define TO_UPPER 2
#define TO_LOWER 3



// to convert the string, inplace
int convert_string(char* str, int mode){
    // leave string unchanged
    if (mode == ORIGINAL)
        return EXIT_SUCCESS;

    // iterate over the string
    for (int i = 0; i < strlen(str); i++){
        if (mode == TO_UPPER)
            str[i] = toupper(str[i]);
        else
            str[i] = tolower(str[i]);
    }

    return EXIT_SUCCESS;
}


int cat_file(const char *fname, int mode){
    #define BUFFER_SIZE 256
    char bufffer[BUFFER_SIZE];

    // try open file in read mode
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        return EXIT_FAILURE;

    // test the end of the file (feof) // alternatively you can use fread and check >0 bytes read
    while (!feof(fp)){ 
        // read the file text to the buffer  
        fread(bufffer, 1, BUFFER_SIZE, fp);

        // transform the string, if needed
        convert_string(bufffer, mode);

        // output the string
        printf("%s", bufffer);
    }

    // close file
    fclose(fp);

    return 0;
}




int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2 || argc > 3) {
        printf("ERROR -> usage: %s <filename> or %s <-u> <filename>  \n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    // by default
    int mode = ORIGINAL;

    // test number of arguments
    if(argc == 3){
        
        // decode the 2 argument
        if (strcmp("-u", argv[1]) == 0) {
            mode = TO_UPPER;
        }
        else if(strcmp("-l", argv[1]) == 0) {
            mode = TO_LOWER;
        }
        else {
            printf("Invalid argument, only -u or -l allowed\n\r");
            return EXIT_FAILURE;

        }
    }

    // handle positional arguments 
    if(argc == 2)
        cat_file(argv[1], mode);
    else
        cat_file(argv[2], mode);


return EXIT_SUCCESS;

}