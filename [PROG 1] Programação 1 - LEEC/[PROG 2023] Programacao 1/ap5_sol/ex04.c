/*
Escreva uma fun¸c˜ao que conte quantas vezes um determinado d´ıgito existe num n´umero pedido ao utilizador.
Exemplo
1 Introduza um numero inteiro: 3276022
2 introduza um digito: 2
3 O digito 2 aparece 3 vezes no numero 3276022


*/

#include <stdio.h>   
#include <stdlib.h> 
#include <math.h>
#include <string.h>



int countOccurences(int num_a, int num_b) {
    int count =0;

    while(num_a !=0){
        if (num_a % 10 == num_b)
            count++;

        num_a /=10;
    }
    return count;
}




int main() {
    int num_1, num_2;
    printf("Insira o primeiro valor: ");
    scanf("%d", &num_1);

    printf("Insira o valor a procurar: ");
    scanf("%d", &num_2);


   printf("Number of occurences of %d in %d is : %d \n", num_2, num_1, countOccurences(num_1, num_2));

    

    return 0;
}