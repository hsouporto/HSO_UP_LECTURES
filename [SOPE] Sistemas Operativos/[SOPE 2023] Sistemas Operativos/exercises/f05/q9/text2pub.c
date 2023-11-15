#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


// STATUS: TESTED

#define SEED 1

char *cmd_final[] = {"zip", "-R", "final", "*.epub", NULL};  

int main(int argc, char* argv[]) {

    // sanity checks
    if(argc < 2){
        printf("Usage %s  filename1, filename n\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid;

    // now each process lauch its own version
    for (int i = 1; i < argc; i++){

        char buffer[100];
        strcpy(buffer, argv[i]);            // safe copy maintain original
        printf("ori: %s\n", argv[i]);

        char *file_dest = strtok(buffer, ".");
        strcat(file_dest, ".epub");
        printf("dest: %s\n", file_dest);
        printf("ori: %s\n", argv[i]);

        // try to fork
        if ((pid = fork()) < 0){
            // added
            fprintf(stderr, "Cannot fork: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        if(pid==0){
            //printf("dest: %s\n", file_dest);
            //printf("ori: %s\n", argv[i]);
            printf("[Pid %d] Converting file %s... \n",getpid(), argv[i]);

            // evoque the comamnd
            if (execlp("pandoc", "pandoc", argv[i], "-o",  file_dest, (char *)NULL)) {
               
                fprintf(stderr, "Failed to exec '%s': %s\n", "exec", strerror(errno));
                return EXIT_FAILURE;
            }
            exit(0);
        }

    }

    // parent waits all childs to end
    for(int i = 1; i < argc; i++) // loop will run n times
        wait(NULL);
    

        // final zip
    if (execvp(cmd_final[0], cmd_final) < 0) {
        /* exec error */ 
        fprintf(stderr, "[Parent] Failed to exec '%s': %s\n", cmd_final[0], strerror(errno));
        return EXIT_FAILURE;
    } 


    return EXIT_SUCCESS;


}