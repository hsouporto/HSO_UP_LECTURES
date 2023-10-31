#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// STATUS: TESTED

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