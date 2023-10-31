#include <stdio.h>
#include <stdbool.h>


bool isPrime(int number) {
    if (number <= 1) 
        return false;


    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) 
            return false;
        
    }
    return true;
}

int main() {
    int count, number = 2;
    printf("Enter the number of prime numbers you want: ");
    scanf("%d", &count);

    printf("The first %d prime numbers are:\n", count);


    for (int found = 0; found < count; number++) {
        if (isPrime(number)) {
            printf("%d\n", number);
            found++;
        }
    }

    return 0;
}
