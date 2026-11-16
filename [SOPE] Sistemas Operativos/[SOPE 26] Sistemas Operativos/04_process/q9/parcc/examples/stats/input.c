#include <stdio.h>
#include "stats.h"

int read_numbers(double *v, int max)
{
    int n = 0;
    while (n < max && scanf("%lf", &v[n]) == 1)
        n++;
    return n;
}
