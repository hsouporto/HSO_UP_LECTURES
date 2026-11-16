#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }


    clock_t start_time, end_time;
    double thread_time, task_time;

    char buffer[BUFFER_SIZE];

    start_time = clock();

    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    while (nchars > 0){
        fwrite(buffer, sizeof(char), nchars, stdout);
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    }

    end_time = clock();
    task_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Printing the results
    printf("Time taken by : %f seconds\n", thread_time);
    printf("Time taken by : %f seconds\n", task_time);


    fclose(file);
    exit(EXIT_SUCCESS);
}