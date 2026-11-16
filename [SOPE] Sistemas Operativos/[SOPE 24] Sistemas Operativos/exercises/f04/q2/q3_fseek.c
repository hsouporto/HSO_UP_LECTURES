#include <stdio.h>

int main(int argc, char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long position = ftell(file);  // Get N of chars in file


    while (position > 0) {
        position--;
        fseek(file, position, SEEK_SET);  
        int ch = fgetc(file);  
        if (ch != EOF) {
            putchar(ch); 
        }
    }

    fclose(file);
    return 0;
}

