1. Preprocessor
The first thing that GCC makes is run the PRE-PROCESSOR. It takes the source code, removes the comments, includes headers, and replaces macros with code ( keep reading to understand these). You can ask the preprocessor to stop at the end of this stage with the flag “-E”.

$gcc -E file.c
The comments let the people understand what your functions need as input (parameters), what the function does with these parameters, and what it returns in case of success or failure. It means that when someone else needs to use that function can read those comments and be ready to use it. They look like this:

/**
 * function_name - description of the process made by the function
 * @parameter: The description of the parameter
 * Return: Description of what is printed in the standard error
 * if the functions achive its goal, or if it fails
 */
Comments can be inside the function, too. They can inform what the code does, or they can be used to avoid some lines in the compilation.

c = (a < b) ? a : b; /* a comment here can explain this line */
A header file tells the compiler how to call some functionality, It means, which is the name of the function, which are the inputs needed and the output it generates. But headers don’t include the process made in the middle of the inputs and the outputs. Think that the functions are your friends and the header is like an agenda where you save the numbers of your friends, so you can call them when you want to. The header is included in the same subdirectory as the source code, and on the inside, the header files are human-readable, with the same syntax as the source code.

int _putchar(char c);
This is our new friend the function ‘_putchar’. To call her we need to give a char, and it is going to return an integer (a number). The body of the function is going to be in the Libraries added in the linking step.

A macro is a fragment of code that is given a name. They can define constants that are going to be used during the process but they can’t be changed during the process implementation, like in the first example the constant PI. They can define some kind of special function, too. In the second example is defined the process to get the area of a circle of diameter r.

#define PI 3.14
#define circleArea(r) (3.1415*(r)*(r))
2. Compiling
The output of the preprocessor is received and transformed in assembly code.
A human-readable language, a little bit harder than C. Let's see an example of the same function written in C, and written in assembly:

int main(){
return (1);
}
The assembly code gives more specific and detailed instructions than a more human-readable language.

cat example.s
.file   "example.c"
        .text
        .globl  main
        .type   main, @function
main:
.LFB0:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        movl    $1, %eax
        popq    %rbp
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc
.LFE0:
        .size   main, .-main
        .ident  "GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
        .section        .note.GNU-stack,"",@progbits
To see your own functions translated to assembly code, use the flag -S.

$gcc -S filename.c

3. Assembly
The assembler translates the assembly code into binary.

$gcc -c filename.c
The previous example in this stage generates a file with the extension ‘.o’ named ‘object code’. It is a binary file, but an editor as emacs, vim, or nano, will not show the ones and zeros, they will will show something like this:

$ cat example.o
ELF>@@
UH��]�GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0zRx

F                                                       A�C
 ��
                 
                   example.cmain .symtab.strtab.shstrtab.text.data.bss.comment.note.GNU-                                                                                       -stack.rela.eh_frame
If you want to see the file in zeros and ones, you can use the command xxd:

xxd  -b example.o
It is a little bit long: 204 lines, just to return the number 1.


4. Linking
Finally, the linker adds the environment variables, function definitions, and settings required to run the code, creating a very big executable file. Keep reading to see what these mean.

To complete the linking phase, you can compile without any flag:

$gcc filename.c
By default, it will create a new executable file called a.out. Execute it like this:

$ ./a.out
The linker will look for the environmental variables mentioned in your code, for example:

$HOME
And will bring the content of the variable, in my case:

/home/vagrant
You can see all your environment variables with the command printenv:

$ printenv
LANG=en_US.UTF-8
HOME=/home/vagrant      #This is the home directory
XDG_SESSION_ID=13
USER=vagrant
SHELL=/bin/bash
LANGUAGE=en_US:
PATH=/home/vagrant/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
_=/usr/bin/printenv
OLDPWD=/home/vagrant/holberton-system_engineering-devops
and see the content of one of these with echo:

$ echo $HOME
/home/vagrant
All these variables can be taken into account inside your functions.

About function definitions, the compiler already knows that we called the library stdio.h, and we used the function putchar. But it only knows the prototype that we included in the header. The linker now searches the body of the function putchar and includes it inside our program.



1. **Preprocessing (`cpp`)**
   - The first step is preprocessing. The source code is processed by the C Preprocessor (`cpp`), which handles directives like `#include`, `#define`, and `#ifdef`. It generates an intermediate file with all these processed directives.

2. **Compilation (`cc1`)**
   - The preprocessed code is passed to the compiler proper (`cc1`), which generates assembly code from the high-level language source code. This step involves parsing the code, checking it for syntax errors, and translating it into assembly language.

3. **Assembly (`as`)**
   - The assembly code generated in the previous step is passed to the assembler (`as`), which converts it into machine code (binary code) and produces an object file. The object file typically has a `.o` or `.obj` extension.

4. **Linking (`ld`)**
   - If your code consists of multiple source files or depends on external libraries, you need to link them together. The linker (`ld`) takes care of this task. It resolves references between different object files, libraries, and system-level dependencies, creating a single executable file or shared library.

5. **Output Generation**
   - The final output can be one of the following:
     - Executable Binary: If you're compiling a standalone program, the output is an executable binary file.
     - Shared Library: If you're building a shared library, the output is a `.so` (shared object) file on Linux or a `.dll` (dynamic-link library) file on Windows.
     - Object Files: In some cases, you may choose to compile only to the object file level without linking. This is common when building large projects, and the linking is done separately to save time.

6. **Optional Optimization (`-O`)**
   - You can apply optimization flags (e.g., `-O2`, `-O3`) during the compilation process to instruct the compiler to optimize the generated code for better performance.

7. **Optional Debugging Information (`-g`)**
   - To aid in debugging, you can include debugging information in the output binary using the `-g` flag. This information allows you to use debugging tools to inspect variables, set breakpoints, and trace program execution.

8. **Optional Additional Flags and Options**
   - Depending on your specific requirements, you can specify additional flags and options to control various aspects of compilation, such as specifying include directories (`-I`), library directories (`-L`), and library names (`-l`).

9. **Final Output**
   - Once the compilation process is complete, you'll have your executable program, shared library, or object files ready for use or distribution.

Keep in mind that the exact details and options may vary depending on the platform, programming language, and specific requirements of your project. The steps outlined here provide a general overview of the compilation process using GCC for C and C++ programs.
