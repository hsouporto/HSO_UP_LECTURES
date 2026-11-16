#include <stdio.h>
int main(int argc, char *argv[]){
    printf("# arguments = %d\n", argc - 1);
    printf("the command arguments are: %s\n", argv[0]);

    
    for (int i = 1; i < argc; i++)
        printf("argv[%d]=%s\n", i, argv[i]);
    return 0;
}