#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024



int main(int argc, char *argv[]){

    clock_t start_time, end_time;
    double read_time, task_time;


    if (argc <2){
        printf("File argument not given\n");
       return -1;

    }


    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    // 1024
    start_time = clock();

    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);

    while (nchars > 0){
        fwrite(buffer, sizeof(char), nchars, stdout);           // are putitng in the stdout
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file); // 
    }

    end_time = clock();
    read_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken by READING with 1024: %f seconds\n", read_time);




    // 1
    start_time = clock();
    nchars = fread(buffer, sizeof(char), 1, file);

    while (nchars > 0){
        fwrite(buffer, sizeof(char), nchars, stdout);           // are putitng in the stdout
        nchars = fread(buffer, sizeof(char), 1, file); // 
    }

    end_time = clock();
    read_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken by READING with 1: %f seconds\n", read_time);


    // Alternative way
    /*
    
    while(nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file) > 0){
        fwrite(buffer, sizeof(char), nchars, stdout); 
    }
    */

    fclose(file);
    exit(EXIT_SUCCESS);
}