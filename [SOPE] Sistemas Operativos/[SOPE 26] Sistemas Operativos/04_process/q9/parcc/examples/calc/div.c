#include "calc.h"

int divide(int a, int b, int *ok)
{
    if (b == 0) { *ok = 0; return 0; }
    *ok = 1;
    return a / b;
}
