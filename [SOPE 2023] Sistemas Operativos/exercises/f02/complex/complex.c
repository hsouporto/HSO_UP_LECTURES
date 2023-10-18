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
    return complex_new(z->x * w->x - z->y * w->y, z->x * w->y + z->y * w->x);
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
return atan2(z->y, z->x);
}

double complex_re(complex* z){
    return z->x;
}

double complex_im(complex* z){
    return z->y;
}
