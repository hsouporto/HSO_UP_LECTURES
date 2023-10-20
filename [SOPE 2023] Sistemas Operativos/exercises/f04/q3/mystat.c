#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

//STATUS: TESTED


// function
void print_permissions_advanced(struct stat info){
    printf("--Advaced File Permissions--\n");
    printf("File Size: \t\t%lld bytes\n", info.st_size);
    printf("Number of Links: \t%d\n", info.st_nlink);
    printf("File inode: \t\t%llu\n", info.st_ino);

    printf("File Permissions: \t");
    printf( (S_ISDIR(info.st_mode)) ? "d" : "-");
    printf( (info.st_mode & S_IRUSR) ? "r" : "-");
    printf( (info.st_mode & S_IWUSR) ? "w" : "-");
    printf( (info.st_mode & S_IXUSR) ? "x" : "-");
    printf( (info.st_mode & S_IRGRP) ? "r" : "-");
    printf( (info.st_mode & S_IWGRP) ? "w" : "-");
    printf( (info.st_mode & S_IXGRP) ? "x" : "-");
    printf( (info.st_mode & S_IROTH) ? "r" : "-");
    printf( (info.st_mode & S_IWOTH) ? "w" : "-");
    printf( (info.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("The file %s a symbolic link\n", (S_ISLNK(info.st_mode)) ? "is" : "is not");

}


int main(int argc, char* argv[]) {
    struct stat info;
    
    // sanity checks
    if (argc < 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }

    // iterate over the files
    for (int i=1; i < argc; i++){

        // try to get status of file
        if (stat(argv[i], &info) == -1) {
            fprintf(stderr, "fsize: Can´t stat %s\n", argv[1]);
            continue;
        }
        
        // all when well, print stuff
        printf("%s size: %d bytes, disk_blocks: %d\n\r", argv[i], (int)info.st_size, (int)info.st_blocks);
        printf("Last modified time: %s", ctime(&info.st_mtime));
        printf("User ID %u\n\r", info.st_uid);
        
        // more advanced stuff to be shown
        print_permissions_advanced(info);



   





        
    }


    return EXIT_SUCCESS;
}