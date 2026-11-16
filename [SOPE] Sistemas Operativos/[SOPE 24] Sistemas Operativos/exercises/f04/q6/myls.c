#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

// STATUS: TESTED: arrange output

int main (int argc, char** argv) {
    char buffer[512];
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;

    // test arguments
    if (argc != 2) {
        fprintf (stderr, "usage: %s dirname\n", argv[0]);
        return EXIT_FAILURE;
    }

    // try open directory
    mydir = opendir (argv[1]);
    if (mydir == NULL) {
        fprintf (stderr, "%s: Cannot open directory ’%s’\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    printf ("%s/\n", argv[1]);
    // iterate over the files listed
    while((myfile = readdir(mydir)) != NULL){
        sprintf(buffer, "%s/%s", argv[1], myfile->d_name);
        stat(buffer, &mystat);                 // get the status of file

        // permissions (change this to sprintf easy to format)
        printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
        printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
        printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
       
        // prinf sixe of file
        printf(" %10lld ",mystat.st_size);       // print size of file
        printf(" %10s ", myfile->d_name);    // print name

        // format the time
        printf(" %20s ", ctime(&mystat.st_mtime));
    }

    closedir(mydir);
    return EXIT_SUCCESS;
}

