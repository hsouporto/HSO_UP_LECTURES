/*
Escreva um programa que, atrav´es de uma fun¸c˜ao, fa¸ca uma multiplica¸c˜ao entre um qualquer n´umero e outro
que seja potˆencia de base 2 sem usar o operador de multiplica¸c˜ao “*”.

*/


#include <stdio.h>

int mulPower_2(int num, int power_factor) {
    return num << power_factor;
}

int main() {
    int num, power, res;
    printf("Insira um operando: ");
    scanf("%d", &num);

    printf("Insira outro operando (potencia de base 2): ");
    scanf("%d", &power);

    res = mulPower_2(num, power);
    printf("O resultado da multiplicacao e: %d\n", res);

    return 0;
}
