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