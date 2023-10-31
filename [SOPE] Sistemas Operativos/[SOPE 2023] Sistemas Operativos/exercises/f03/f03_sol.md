1. Consider the following program the exemplifies the use of the main function in its most
general form in C.

```
#include <stdio.h>
int main (int argc, char* argv[]) {
    printf("# arguments = %d\n", argc - 1);
    printf("the command arguments are: %s\n", argv[0]);

    for (int i = 1; i < argc ; i++)
        printf("argv[%d]=%s\n", i, argv[i]);
    
    return 0;
}
````

Compile the program and try it with the following commands:

```
$ gcc -Wall maintest.c -o maintest
$ ./maintest
$ ./maintest mercury
$ ./maintest mercury venus
$ ./maintest mercury venus earth
$ ./maintest mercury venus earth mars
````

The type of the main function is:
int main (int argc, char* argv[])

Here argc is the number of strings in the command line and argv is a vector that stores all
those strings (e.g., in the second example, argv[0] = "./maintest" and argv[0] = "mercury").

This form of the main function is very useful as it allows the programmer to pass values
to the application without using I/O functions such as scanf.

===================================

2. Consider the following program that takes two strings from the command line (argv[1]
e argv[2]) and manipulates them with the string subset of the Standard C Library (clib)
API. Compile it and try it.

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 64
int main(int argc, char* argv[]) {
    char* p1 = (char*)malloc(MAX_SIZE * sizeof(char));
    char* p2 = (char*)malloc(MAX_SIZE * sizeof(char));
    int result = strcmp(argv[1], argv[2]);

    if (result == 0)
        printf("the strings are the same\n");

    else if (result < 0)
        printf("%s < %s\n", argv[1], argv[2]);

    else
       printf("%s > %s\n", argv[1], argv[2]);

    strcpy(p1, argv[1]);
    strcpy(p2, argv[2]);

    printf("p1 holds:%s\n", p1);
    printf("p2 holds:%s\n", p2);

    strcat(p1,p2);
    printf("p1 holds:%s\n", p1);

    strcat(p2,p1);
    printf("p2 holds:%s\n", p2);

    exit(EXIT_SUCCESS);
}
````

Run the command man 3 string to see the full set of functions in this API. Based on this
example, write a program that:

• gets a string from the command line and transforms it into an equivalent string but
in lowercase;

````
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// STATUS: TESTED

// macro function
#define my_tolower(a) (((a) <= 90 && ((a) >= 65)) ? (a + 32) : (a))


