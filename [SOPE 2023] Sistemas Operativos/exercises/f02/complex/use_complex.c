#include <stdio.h>
#include <stdlib.h>

// STATUS: TESTED

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