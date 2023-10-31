/*
Escreva um programa que calcule o peso ideal de uma pessoa (em quilos) sabendo que para homens, pesoideal =
72.7 × altura − 58, e para mulheres, pesoideal = 62.1 × altura–44.7. O c´alculo dever´a ser feito por uma fun¸c˜ao,
que recebe como argumentos a altura (em metros) e o sexo da pessoa
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


#define N_SIDES 6



float computeIdealweight (float height, char sex){

    if (sex == 'f')
        return 72.7 * height - 58;
    else
        return 62.1 * height - 44.7;
}



int main(int argc, char *argv[]){
    float height;
    float ideal;
    char sex = 'M'; // male by default


    while(1){
        printf("Please insert person height \n");
        scanf("%f", &height);

        if (height < 0)
            continue;

        printf("Please insert person gender \n");
        scanf(" %c", &sex);    

        // and good practtice in this if to convert averthing to lowwer or upper to be case invariant
        sex = tolower(sex);

        if (sex=='m' || sex=='f'){
            ideal = computeIdealweight(height, sex);
        
        }else {
            printf("Invalif option inserted, repeat \n");
            continue;
        }

        printf("Peso ideal e %.2f \n", ideal); // forma with only 2 decimal cases

        // lets doit it again
        printf("Another run\n");
    }

    return 0;
}