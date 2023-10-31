/*

Escreva um programa que determina as solu¸c˜oes de uma equa¸c˜ao de segundo grau. Tenha em aten¸c˜ao que existem
equa¸c˜oes que n˜ao tˆem solu¸c˜ao (real).
Exemplo
1 Insira os coeficientes da equacao (axˆ2+bx+c=0): 1 2 -15
2 A equacao xˆ2+2x-15=0 tem as solucoes x=3 e x=-5
3
4 Insira os coeficientes da equacao (axˆ2+bx+c=0): 2 3 2
5 A equacao 2xˆ2+3x+2=0 n o tem solucoes reais

*/



#include <stdio.h>
#include <math.h>

void calcSquareRoot(double a, double b, double c) {
    double discriminating = pow(b, 2) - 4 * a * c;

    // test if larger than zero (two roots)
    if (discriminating > 0) {
        double root1 = (-b + sqrt(discriminating)) / (2 * a);
        double root2 = (-b - sqrt(discriminating)) / (2 * a);

        printf("The equation has two distinct real roots: x = %.2f and x = %.2f\n", root1, root2);

    } else if (discriminating  == 0) {
        double root = -b / (2 * a);
        printf("The equation has one real root: x = %.2f\n", root);

    } else {
        printf("The equation has no real roots.\n");
    }
}

int main() {
    double a, b, c;
    
    printf("Enter the coefficients of the equation (ax^2 + bx + c = 0): ");
    scanf("%lf %lf %lf", &a, &b, &c);

    calcSquareRoot(a, b, c);


    return 0;
}