# Solutions Ficha 02 (HSO)

1. Recall the definition of the complex number z ∈ C as x + yi, where x, y ∈ R. The
values x and y represent, respectively, the real and imaginary parts of z.
The following C header file (a file with extension .h) defines a new datatype called complex
that can be used to implement a library of functions that operate on complex numbers.
The list of such functions and their types (the library’s Application Programmer’s Interface
or API) is also provided in this file (complex.h):

```
/* definition of new type complex */
typedef struct {
    double x;
    double y;
} complex;

/* definition of the complex library API */
complex* complex_new(double, double);
complex* complex_add(complex *, complex *);
complex* complex_sub(complex *, complex *);
complex* complex_mul(complex *, complex *);
complex* complex_div(complex *, complex *);
complex* complex_conj(complex *);
double complex_mod(complex *);
double complex_arg(complex *);
double complex_re(complex *);
double complex_im(complex *);

```

Consider also the file use_complex.c that makes use of the above API to create complex
numbers and to manipulate them.

```
#include <stdio.h>
#include <stdlib.h>

#include "complex.h"
int main(int argc, char** argv) {
    complex* z1 = complex_new(-2.16793, 5.23394);
    complex* z2 = complex_new( 1.12227, 2.52236);
    complex* z3 = complex_add(z1, z2);
    complex* z4 = complex_sub(z1, z2);
    complex* z5 = complex_mul(z1, z2);
    complex* z6 = complex_div(z1, z2);
    double x1 = complex_mod(z1);
    double x2 = complex_re(z1);
    double x3 = complex_im(z3);
    printf("z1 = %f + %fi\n", z1->x, z1->y);
    printf("z2 = %f + %fi\n", z2->x, z2->y);
    printf("z3 = %f + %fi\n", z3->x, z3->y);
    printf("z4 = %f + %fi\n", z4->x, z4->y);
    printf("z5 = %f + %fi\n", z5->x, z5->y);
    printf("z6 = %f + %fi\n", z6->x, z6->y);
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
    printf("x3 = %f\n", x3);
    return 0;
}
```

Finally, the file complex.c provides the implementation of the API, i.e., the implementation
of all functions listed in complex.h:

```
#include <stdlib.h>
#include <math.h>
#include "complex.h"
/*
* implementation of the Complex API
*/
complex* complex_new(double x, double y) {
    complex* z = (complex*) malloc(sizeof(complex));
    z->x = x;
    z->y = y;
    return z;
}
complex* complex_add(complex* z, complex* w){
    return complex_new(z->x + w->x, z->y + w->y);
}

complex* complex_sub(complex* z, complex* w){
    /* to complete ... */
    return complex_new(z->x - w->x, z->y - w->y);
}

complex* complex_mul(complex* z, complex* w){
    return complex_new(z->x * w->x - z->y * w->y,
    z->x * w->y + z->y * w->x);
}

complex* complex_div(complex* z, complex* w){
    /* to complete ... */
    return complex_new(z->x / w->x - z->y / w->y, z->x / w->y + z->y / w->x);
}

complex* complex_conj(complex* z){
    /* to complete ... */
    return complex_new(z->x , z->y * (-1.0));
}

double complex_mod(complex* z){
    /* to complete ... */
    return sqrt(pow(z->x, 2) +  pow(z->y, 2)) ;
}
double complex_arg(complex* z){
    return atan2(z->y,z->x);
}

double complex_re(complex* z){
    return z->x;
}

double complex_im(complex* z){
    /* to complete ... */
    return z->y;
}
```

The exercise asks for create a file for each function and compile it. what we do is just simple
````
gcc -Wall -c complex_*.c (select all files that match and compile without linking)
````

This will generate a set of object files for each function.
To create a library, we should make a archive with all object files as

````
$ ar -rc libcomplex.a complex_*.o (aggregate all .o that matches and create archive)

$ ar -t libcomplex.a // usar o comando "ar" para ver o cont ́eudo

