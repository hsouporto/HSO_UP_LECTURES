
/*
Escreva um programa que desenhe um retˆangulo no ecr˜a, atrav´es de um procedimento ao qual s˜ao passados trˆes
parˆametros pelo utilizador: car´ater a utilizar (char ), n´umero de linhas e n´umero de colunas.
Exemplo
1 Introduza um carater: x
2 Introduza o numero de linhas: 4
3 Introduza o numero de colunas: 6
4 xxxxxx
5 x____x
6 x____x
7 xxxxxx

*/

#include <stdio.h>


void print_rectangle(char c, int linhas, int colunas){

    for (int i = 1; i <= linhas; i++){
        for (int j = 1; j <= colunas; j++){
            if (i == 1 || i == linhas || j == 1 || j == colunas)
                printf("%c", c);
            else
                printf(" ");
        }
        printf("\n");
    }
}


int main(){
    char caractere;
    int linhas, colunas;

    printf("Introduza um carater: ");
    scanf(" %c", &caractere);
    printf("Introduza o numero de linhas: ");
    scanf("%d", &linhas);
    printf("Introduza o numero de colunas: ");
    scanf("%d", &colunas);

    print_rectangle(caractere, linhas, colunas);



    return 0;
}
