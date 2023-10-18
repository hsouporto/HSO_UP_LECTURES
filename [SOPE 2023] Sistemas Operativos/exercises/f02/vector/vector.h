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