$ nm libcomplex.a // o comando "nm" tamb ́em permite faz^e-l

````
finally, we compile the main program use_complex.c informing the compiler (actually the
linker) that it should use code from the library libcomplex.a (-lcomplex) located in the
current directory (-L.):

```´
gcc -Wall use_complex.c -o use_complex -L. -lcomplex -lm
````

Note also that C’s math library was also included -lm, as function in it such as atan2 and
sqrt, are used in the implementation of complex.c


Alternatively, you can create an single file complex.c compile it and follow same steps 

To run the example, we first compile the API and build a library as an archive (extension.a) as libcomplex.a that will be used by the main program:
```
$ gcc -Wall -c complex.c        // compile the file and dont link

$ ar -rc libcomplex.a complex.o  // create a archive  (-r replace, -c create silentsly)
$ ar -t libcomplex.a            // -t list order of appearance
```

finally, we compile the main program use_complex.c informing the compiler (actually the
linker) that it should use code from the library libcomplex.a (-lcomplex) located in the
current directory (-L.):

```
$ gcc -Wall use_complex.c -o use_complex -L. -lcomplex -lm
````

Note also that C’s math library was also included -lm, as function in it such as atan2 and
sqrt, are used in the implementation of complex.c.

**Response:**

ar creates archive (-r ~ replace add specific files to, -c ~no verbose, -t ~list by order off appearence)

gcc -Wall use_complex.c -o use_complex -L. -lcomplex -lm  (-L ~where to look for, . ~current directory)
 
**More details:**

In the GCC (GNU Compiler Collection) command, the -L option is used to specify directories where the linker should look for libraries when resolving symbols in your program. The period (.) after the -L option refers to the current directory, which means that the linker should look for libraries in the current directory.

Here's a breakdown of the -L. option:

-L: This is the option flag that tells GCC to specify a library directory.
.: This is the argument to the -L option, and it represents the current directory.
When you compile a program that depends on external libraries, the linker needs to find those libraries to resolve symbols used in your code. By using the -L option followed by a directory path, you can instruct the linker to search for libraries in that directory. In this case, by specifying -L., you're telling the linker to look for libraries in the current directory where you're running the GCC compiler.

Here's an example of how you might use this option:

bash
Copy code
gcc -o my_program my_program.c -L. -lmylib
In this example:

-o my_program specifies the output executable file name.
my_program.c is the source code file.
-L. tells the linker to search for libraries in the current directory.
-lmylib specifies that your program depends on a library called libmylib.so or libmylib.a.
So, the -L. option helps ensure that the linker can find the necessary libraries located in the current directory during the compilation process.

================================================


2. Repeat the above exercise but now building and using a dynamic library, by running
the following commands:

```
$ gcc -c -Wall -fPIC -o complex.o complex.c
$ gcc -shared -o libcomplex.so complex.o
```

**Response:** 

Position Independent Code means that the generated machine code is not dependent on being located at a specific address in order to work.


**More Details:**

When you compile code with the -fPIC (Position-Independent Code) option in GCC, it has an impact on the code generation, making it suitable for use in shared libraries or position-independent executables. When using this option in conjunction with the -L option, it typically means you're compiling code that is intended to be used in shared libraries, and you're specifying the library search path for those shared libraries.

Here's how it works:

-fPIC Option: This option tells GCC to generate position-independent code. Position-independent code can be loaded and executed at any memory address, making it suitable for shared libraries (.so files on Linux) because the operating system can load them at different addresses for each process that uses them. This option is essential when building shared libraries.

-L. Option: This part remains the same as explained earlier. It specifies the current directory as a library search path.

When you combine these options in your GCC command, you're essentially telling the compiler to generate position-independent code and also look for libraries in the current directory.

Here's an example:


