#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// STATUS: TESTED

int main(int argc, char const *argv[]){

    // sanity checks
    if (argc != 3){
        printf("ERROR -> Usage: %s <string> <substring>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // allocate new char arrays and copy them (plus one to add \0)
    char *str = malloc(strlen(argv[1])  * sizeof(char));
    strcpy(str, argv[1]);

    // copy first string
    char *substr = malloc(strlen(argv[2]) * sizeof(char));
    strcpy(substr, argv[2]);

    // auxliary pointer to maintain str original
    char *aux_str = str;

    // count number of ocurrences
    unsigned int n_occur = 0;
    
    // while strstr != NULLL, a math is found
    while ((aux_str=strstr(aux_str, substr)) != NULL) { // loop ultil end, if found
        n_occur++;

        aux_str ++;                 // this 
        //aux_str +=strlen(substr);   // vs this
        #ifdef DEBUBG
        printf("DEBUG: aux = '%s'\n", aux_str);
        #endif
    }

    printf("Num of ocurrences: %u\n", n_occur);

    // free the mallocs
    free(str);
    free(substr);

    return EXIT_SUCCESS;
}
