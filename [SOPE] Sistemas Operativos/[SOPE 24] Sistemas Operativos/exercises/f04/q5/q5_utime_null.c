#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "sys/stat.h"

int main(int argc, char *argv[]){
    if (access(argv[1], F_OK) == 0){
        /* file exists - insert code to change last access date */
        utimes(argv[1], NULL);
    }
    else{
        /* file does not exist - create it with given access permissions */
        mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        int fd = open(argv[1], O_CREAT | O_WRONLY, perms);
        close(fd);
    }
    exit(EXIT_SUCCESS);
}