Option -fPIC informs the compiler that it should generate position independent code. This
is important because the dynamic library will be loaded into memory when the program is
already running (hence the dynamic adjective) in addresses that are not known a priori by
the compiler. Option -shared indicates to the compiler that the resulting library should
be created as a shared object (extension .so), as libcomplex.so. After being created, the
library is used in much the same way as its static version to compile the main program:

```
$ gcc -Wall use_complex.c -o use_complex -L. -lcomplex
$ ./use_complex
```

Depending on the operating system you are using, you may also need to run the command:
````
$ export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
````
so that the library may be found by the operating system.

================================================

3. Consider the header file vector.h as follows, containing the definition of a type vector,
that represents a 3D vector ∈ R3:

```
/* definition of new type vector */
typedef struct {
    double x;
    double y;
    double z;
} vector;
/* definition of the vector API */
vector* vector_new(double, double, double);
vector* vector_add(vector*, vector*);
vector* vector_sub(vector*, vector*);
vector* vector_scale(double, vector*);
vector* vector_vprod(vector*, vector*);
double vector_sprod(vector*, vector*);
double vector_mod(vector*);
````

As in the previous exercise, consider a file use_vector.c that uses the “vector” API.

```
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char** argv) {
    vector* v1 = vector_new(-5.1, 2.3, 3.6);
    vector* v2 = vector_new( 1.6, 7.6, -4.2);
    vector* v3 = vector_add(v1, v2);
    vector* v4 = vector_sub(v1, v2);
    vector* v5 = vector_scale(-9.2, v2);
    vector* v6 = vector_vprod(v1,v2);
    double x1 = vector_sprod(v1, v2);
    double x2 = vector_mod(v6);
    printf("v1 = (%f, %f, %f)\n", v1->x, v1->y, v1->z);
    printf("v2 = (%f, %f, %f)\n", v2->x, v2->y, v2->z);
    printf("v3 = (%f, %f, %f)\n", v3->x, v3->y, v3->z);
    printf("v4 = (%f, %f, %f)\n", v4->x, v4->y, v4->z);
    printf("v5 = (%f, %f, %f)\n", v5->x, v5->y, v5->z);
    printf("v6 = (%f, %f, %f)\n", v6->x, v6->y, v6->z);
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
    return 0;
}
```

Write an implementation for the API in a file vector.c, compile it and build a library
libvector.a. Compile the program use_vector.c with the library and run it.

`````
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/* definition of the vector API */
vector* vector_new(double x, double y, double z){
    vector* v = (vector*) malloc(sizeof(vector));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
};


vector* vector_add(vector* v, vector* u){
    return vector_new(v->x + u->x, v->y + u->y, v->z + u->z );
}


vector* vector_sub(vector* v, vector* u){
    return vector_new(v->x - u->x, v->y - u->y, v->z - u->z );
}

vector* vector_scale(double x, vector* v){
    return vector_new(v->x * x, v->y * x , v->z * x);

}

vector* vector_vprod(vector* v, vector* u){
    return vector_new((v->y * u->z -v->z * u->y),  ( v->z * u->x - v->y * u->x  ), (v->x * u->y - v->x * u->z));
}


double vector_sprod(vector* u, vector* v){
    return (u->x * v->x + u->y * v->y + u->z * v->z);
}

double vector_mod(vector* u){
    return sqrt(pow(u->x, 2) + pow(u->y, 2) + pow(u->z, 2));
}
`````

`````
gcc -Wall -c vector_*.c

ar -rc libcvector.a vector_*.o (aggregate all .o that matches and create archive)

$ ar -t libcvector.a // usar o comando "ar" para ver o cont ́eudo

$ nm libvector.a // o comando "nm" tamb ́em permite faz^e-l


gcc -Wall use_vector.c -o use_vector -L. -libvector -lm

`````


===============================================


4. Consider the file matrix.h that contains the definition of type matrix, representing a
N × M matrix of floating point values.

```
/* definition of new type matrix */

typedef struct {
    int n;
    int m;
    double* vals;
} matrix;

