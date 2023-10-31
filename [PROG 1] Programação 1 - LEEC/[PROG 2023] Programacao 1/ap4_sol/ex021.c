/*
Reescreva o programa usando o conceito de fun¸c˜oes. Dever´a usar a seguinte fun¸c˜ao, que retorna um
n´umero inteiro aleat´orio entre os limites inferior e superior recebidos como parˆametros:
1

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int aleatorio(int limiteInferior, int limiteSuperior){

    return limiteInferior + rand() % (limiteSuperior + 1 - limiteInferior);
}



int main(int argc, char *argv[]){
    int n_launches;
    int count =0;

    // set seed variable with time
    srand(time(0));

    // or set seed fixed
    //srand(0);

    while(1){
        printf("Please insert number of dice lauches\n");
        scanf("%d", &n_launches);

        if (n_launches < 1)
            continue;

        for (int i = 0; i < n_launches; i++) {

            if (aleatorio(2, 6) == 4) {
                count++;
            }

        }
        
        printf("A face quatro saiu %d vezes.\n", count);

        // lets doit it again
        count =0;
        printf("Another run\n");
    }

    return 0;
}
