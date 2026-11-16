#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "sys/stat.h"

// STATUS: TESTED

int main(int argc, char* argv[]) {
    if (argc != 3 ) {
        (void)fprintf(stderr, "usage: %s perms file\n", argv[0]);
    return EXIT_FAILURE;
    }

    int perms = atoi(argv[1]);
    int operms = perms % 10;
    perms = perms / 10;
    int gperms = perms % 10;
    perms = perms / 10;
    int uperms = perms;
    mode_t newperms = (mode_t)0;

    switch (uperms) {
        case 0: break;

        case 1: newperms |= S_IXUSR; break;
        
        case 2: newperms |= S_IWUSR; break;
        
        case 3: newperms |= S_IWUSR | S_IXUSR; break;

        case 4: newperms |= S_IRUSR; break;

        case 5: newperms |= S_IRUSR | S_IXUSR; break;

        case 6: newperms |= S_IRUSR | S_IWUSR; break;
        
        case 7: newperms |= S_IRUSR | S_IWUSR | S_IXUSR; break;

        default:
            (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
            return EXIT_FAILURE;
    }


    switch (gperms) {
        case 0: break; /* ... */

        case 1: newperms |= S_IXGRP; break;
        
        case 2: newperms |= S_IWGRP; break;
        
        case 3: newperms |= S_IWGRP | S_IXGRP; break;
        
        case 4: newperms |= S_IRUSR; break;

        case 5: newperms |= S_IRGRP | S_IXGRP; break;

        case 6: newperms |= S_IRGRP | S_IWGRP; break;
        
        case 7: newperms |= S_IRGRP | S_IWGRP | S_IXGRP; break;

        default:
        
            (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
            return EXIT_FAILURE;
    }

    switch (operms) {
        case 0: break;
        
        case 1: newperms |= S_IXOTH; break;
        
        case 2: newperms |= S_IWOTH; break;
        
        case 3: newperms |= S_IWOTH | S_IXOTH; break;
        
        case 4: newperms |= S_IROTH; break;
        
        case 5: newperms |= S_IROTH | S_IXOTH; break;
        
        case 6: newperms |= S_IRGRP | S_IWGRP; break; 
        
        case 7: newperms |= S_IRGRP | S_IWGRP | S_IXGRP; break; 

        default:
            (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
            return EXIT_FAILURE;
    }

    if (chmod(argv[2], newperms) == -1) {
        (void)fprintf(stderr, "%s: cannot chmod %s\n", argv[0], argv[2]);
        return EXIT_FAILURE;
    }

   
    return EXIT_SUCCESS;
}