/*
Implemente um programa que indique se um n´umero solicitado ao utilizador se encontra em algum dos seguintes
intervalos:
−10 5 45 120 245
Exemplo
1 Indique um numero: 50
2 O numero nao se encontra nos intervalos
3 Indique um numero: 200
4 O numero encontra-se no intervalo: ]120,245]
*/



#include <stdio.h>

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if ((number > -10 && number <= 5) || (number > 45 && number <= 120) || (number > 245))
        printf("The number falls within the specified intervals.\n");
        
    else 
        printf("The number does not fall within the specified intervals.\n");
    

    return 0;
}