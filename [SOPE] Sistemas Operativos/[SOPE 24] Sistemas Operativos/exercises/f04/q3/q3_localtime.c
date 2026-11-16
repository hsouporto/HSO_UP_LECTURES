#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s file1 [file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat info;
    off_t total_size = 0;
    blkcnt_t total_blocks = 0;

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &info) == -1) {
            fprintf(stderr, "%s: Can’t stat %s\n", argv[0], argv[i]);
            continue; // Skip to the next file if there's an error
        }

        // Accumulate total size and total disk blocks
        total_size += info.st_size;
        total_blocks += info.st_blocks;

        // Convert human readable
        char timebuf[64];
        struct tm *tm_info = localtime(&info.st_mtime); // From stat mtime convert to readable local time
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);

        // Print file-specific information
        printf("%s - size: %ld bytes, disk blocks: %ld, last modified: %s, owner UID: %d\n",
               argv[i], (long)info.st_size, (long)info.st_blocks, timebuf, info.st_uid);
    }

    // Print total size and total blocks
    printf("Total size: %ld bytes, Total disk blocks: %ld\n", (long)total_size, (long)total_blocks);

    exit(EXIT_SUCCESS);

}

