
/*
Escreva um programa com uma fun¸c˜ao que determina o capital acumulado (ca) ao fim de n anos. Para este
c´alculo, considere um capital inicial (ci) que ´e atualizado a uma taxa de juro anual constante (j). Os valores de
ci, j e o n´umero de anos s˜ao especificados pelo utilizador (inputs).
Nota: O capital acumulado ´e calculado com a seguinte f´ormula: ca = ci ∗

1 + j
100
n

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


float compute(float ci, float tj, int n_years){
    return ci * pow((1 + (tj/100.0)), n_years);

}




int main(int argc, char *argv[]){
    float ci;
    float tj;
    int n_years;
    

    printf("Qual o capital inicial? \n");
    scanf("%f", &ci);

    printf("Qual a taxa de juro anual a ser aplicada? \n ");
    scanf("%f", &tj);

    printf("Durante quantos anos? \n");
    scanf("%d", &n_years);

    printf("O capital acumulado ao fim de %d anos eh de %f euros\n",n_years, compute(ci, tj, n_years));


    return 0;
}