#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

void print_file_info(const char *path, const struct dirent *entry) {
    struct stat file_stat;
    char full_path[1024];

    // Construct the full path for stat
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
    if (stat(full_path, &file_stat) == -1) {
        perror("stat");
        return;
    }

    // File type and permissions
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");

    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    
    // Number of links
    printf(" %lu", file_stat.st_nlink);

    // User and group names
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group  *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");

    // File size
    printf(" %5lld", (long long)file_stat.st_size);

    // Last modification time
    char timebuf[80];
    struct tm *tm = localtime(&file_stat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);
    printf(" %s", timebuf);

    // File name
    printf(" %s\n", entry->d_name);
}

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            print_file_info(path, entry);
        }
    }
    closedir(dir);
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

    if (S_ISDIR(path_stat.st_mode)) {
        // If it's a directory, list contents
        list_directory(argv[1]);
    } else {
        // If it's a file, print information for that file
        struct dirent file_entry;
        strcpy(file_entry.d_name, argv[1]);
        print_file_info(".", &file_entry);
    }

    return 0;
}