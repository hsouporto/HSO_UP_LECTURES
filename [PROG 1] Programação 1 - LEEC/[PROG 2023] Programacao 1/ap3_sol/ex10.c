
#include <stdio.h>
#include <float.h>

int main() {
    float num, min = FLT_MAX, max = -FLT_MAX, sum = 0.0;
    int count = 0;

    while (1) {
        if (scanf("%f", &num) != 1) {
            break;
        }

        sum += num;
        count++;

        if (num < min)
            min = num;


        if (num > max) 
            max = num;
    }

    if (count > 0) {
        float average = sum / count;
        printf("A media dos numeros e %.2f, o maximo e %.2f e o minimo e %.2f.\n", average, max, min);
    } else {
        printf("Nenhum numero foi inserido.\n");
    }

    return 0;
}