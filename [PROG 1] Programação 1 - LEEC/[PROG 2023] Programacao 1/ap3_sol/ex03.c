/*
Escreva um programa que leia um n´umero inteiro com um ou mais d´ıgitos e calcule a soma dos seus d´ıgitos.
1 Insira um numero? 325
2 A soma dos digitos e 10.
1

*/

#include <stdio.h>

int main() {
    int numero, soma;
    soma=0;
    printf("Insira um numero?  ");
    scanf("%d", &numero);

    while(numero >0){
        soma += numero %10;
        numero /= 10;
    }

    printf("A soma dos digitos e %d.\n", soma);

    return 0;
}