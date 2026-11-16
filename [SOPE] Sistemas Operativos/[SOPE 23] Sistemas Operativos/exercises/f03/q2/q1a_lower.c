#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// STATUS: TESTED

// macro function
#define my_tolower(a) (((a) <= 90 && ((a) >= 65)) ? (a + 32) : (a))


int main(int argc, char const *argv[]){
     
    // test if number of arguments is correct 
    if (argc < 2){
        printf("ERROR -> Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // maintain original, alternatively use malloc and strcopy
    char *str = (char*) argv[1];
    #ifdef DEBUG
    printf("DEBUG: string length = %d\n", (int) strlen(str));
    #endif

    // iterate over the string chars
    for (size_t i = 0; i < strlen(str); i++){
       // str[i] = tolower(str[i]);               // convert char to lower (alternatively you can do your own tolower (check ascci table))
        str[i] = my_tolower(str[i]);              // alternative implementation using an macro
    }

    printf("Converted String: %s\n", str);
    return EXIT_SUCCESS;
}