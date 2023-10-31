

#include <stdio.h>

#define PI 3.1416


int main (int argc, char* argv[]){
    double radius, perimeter;

    printf("Raio ?\n");
    scanf("%lf", &radius);


    printf("Area %lf \n", PI * radius* radius);
    printf("Perimeter %lf \n", 2* PI * radius);
    
   
    return 0;
}