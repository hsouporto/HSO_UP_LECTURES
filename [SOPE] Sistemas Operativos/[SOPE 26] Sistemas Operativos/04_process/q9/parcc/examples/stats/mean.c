#include "stats.h"

double mean(const double *v, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return n ? s / n : 0;
}
