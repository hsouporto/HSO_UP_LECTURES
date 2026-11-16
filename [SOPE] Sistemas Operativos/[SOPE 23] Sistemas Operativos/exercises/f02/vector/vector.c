#include <stdlib.h>
#include <math.h>
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