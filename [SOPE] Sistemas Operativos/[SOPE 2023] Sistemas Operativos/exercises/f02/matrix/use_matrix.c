#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// STATUS: NOT TESTED

int main(int argc, char** argv) {
    matrix* u1 = matrix_new_random(2, 2, 1.1, 5.5);
    matrix_print(u1);
    matrix* u2 = matrix_new_random(2, 2, 5, 10);
    matrix_print(u2);
    matrix* u3 = matrix_add(u1, u2);
    matrix_print(u3);

    matrix* u4 = matrix_sub(u1, u2);
    matrix_print(u4);

    
    matrix* u5 = matrix_mul(u1, u2);
    matrix_print(u5);

    double val = matrix_get(0, 0, u5);
    printf("Values %f\n\r", val);

    matrix* u6 = matrix_trans(u1);
    matrix_print(u1);
    matrix_print(u6);

    /*
    matrix_print(u1);
    matrix_print(u2);
    matrix_print(u3);
    matrix_print(u4);
    matrix_print(u5);
    matrix_print(u6);
    */
    
    return 0;
}