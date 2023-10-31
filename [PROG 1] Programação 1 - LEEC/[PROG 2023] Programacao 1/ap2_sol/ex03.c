/*
Escreva um programa que leia um n´umero inteiro e indique se este ´e par ou ´ımpar.
1

*/

#include <stdio.h>

#define IS_EVEN(n) ((n) % 2 == 0) ? 1 : 0

int main(int argc, char *argv[]){
    int number;

    printf("Number ?\n");
    scanf("%d", &number);

    if (IS_EVEN(number))
        printf("%d is an even number.\n", number);

    else
        printf("%d is an odd number.\n", number);

    return 0;
}
