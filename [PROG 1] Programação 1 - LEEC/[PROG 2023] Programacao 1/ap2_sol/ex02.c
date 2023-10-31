/*
Escreva um programa que leia a temperatura em graus Celsius e apresente a temperatura equivalente em Kelvin
e em graus Fahrenheit. Os valores devem ser apresentados com 2 casas decimais.
Nota: k = c + 273.15 e f = c ∗ 9
5 + 32, sendo k, c e f as temperatura em graus Kelvin, Celsius e
Fahrenheit, respetivamente.

*/


#include <stdio.h>



int main (int argc, char* argv[]){
    double temperature;

    printf("Temperature ?\n");
    scanf("%lf", &temperature);


    printf("Kelvin %.2f \n", temperature + 273.15);
    printf("Fahrenheit %.2f\n", (temperature * 95 + 32));
    
    return 0;
}