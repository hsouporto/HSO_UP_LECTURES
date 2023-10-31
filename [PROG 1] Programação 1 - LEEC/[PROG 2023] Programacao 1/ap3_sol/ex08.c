#include <stdio.h>


void convertToRoman(int num) {
   
    char *roman[] = {"C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[] = {100, 90, 50, 40, 10, 9, 5, 4, 1};

    for (int i = 0; i < 9; i++) {
        while (num >= values[i]) {
            printf("%s", roman[i]);
            num -= values[i];
        }
    }
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (number < 1 || number > 100) {
        printf("Number out of range.\n");
        return 1;
    }

    printf("Roman Numerals: ");
    convertToRoman(number);
    
    printf("\n");

    return 0;
}
