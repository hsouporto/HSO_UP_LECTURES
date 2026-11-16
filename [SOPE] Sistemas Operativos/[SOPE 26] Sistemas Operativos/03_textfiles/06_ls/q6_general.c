#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
int main(int argc, char **argv) {
    int len;
    if (argc != 2) {
        printf("usage: %s dirname\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    DIR *q = opendir(argv[1]);
    if (q == NULL){
        printf("cannot open directory: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("%s/\n", argv[1]);
    struct dirent *p = readdir(q);
    while (p != NULL){
        printf("\t%s\n", p->d_name);
        p = readdir(q);
    }
    
    closedir(q);
    exit(EXIT_SUCCESS);
}