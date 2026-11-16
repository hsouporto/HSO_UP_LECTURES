
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s -o output_file source_file1 source_file2 ... source_filen\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *outputFile = argv[2];

    // Compile each source file in parallel
    for (int i = 3; i < argc; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);

        } else if (pid == 0) {
            execlp("gcc", "gcc", "-Wall", "-c", argv[i], (char *)NULL);
            perror("Compilation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent wait all childs to finish
    for (int i = 3; i < argc; i++) {
        wait(NULL);
    }

    // Lest link the object files into the final executable

    execlp("gcc", "gcc", argv[3], "-o", outputFile, (char *)NULL);


    return 0;
}


/*
Compile this program using a C compiler (e.g., `gcc`). The program expects the output file (`-o` flag) followed by the source files. For example:

```bash
$ gcc parcc.c -o parcc
$ ./parcc -o myprogram prog1.c prog2.c prog3.c
```

This will compile each source file in parallel and then link them to create the final executable `myprogram`.
*/