/* definition of the matrix API */
matrix* matrix_new(int, int);
matrix* matrix_new_random(int, int, double, double);
void matrix_print(matrix*);
double matrix_get(int, int, matrix*);
void matrix_set(int, int, double, matrix*);
matrix* matrix_add(matrix *, matrix *);
matrix* matrix_sub(matrix *, matrix *);
matrix* matrix_mul(matrix *, matrix *);
matrix* matrix_trans(matrix *);
````

Consider the file matrix.c that contains a partial implementation for the API. Complete it.

```
include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* implementation of the matrix API */

matrix* matrix_new(int n, int m) {
    matrix* u = (matrix*) malloc(sizeof(matrix));
    u->n = n;
    u->m = m;
    u->vals = (double*) malloc ((u->n * u->m) * sizeof(double));
    return u;
}

matrix* matrix_new_random(int n, int m, double min, double max) {

    matrix* u = (matrix*) malloc(sizeof(matrix));
    u->n = n;
    u->m = m;
    u->vals = (double*) malloc ((u->n * u->m) * sizeof(double));
    int i, j;
    double range = max - min;
    double div = RAND_MAX / range;
    for(i = 0; i < u->n; i++)
        for(j = 0; j < u->m; j++)
            matrix_set(i, j, min + (rand() / div), u);
    return u;
}

void matrix_print(matrix* u) {
    /* to complete ... */
    
    for(int i = 0; i < u->n; i++){
        printf("| ");

    
        for(int j = 0; j < u->m; j++)
            printf("% f ", *(u->vals + i * u->m + j));

        printf("|\n\r");

    }
    printf("\r\n");
}

double matrix_get(int i, int j, matrix* u){
    return *(u->vals + i * u->m + j);
}

void matrix_set(int i, int j, double val, matrix* u){
    *(u->vals + i * u->m + j)=val;
}

matrix* matrix_add(matrix* u, matrix* v){
    int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) + matrix_get(i, j, v), w);
    
    return w;
}

matrix* matrix_sub(matrix* u, matrix* v){
        int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) - matrix_get(i, j, v), w);
    
    return w;
}

matrix* matrix_mul(matrix* u, matrix* v){
    int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) *  matrix_get(i, j, v), w);
    
    return w;
}

matrix* matrix_trans(matrix* u){

    // allocate new matrix
    matrix* w = matrix_new(u->m, u->n);
    
    for (int i = 0; i < u->n; i++) {
        for (int j = 0; j < u->m; j++) {
            matrix_set(j, i, matrix_get(i, j, u), w); // bet from u and place into wß
            
        }
        
    }
    return w;
}

```

Write a file use_matrix.c with a main() function where you create some matrices and
use the API to perform operations on them.

===========================================

5. TODO: Consider the file list.h that contains a definition of a type list, representing a linked
list of integers.

````
/* definition of new type list */
typedef struct anode {
    int val;
    struct anode* next;
} node;

typedef struct {
    int size;
    node* first;
} list;

/* definition of the list API */
node* node_new(int, node*);
list* list_new();
list* list_new_random(int, int);
void list_add_first(int, list *);
void list_add_last(int, list *);
int list_get_first(list *);
int list_get_last(list *);
void list_remove_first(list *);
void list_remove_last(list *);
int list_size(list *);
void list_print(list *);
````

Consider the file list.c that contains a partial implementation of the aforementioned API.
Complete it.

