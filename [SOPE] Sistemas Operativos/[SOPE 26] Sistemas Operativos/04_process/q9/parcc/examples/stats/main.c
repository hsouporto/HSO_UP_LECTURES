#include <stdio.h>
#include "stats.h"

#define MAX 1000

/* Reads numbers from stdin, e.g.  echo 3 1 4 1 5 9 | ./stats */
int main(void)
{
    double v[MAX];
    int n = read_numbers(v, MAX);
    if (n == 0) { fprintf(stderr, "no numbers read\n"); return 1; }
    printf("count = %d\n", n);
    printf("mean  = %.3f\n", mean(v, n));
    printf("min   = %.3f\n", minimum(v, n));
    printf("max   = %.3f\n", maximum(v, n));
    return 0;
}
