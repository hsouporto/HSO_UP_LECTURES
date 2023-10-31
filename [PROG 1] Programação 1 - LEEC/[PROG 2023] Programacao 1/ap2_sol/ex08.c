#include <stdio.h>

int main() {
    float R1, R2;
    printf("Valor de R1 (em ohm)? ");
    scanf("%f", &R1);
    printf("Valor de R2 (em ohm)? ");
    scanf("%f", &R2);

   
    printf("Valor da resistencia equivalente em serie: %.4f ohm\n", R1 + R2);


    printf("Valor da resistencia equivalente em paralelo: %.4f ohm\n", (R1 * R2) / (R1 + R2));

    return 0;
}
