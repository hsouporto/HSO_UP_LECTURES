

#include <stdio.h>

#define ROUND(numero) ((numero)% 2 == 0) ? (numero) : (numero + 1)

int main() {
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);

    printf("Os dois números pares mais próximos de %d são %d e %d\n", numero, ROUND(numero) - 2, ROUND(numero) + 2);;

    return 0;
}
