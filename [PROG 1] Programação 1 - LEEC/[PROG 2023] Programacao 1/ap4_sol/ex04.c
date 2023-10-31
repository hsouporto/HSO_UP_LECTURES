/*
Implemente uma fun¸c˜ao, com parˆametros a e x, para o c´alculo de f (x) = a × x2 (par´abola). Utilize a fun¸c˜ao num
programa que apresenta os valores de f (x) para valores de x num determinado intervalo definido pelo utilizador.
O utilizador deve especificar os limites (inferior e superior) do intervalo, bem como o incremento a utilizar.

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>






float f(float a, float x){

    return a * pow(x, 2);
}



int main(int argc, char *argv[]){
    float a;
    float lower;
    float upper;
    float step;
    

    printf("Qual o valor de a? \n");
    scanf("%f", &a);

    printf("Qual o intervalo? \n ");
    scanf("%f %f", &lower, &upper);

    printf("Qual o incremento? \n");
    scanf("%f", &step);

    // lets loop
    for (float x = lower; x <= upper; x += step) {
        printf("f(%.1f) = %.1f\n", x, f(a, x));
    }


    return 0;
}
