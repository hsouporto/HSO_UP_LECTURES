#include <stdio.h>

int main() {
    double numero;
    printf("Insira um numero: ");
    scanf("%lf", &numero);

    printf("Numero com 3 casas decimais = %.3lf\n", numero);

    int parte_inteira = (int)numero; 
    printf("Parte inteira = %d\n", parte_inteira);

    printf("Parte decimal = %.6lf\n", (double) (numero - parte_inteira));

    return 0;
}