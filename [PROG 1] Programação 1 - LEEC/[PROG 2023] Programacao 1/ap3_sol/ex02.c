/*
Escreva um programa que leia um ponto (coordenadas x, y) e indique em que quadrante se encontra.
Exemplo
1 Indique o ponto (x,y): -4 5
2 O ponto encontra-se no 2o quadrante.
*/


#include <stdio.h>

typedef struct point_t{
    int x;
    int y;
}point_t;


void determineQuadrant(point_t p){

    if (p.x > 0 && p.y > 0) {
        printf("O ponto encontra-se no 1o quadrante.\n");
    } else if (p.x < 0 && p.y > 0) {
        printf("O ponto encontra-se no 2o quadrante.\n");
    } else if (p.x < 0 && p.y < 0) {
        printf("O ponto encontra-se no 3o quadrante.\n");
    } else if (p.x > 0 && p.y < 0) {
        printf("O ponto encontra-se no 4o quadrante.\n");
    } else if (p.x == 0 && p.y != 0) {
        printf("O ponto está sobre o eixo das ordenadas.\n");
    } else if (p.x != 0 && p.y == 0) {
        printf("O ponto está sobre o eixo das abscissas.\n");
    } else {
        printf("O ponto está na origem.\n");
    }


}


int main() {
    point_t point;
    printf("Indique o ponto (x, y): ");
    scanf("%d %d", &point.x, &point.y);

    determineQuadrant(point);

    return 0;
}