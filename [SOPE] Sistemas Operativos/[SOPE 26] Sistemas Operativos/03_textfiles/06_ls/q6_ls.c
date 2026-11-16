#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

#define PATH_MAX 64

// Function to print file permissions in 'ls -l' style
void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");

    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

// List our entry
void list_entry(const char *path, const char *entry_name) {
    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry_name);

    struct stat file_stat;
    if (stat(full_path, &file_stat) == -1) {
        perror("stat");
        return;
    }

    // Show some permissions
    print_permissions(file_stat.st_mode);

    // Print number of hard links
    printf(" %ld", (long)file_stat.st_nlink);

    // Print owner and group names
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw ? pw->pw_name : "UNKNOWN", gr ? gr->gr_name : "UNKNOWN");

    // Print file size
    printf(" %ld", (long)file_stat.st_size);

    // Print last modification time
    char time_str[20];
    struct tm *timeinfo = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);
    printf(" %s", time_str);

    // Print the entry name
    printf(" %s\n", entry_name);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s dirname|filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat path_stat;
    if (stat(argv[1], &path_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Check if the provided path is a directory
    if (S_ISDIR(path_stat.st_mode)) {
        // Open the directory
        DIR *dir = opendir(argv[1]);
        if (dir == NULL) {
            perror("opendir");
            exit(EXIT_FAILURE);
        }

        printf("Directory: %s\n", argv[1]);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                list_entry(argv[1], entry->d_name);
            }
        }

        closedir(dir);
    } else {
        // If the path is a file, print its details
        list_entry(".", argv[1]);
    }

    return 0;
}
