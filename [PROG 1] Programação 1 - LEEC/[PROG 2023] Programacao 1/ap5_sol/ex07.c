#include <stdio.h>

int converte_codigo_cores(int cor, int pos, float *ret) {

    int multiplicador = 1;
    float valores[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // test if value is valid
    if (pos < 1 || pos > 3 || cor < 0 || cor > 9) {
        printf("Invalid values\n");
        return -1; 
    }


    switch (pos){

        case 1:
            *ret = valores[cor] * 10;
        break;

        case 2:
             *ret += valores[cor];
        break;

        case 3:
            for (int i = 0; i < cor; i++)
                multiplicador *= 10;

            *ret *= multiplicador;

        break;

        default:
        break;
    }

    return 1; 
}


int main() {
    int cor1, cor2, cor3;
    float resistencia = 0;

    printf("Introduza a cor da banda 1: ");
    scanf("%d", &cor1);
    printf("Introduza a cor da banda 2: ");
    scanf("%d", &cor2);
    printf("Introduza a cor da banda 3: ");
    scanf("%d", &cor3);

    if (converte_codigo_cores(cor1, 1, &resistencia) == -1 ||
        converte_codigo_cores(cor2, 2, &resistencia) == -1 ||
        converte_codigo_cores(cor3, 3, &resistencia) == -1) {
        printf("Valor da resistencia invalido.\n");
        return -1;
    }

    printf("Valor da resistencia: %.2f Ohms\n", resistencia);

    return 0;
}