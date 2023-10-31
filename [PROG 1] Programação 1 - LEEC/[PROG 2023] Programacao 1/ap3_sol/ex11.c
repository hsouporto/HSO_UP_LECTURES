#include <stdio.h>

int main() {
    int altura, espacos, asteriscos;

    printf("Altura? ");
    scanf("%d", &altura);


    for (int i = 0; i < altura; i++) {
        espacos = altura - i - 1;
        asteriscos = 2 * i + 1;

        for (int j = 0; j < espacos; j++)
            printf(" ");

        // folhas
        for (int j = 0; j < asteriscos; j++)
            printf("*");

        printf("\n");
    }


    for (int i = 0; i < altura - 1; i++) 
        printf(" ");

    // pe
    printf("*\n");

    return 0;
}