```
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* implementation of the List API */
node* node_new(int val, node* p) {
    node* q = (node*)malloc(sizeof(node));
    q->val = val;
    q->next = p;
    return q;
}

list* list_new() {
    list* l = (list*) malloc(sizeof(list));
    l->size = 0;
    l->first = NULL;
    return l;
}

list* list_new_random(int size, int range) {
    list* l = list_new();
    int i;
    for(i = 0; i < size; i++)
    list_add_first(rand() % range, l);
    return l;
}
void list_add_first(int val, list *l) {
    /* to complete ... */
}

void list_add_last(int val, list *l) {
    node* p = node_new(val, NULL);
    if (l->size == 0) {
    l->first = p;
    }else{
    node* q = l->first;
    while (q->next != NULL)
    q = q->next;
    q->next = p;
    }
    l->size++;
}

int list_get_first(list *l) {
    /* assumes list l is not empty */
    return l->first->val;
}

int list_get_last(list *l) {
    /* to complete ... */
}

void list_remove_first(list *l) {
    /* assumes list l is not empty */
    node* p = l->first;
    l->first = l->first->next;
    l->size--;
    /* free memory allocated for node p */
    free(p);
}

void list_remove_last(list *l) {
    /* to complete ... */
}

int list_size(list *l) {
    /* to complete ... */
}
void list_print(list* l) {
    /* to complete ... */
}
```

Write a file use_list.c that creates one or more lists and that uses the functions of the
API to manipulate them.

==================================================


6. The code that follows presents an alternative implementation of exercise 1 for a library
that operates on complex numbers (file complex.c):

````
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
char complex_buf[100];

complex complex_new(double x, double y) {
    complex z;
    z.x = x;
    z.y = y;
    return z;
}

char* complex_print(complex z) {
    if (z.y == 0)
    sprintf(complex_buf, "%f", z.x);
    else if (z.x == 0)
    sprintf(complex_buf, "%fi", z.y);
    else if (z.y > 0)
    sprintf(complex_buf, "%f+%fi", z.x, z.y);
    else
    sprintf(complex_buf, "%f%fi", z.x, z.y);
    return complex_buf;
}

complex complex_add(complex z, complex w){
    complex r;
    r.x = z.x + w.x;
    r.y = z.y + w.y;
    return r;
}

complex complex_sub(complex z, complex w){
    complex r;
    r.x = z.x - w.x;
    r.y = z.y - w.y;
    return r;
}

complex complex_mul(complex z, complex w){
    complex r;
    r.x = z.x * w.x - z.y * w.y;
    r.y = z.x * w.y + z.y * w.x;
    return r;
}

complex complex_div(complex z, complex w){
    complex r;
    double d = w.x * w.x + w.y * w.y;
    r.x = (z.x * w.x + z.y * w.y) / d;
    r.y = (- z.x * w.y + z.y * w.x) / d;
    return r;
}

complex complex_conj(complex z){
    complex r;
    r.x = z.x;
    r.y = -z.y;
    return r;
}

double complex_mod(complex z){
    return sqrt(z.x * z.x + z.y * z.y);
}
double complex_arg(complex z){
    return atan2(z.y, z.x);
}

double complex_re(complex z){
    return z.x;
}

double complex_im(complex z){
    return z.y;
}
````

This new API is used in file use_complex.c:


```
#include <stdio.h>
#include "complex.h"

int main(int argc, char** argv) {
    complex z1 = complex_new(-2.16793, 5.23394);
    complex z2 = complex_new( 1.12227, 2.52236);
    complex z3 = complex_add(z1, z2);
    complex z4 = complex_sub(z1, z2);
    complex z5 = complex_mul(z1, z2);
    complex z6 = complex_div(z1, z2);
    double x1 = complex_mod(z1);
    double x2 = complex_re(z1);
    double x3 = complex_im(z3);
    printf("z1 = %s\n", complex_print(z1));
    printf("z2 = %s\n", complex_print(z2));
    printf("z3 = %s\n", complex_print(z3));
    printf("z4 = %s\n", complex_print(z4));
    printf("z5 = %s\n", complex_print(z5));
    printf("z6 = %s\n", complex_print(z6));
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
    printf("x3 = %f\n", x3);
    return 0;
}
```

Based on the code here presented, write the corresponding header file complex.h, compile
the library and main program and check that you get similar results to those of exercise

==============================================


