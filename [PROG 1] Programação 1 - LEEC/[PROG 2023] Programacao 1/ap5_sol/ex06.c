
/*
Um ripple carry adder ´e um circuito digital constitu´ıdo por N full adders de 1 bit em cascata, que permite adicionar
dois n´umeros bin´arios de N bits1. Implemente a seguinte fun¸c˜ao, que recebe dois n´umeros bin´arios e retorna o
resultado da sua soma.
1 int soma_binario(int a, int b);
A soma dos dois n´umeros pode ser feita recorrendo a N full adders, em que cada um soma cada algarismo de
ambos os operandos, tendo em conta n˜ao s´o esses algarismos, mas tamb´em o carry-in da soma anterior. Este
m´odulo produz o resultado da soma dos dois algarismos e o carry-out, usado na soma dos algarismos seguintes
como carry-in.
*/



#include <stdio.h>   
#include <stdlib.h> 
#include <math.h>
#include <string.h>

int soma_binario(int a, int b) {
    int res = 0; 
    int cr = 0; 
    int bit_mask = 1;

    while (a > 0 || b > 0) {
       
        // extract the lower bit from both numbers 
        int bit_a = a % 10;     
        int bit_b = b % 10;

        // apply the adder expression
        int bit_soma = bit_a ^ bit_b ^ cr;

        // propagating carry accordinly, 1 + 1 -> cr = 1 
        cr = (bit_a & bit_b) | (cr & (bit_a ^ bit_b));

        // accumulate the sum with actual value stored
        res = bit_soma * bit_mask + res;

        // proccced to next bit
        a /= 10;
        b /= 10;

        bit_mask *= 10;      // next number (since we represent binary in a integer representation), to go next bit just multyply by 10)
    }

    // final carry addition
    if (cr) {
        res = bit_mask + res;
    }

    return res;
}


int main() {
    int a, b;


    printf("Insira o primeiro valor: ");
    scanf("%d", &a);

    printf("Insira o segundo valor : ");
    scanf("%d", &b);

    printf("A soma dos dois numeros binarios e %d \n", soma_binario(a, b));


    return 0;
}