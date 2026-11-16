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