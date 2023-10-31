#include <stdio.h>

int main() {
    int totalSegundos, dias, horas, minutos, segundos;
    printf("Quantos segundos? ");
    scanf("%d", &totalSegundos);

   
    dias = totalSegundos / (24 * 3600);
    totalSegundos = totalSegundos % (24 * 3600);

    horas = totalSegundos / 3600;
    totalSegundos = totalSegundos % 3600;
    
    minutos = totalSegundos / 60;
    segundos = totalSegundos % 60;


    printf("%d segundos correspondem a %d dia(s), %d hora(s), %d minuto(s) e %d segundo(s)\n",
           totalSegundos, dias, horas, minutos, segundos);

    return 0;
}


