#include <stdio.h>

int main() {
    float populationA, populationB, rateA, rateB;
    int years = 0;


    printf("Country A (population/rate): ");
    scanf("%f %f", &populationA, &rateA);
    
    printf("Country B (population/rate): ");
    scanf("%f %f", &populationB, &rateB);

  
    while (populationA >= populationB) {
        populationA += (rateA / 100) * populationA;
        populationB += (rateB / 100) * populationB;
        years++;
    }

    // Printing the result
    printf("Population of B will surpass A in %d years.\n", years);

    return 0;
}
