#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

/* Usage: ./calc 12 + 4   (operators: + - x /) */
int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s a op b   (op is + - x /)\n", argv[0]);
        return 1;
    }
    int a = atoi(argv[1]), b = atoi(argv[3]), ok = 1, r = 0;

    switch (argv[2][0]) {
    case '+': r = add(a, b); break;
    case '-': r = sub(a, b); break;
    case 'x': r = mul(a, b); break;
    case '/': r = divide(a, b, &ok); break;
    default:
        fprintf(stderr, "unknown operator '%s'\n", argv[2]);
        return 1;
    }
    if (!ok) { fprintf(stderr, "division by zero\n"); return 1; }
    printf("%d %s %d = %d\n", a, argv[2], b, r);
    return 0;
}
