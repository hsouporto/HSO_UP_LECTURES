/*
Escreva um programa que simula n lan¸camentos de um dado de seis lados, com n definido pelo utilizador,
apresentando ao final quantas vezes saiu a face 4.
Sugest˜ao: utilize a fun¸c˜ao rand() da biblioteca stdlib.h para gera¸c˜ao de n´umeros aleat´orios. Estude o tipo de
retorno e como definir intervalos de aleatoriedade. Por fim, considere utilizar a fun¸c˜ao srand() para alterar o
comportamento aleat´orio da fun¸c˜ao

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N_SIDES 6






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

            if ((rand() % N_SIDES + 1) == 4) {
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