int main(int argc, char const *argv[]){
     
    // test if number of arguments is correct 
    if (argc < 2){
        printf("ERROR -> Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // maintain original, alternatively use malloc and strcopy
    char *str = (char*) argv[1];
    #ifdef DEBUG
    printf("DEBUG: string length = %d\n", (int) strlen(str));
    #endif

    // iterate over the string chars
    for (size_t i = 0; i < strlen(str); i++){
       // str[i] = tolower(str[i]);               // convert char to lower (alternatively you can do your own tolower (check ascci table))
        str[i] = my_tolower(str[i]);              // alternative implementation using an macro
    }

    printf("Converted String: %s\n", str);
    return EXIT_SUCCESS;
}
````

• gets two strings from the command line and indicates whether the first occurs within
the second;

```
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// STATE: TESTED
 
#define MAX_STR_SIZE 64

int main(int argc, char* argv[]) {

    if(argc < 3){
        printf("ERROR -> Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // allocate new char arrays and copy them (plus one to add \0)
    char *str = malloc(strlen(argv[1]) * sizeof(char));
    strcpy(str, argv[1]);

    // copy first string
    char *substr = malloc(strlen(argv[2]) * sizeof(char));
    strcpy(substr, argv[2]);

    // NOTE: strstr expects bigger and small, but for sanity checks we do test len of strings
    if(strlen(str) >= strlen(substr)){
        if((strstr(str, substr)) != NULL)
            printf("String <%s> contains <%s>\r\n", str, substr);
        else
            printf("String <%s> dont contain <%s>\r\n", str, substr);

    // reverse test
    }else{
        if((strstr(substr, str)) != NULL)
            printf("String <%s> contains <%s>\r\n", substr, str);
        else
            printf("String <%s> dont contain <%s>\r\n", substr, str);

    }
   
    return EXIT_SUCCESS;
}
````

• gets two strings from the command line and indicates how many times the first occurs
in the second.

```
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// STATUS: TESTED

int main(int argc, char const *argv[]){

    // sanity checks
    if (argc != 3){
        printf("ERROR -> Usage: %s <string> <substring>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // allocate new char arrays and copy them (plus one to add \0)
    char *str = malloc(strlen(argv[1])  * sizeof(char));
    strcpy(str, argv[1]);

    // copy first string
    char *substr = malloc(strlen(argv[2]) * sizeof(char));
    strcpy(substr, argv[2]);

    // auxliary pointer to maintain str original
    char *aux_str = str;

    // count number of ocurrences
    unsigned int n_occur = 0;
    
    // while strstr != NULLL, a math is found
    while ((aux_str=strstr(aux_str, substr)) != NULL) { // loop ultil end, if found
        n_occur++;

        aux_str ++;                 // this 
        //aux_str +=strlen(substr);   // vs this
        #ifdef DEBUBG
        printf("DEBUG: aux = '%s'\n", aux_str);
        #endif
    }

    printf("Num of ocurrences: %u\n", n_occur);

    // free the mallocs
    free(str);
    free(substr);

    return EXIT_SUCCESS;
}

```

Suggestion: do man tolower and man toupper to see clib functions that may be relevant.

===========================================

3. Consider the following program that opens a file whose name is given as an argument
(argv[1] in the code), reads its content in blocks of BUFFER_SIZE bytes and that writes
those bytes to the terminal (stdout).

```
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "r");
    if ( file == NULL ) {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    while (nchars > 0) {
        fwrite(buffer, sizeof(char), nchars, stdout);
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    }
    
    fclose(file);
    exit(EXIT_SUCCESS);
}
````
Compile the program and try it with the following commands:
```
$ gcc -Wall filetest.c -o filetest
$ cat > quote.txt
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Cras gravida nisl tortor, eget vulputate lacus viverra non.
Proin pharetra gravida condimentum.
Nam imperdiet dictum placerat.
^D

$ ./filetest quote.txt
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Cras gravida nisl tortor, eget vulputate lacus viverra non.
Proin pharetra gravida condimentum.
Nam imperdiet dictum placerat.
$
```
Check the system manual pages for the functions fopen, fread, fwrite and fclose and
try to understand how the program works. What happens if you define BUFFER_SIZE with
the value 1?

==========================================

4. Based on the previous exercise, write a command called mycat that:

• receives the name of a file as an argument and prints its content (this is exactly what
the shell command cat when given a file name);

• receives a sequence of file names as arguments and prints their contents in the terminal
sequentially (again, this is similar to the way cat works).

```
$ gcc -Wall mycat.c -o mycat
$ cat > file1
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Cras gravida nisl tortor, eget vulputate lacus viverra non.
Proin pharetra gravida condimentum.
Nam imperdiet dictum placerat.
^D

$ cat > file2
Sed convallis hendrerit scelerisque.
Sed sodales sagittis nulla vitae auctor.
Quisque lobortis tortor vitae ligula ullamcorper fermentum.
Aliquam interdum, metus sed rhoncus gravida,
nibh nisl porttitor tortor, in finibus mauris erat et lacus.
^D

$ cat > file3
Aliquam sit amet arcu molestie, sodales sem vitae, semper nisi.
Curabitur lacinia vel metus in aliquam.
Fusce non tellus pulvinar, tincidunt quam ac, rhoncus turpis.
^D

$ ./mycat file1
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Cras gravida nisl tortor, eget vulputate lacus viverra non.
Proin pharetra gravida condimentum.
Nam imperdiet dictum placerat.

$ ./mycat file1 file2 file3
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Cras gravida nisl tortor, eget vulputate lacus viverra non.
Proin pharetra gravida condimentum.
Nam imperdiet dictum placerat.
Sed convallis hendrerit scelerisque.
Sed sodales sagittis nulla vitae auctor.
Quisque lobortis tortor vitae ligula ullamcorper fermentum.
Aliquam interdum, metus sed rhoncus gravida,
nibh nisl porttitor tortor, in finibus mauris erat et lacus.
Aliquam sit amet arcu molestie, sodales sem vitae, semper nisi.
Curabitur lacinia vel metus in aliquam.
Fusce non tellus pulvinar, tincidunt quam ac, rhoncus turpis.
```

**Response:**

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// STATUS: TESTED
// NOTE: using write streamer and read



#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2) {
        printf("ERROR -> usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* loop in the number of files and argv */
    char buffer[BUFFER_SIZE];
    int bytesin;

    for (int i=1; i <argc; i++){
        /* check if file can be opened and is readable */
        int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                printf("error: cannot open %s\n", argv[i]);
                break;
            }

        /* print the contents in blocks */
        while ((bytesin = read(fd, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytesin);
        }
        /* close file */
        close(fd); 
    }  
    return EXIT_SUCCESS;
}

```

OR

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// STATUS: TESTED
// NOTE: USING FREAD AND FWRITE

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2) {
        printf("ERROR -> usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* loop in the number of files and argv */
    char buffer[BUFFER_SIZE];
    FILE *fp= NULL;
    int n_read;

    for (int i=1; i <argc; i++){
        /* check if file can be opened and is readable */
        fp = fopen(argv[i], "rt");  // r for read only, t for text mode
            if (fp == NULL) {
                printf("error: cannot open %s\n", argv[i]);
                break;
            }

        /* print the contents in blocks */
         while ((n_read = fread(buffer, 1, sizeof buffer, fp)) > 0) // while we have something to read
            fwrite(buffer, 1, n_read, stdout);
            printf("%s\n", buffer);

        /* close file */
        fclose(fp); 
    }  
    return EXIT_SUCCESS;
}


```
=============================================

5. Write a program that receives two file names as arguments (argv[1] and argv[2]
in the code) and that copies the content of the first file to the second file. If the second
file does not exist yet, then it must be created. If it already exists, its contents will be
overwritten. This emulates the behavior of the Bash shell command cp.

```
$ gcc -Wall mycp.c -o mycp
$ cat > file1
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
^D

$ ./mycp file1 file2
$ cat file2
Lorem ipsum dolor sit amet, consectetur adipiscing elit.

$ cat > file3
Cras gravida nisl tortor, eget vulputate lacus viverra non.
^D

$ ./mycp file3 file2
$ cat file2
Cras gravida nisl tortor, eget vulputate lacus viverra non.

```

**Response:**

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// STATUS: TESTED

int cp(const char *src_filename, const char *dest_filename){
    // open both files with second + 
    FILE *fpsrc = fopen(src_filename, "r");
    FILE *fpdest = fopen(dest_filename, "w+"); // create if not exist


    // read the file in chuncks of 'BUFFER_SIZE' characters
    #define BUFFER_SIZE 256
    char buffer[BUFFER_SIZE] ;

    size_t count; // store number of characters read by 'fread'
    while ((count = fread(buffer, 1, BUFFER_SIZE, fpsrc))){
        // write to dest file
        fwrite(buffer, sizeof(char), count, fpdest);
        
    }

    return EXIT_SUCCESS;
}


int main(int argc, char const *argv[]){

    /* check if exactly one argument is present */
    if (argc < 3) {
        printf("ERROR -> usage: %s <source_filename> <dest_filename> \n\r", argv[0]);
        return EXIT_FAILURE;
    }

    // copy the files
    cp(argv[1], argv[2]);
    return EXIT_SUCCESS;

}
```

==========================================

6. Write a program mywc that, given a text file as a command line argument, prints:

• the number of characters in the file, if an option -c is used;

• the number of words in the file, if an option -w is used;

• the number of lines in the file, if an option -l is used.

```
$ gcc -Wall mycp.c -o mycp
$ cat > file.txt
This is a test
^D

$ ./mywc -c file.txt
15

$ ./mywc -w file.txt
4

$ ./mywc -l file.txt
1
```

Compare your program to the shell command wc.

**Response:**

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// STATUS: TESTED

#define N_CHARS 1
#define N_WORDS 2
#define N_LINES 3


// Note, this is no to effience, you should use Fread
unsigned long count_file(const char *fname, int mode){

    char ch;
    unsigned long count=0;
    
    // try open file in read mode
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        return 0;

    
    while ((ch = fgetc(fp)) != EOF) {
        // decode de mode
        switch (mode){
            case N_CHARS:
                    count++;
                break;

            case N_LINES:
                      if (ch == '\n' || ch == '\0')count++;
                break;
            
            case N_WORDS:
                      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')count++;
                break;

            default:
                return 0;
                break;
        }
    }

    // close file
    fclose(fp);

    return count;
}




int main(int argc, char* argv[]) {
    /* check if exactly one argument is present */
    if (argc < 2 || argc > 3) {
        printf("ERROR -> usage: %s <filename> or %s <-c or -w> <filename>  \n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    // by default
    int mode = N_CHARS;

    // test number of arguments
    if(argc == 3){
        
        // decode the 2 argument
        if (strcmp("-c", argv[1]) == 0) {
            mode = N_CHARS;
        }
        else if(strcmp("-w", argv[1]) == 0) {
            mode = N_WORDS;
            }
        else if(strcmp("-l", argv[1]) == 0) {
             mode = N_LINES;
            }
    }

    unsigned long count=0;

    // handle positional arguments 
    if(argc == 2)
       count = count_file(argv[1], mode);
    else
       count = count_file(argv[2], mode);


    // present our data accordingly
    switch (mode){
    case N_CHARS:
            printf("Files has %lu CHARS \n\r", count);

        break;

    case N_WORDS:
            printf("Files has %lu WORDS \n\r", count);
        break;

    case N_LINES:
            printf("Files has %lu LINES \n\r", count);
        break;
    default:

        break;
    }   


    return EXIT_SUCCESS;

}

```


