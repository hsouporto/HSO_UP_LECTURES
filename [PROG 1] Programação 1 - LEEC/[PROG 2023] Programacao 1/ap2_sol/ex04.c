/*
Escreva um programa que leia dois n´umeros inteiros e indique se o primeiro ´e m´ultiplo do segundo.
Exemplo
1 Numero inteiro 1? 336
2 Numero inteiro 2? 7
3 336 e multiplo de 7
4
5 ---
6
7 Numero inteiro 1? 210
8 Numero inteiro 2? 9
9 210 nao e multiplo de 9
*/




#include <stdio.h>

#define IS_MULTIPLE(n, m) ((n) % m == 0) ? 1 : 0

int main(int argc, char *argv[]){
    int a, b;

    printf("Number ?\n");
    scanf("%d", &a);

    printf("Number ?\n");
    scanf("%d", &b);


    if (IS_MULTIPLE(a, b))
        printf("%d is not a multiople of %d \n", b, a);

    else
        printf("%d is  a multiople of %d \n", b, a);

    return 0;
}