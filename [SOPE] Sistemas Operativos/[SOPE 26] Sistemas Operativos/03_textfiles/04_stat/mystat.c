
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat info;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file...\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &info) == -1) {
            perror(argv[i]);
            continue;
        }

        printf("File: %s\n", argv[i]);
        printf("Last modification: %s", ctime(&info.st_mtime));
        printf("Owner UID: %u\n", (unsigned int)info.st_uid);
        printf("Size: %lld bytes\n\n",
               (long long)info.st_size);
        
    }

    return EXIT_SUCCESS;
}