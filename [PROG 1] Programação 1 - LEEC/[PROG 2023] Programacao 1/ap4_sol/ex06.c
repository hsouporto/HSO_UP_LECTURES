/*
Implemente uma fun¸c˜ao distancia que calcule a distˆancia entre dois pontos (x1, y1) e (x2, y2). Todos os parˆametros
de entrada e retorno devem ser n´umeros reais.
Utilize a f´ormula para c´alculo da distˆancia Euclidiana: dist = p(x1 − x2)2 + (y1 − y2)2
Escreva um programa que teste essa fun¸c˜ao, para dois pontos inseridos pelo utilizador. Como sugest˜ao, utilize as
fun¸c˜oes pow() (potencia¸c˜ao) e sqrt() (raiz quadrada) da biblioteca math.h para auxiliar nas opera¸c˜oes necess´arias

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


typedef struct point{
    float x;
    float y;

}point_t;



float dist(point_t a, point_t b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));

}


int main(int argc, char *argv[]){
    point_t a, b;

    printf("Insira ponto A \n");
    scanf("%f %f", &a.x, &a.y);

    printf("Insira ponto B \n");
    scanf("%f %f", &b.x, &b.y);



    printf("A distancia ecludiana  %f \n", dist(a, b));


    return 0;
}