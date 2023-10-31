/*
Escreva um programa que verifique se um n´umero de trˆes d´ıgitos ´e capicua.
Exemplo
1 Insira um numero de 3 digitos: 232
2 O numero e capicua
3 Insira um numero de 3 digitos: 332
4 O numero nao e capicua

*/


#include <stdio.h>

int main() {
    int number, original, reverse = 0;
    printf("Enter a three-digit number: ");
    scanf("%d", &number);

    original = number;

    while (number != 0) {
        reverse = reverse * 10 + number % 10;
        number /= 10;
    }

 
    if (original == reverse) {
        printf("The number is a palindrome.\n");
    } else {
        printf("The number is not a palindrome.\n");
    }

    return 0;
}