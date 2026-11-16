#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// STATE: TESTED
 
#define MAX_STR_SIZE 64

int main(int argc, char* argv[]) {

    if(argc < 3){
        printf("ERROR -> Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // allocate new char arrays and copy them (plus one to add \0)
    char *str = malloc(strlen(argv[1]) * sizeof(char));
    strcpy(str, argv[1]);

    // copy first string
    char *substr = malloc(strlen(argv[2]) * sizeof(char));
    strcpy(substr, argv[2]);

    // NOTE: strstr expects bigger and small, but for sanity checks we do test len of strings
    if(strlen(str) >= strlen(substr)){
        if((strstr(str, substr)) != NULL)
            printf("String <%s> contains <%s>\r\n", str, substr);
        else
            printf("String <%s> dont contain <%s>\r\n", str, substr);

    // reverse test
    }else{
        if((strstr(substr, str)) != NULL)
            printf("String <%s> contains <%s>\r\n", substr, str);
        else
            printf("String <%s> dont contain <%s>\r\n", substr, str);

    }
   
    return EXIT_SUCCESS;
}