#include <stdio.h>

int main() {
    int variavel1, variavel2;
    printf("Insira numero para variavel 1: ");
    scanf("%d", &variavel1);
    
    printf("Insira numero para variavel 2: ");
    scanf("%d", &variavel2);

   
    variavel1 = variavel1 ^ variavel2;
    variavel2 = variavel1 ^ variavel2;
    variavel1 = variavel1 ^ variavel2;

  
    printf("Valor da variavel 1 depois da troca: %d\n", variavel1);
    printf("Valor da variavel 2 depois da troca: %d\n", variavel2);

    return 0;
}