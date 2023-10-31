/*
Implemente uma fun¸c˜ao colisao que determine se duas bolas em 2D est˜ao em colis˜ao. Cada bola ´e definida
pela posi¸c˜ao do seu centro (x, y) e raio r. Sugest˜ao: considere que as bolas est˜ao em colis˜ao se a distˆancia entre
os centros ´e menor que a soma dos raios. Use para esse efeito a fun¸c˜ao distancia implementada no problema
anterio


*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


typedef struct ball{
    float x;
    float y;
    float r;

}ball_t;



float dist(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

}


char * colision(ball_t a, ball_t b){
    
    if ( (a.r + b.r) > (dist(a.x, a.y, b.x, b.y))){
        return "In Colision \n";
    }
    else
        return "No Colision \n";

}


int main(int argc, char *argv[]){
    ball_t a, b;

    printf("Posicao (x, y) e raio da bola 1\n");
    scanf("%f %f %f", &a.x, &a.y, &a.r);

    printf("Posicao (x, y) e raio da bola 2\n");
    scanf("%f %f %f", &b.x, &b.y, &b.r);



    printf("%s \n", (char*) colision(a, b));


    return 0;
}