#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define CHUNK_SIZE 100

int main() {
    const char *name = "shared_memory";
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, CHUNK_SIZE);

    char *ptr = mmap(0, CHUNK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process converting to lowercase and creating new file\n");

        FILE *outputFile = fopen("output.txt", "w");
        while (*ptr != '\0') {
            for (int i = 0; i < CHUNK_SIZE && *ptr; i++) {
                fputc(tolower(*ptr++), outputFile);
            }
            fputc('\0', outputFile);
        }
        fclose(outputFile);
    } else {
        // Parent process
        FILE *inputFile = fopen("input.txt", "r");
        fseek(inputFile, 0, SEEK_END);
        long fileSize = ftell(inputFile);
        fseek(inputFile, 0, SEEK_SET);

        int chunks = (fileSize + CHUNK_SIZE - 1) / CHUNK_SIZE;
        for (int i = 0; i < chunks; i++) {
            fread(ptr, sizeof(char), CHUNK_SIZE, inputFile);
            ptr[CHUNK_SIZE] = '\0';
            ptr += CHUNK_SIZE;
        }
        fclose(inputFile);

        wait(NULL);
        printf("Parent process received modified content. New file created as output.txt.\n");
        shm_unlink(name);
    }

    return 0;
}