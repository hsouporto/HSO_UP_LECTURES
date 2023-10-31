#include <stdio.h>

int main() {
    int bit1, bit2, bit3, bit4;
    printf("Qual o valor em binario? ");
    scanf("%d %d %d %d", &bit1, &bit2, &bit3, &bit4);

   
    int decimal = bit4 + 2 * bit3 + 4 * bit2 + 8 * bit1;

 
    printf("O valor na base decimal: %d\n", decimal);


    int octal = bit4 + 2 * bit3 + 4 * bit2 + 8 * bit1;

  
    printf("O valor na base octal: %o\n", octal);


    int hexadecimal = bit4 + 2 * bit3 + 4 * bit2 + 8 * bit1;


    printf("O valor na base hexadecimal: %X\n", hexadecimal);

    return 0;
}
