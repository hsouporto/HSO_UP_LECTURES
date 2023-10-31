

#include <stdio.h>
#include <stdlib.h>

float fatorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * fatorial(n - 1);
}

double seno(double x, double tolerancia) {
    double termo = x;
    double soma = termo;
    int n = 1;

    while (abs(termo > tolerancia)) {
        n += 2;
        termo = -termo * x * x / (n * (n - 1));
        soma += termo;
    }

    return soma;
}

int main() {
    double x, tolerancia;
    printf("Qual o valor de x? ");
    scanf("%lf", &x);
    printf("Qual o valor da tolerancia? ");
    scanf("%lf", &tolerancia);

    printf("O seno de %.2lf e' %.6lf\n", x, seno(x, tolerancia));

    return 0;
}