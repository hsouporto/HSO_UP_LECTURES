#include <stdio.h>

// swap terms
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition and set pivot to the correct place
int particionar(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// sort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = particionar(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}



int main() {
    int num_numeros;
    printf("Quantos numeros deseja ordenar? ");
    scanf("%d", &num_numeros);

    int numeros[num_numeros];
    printf("Insira %d numeros: ", num_numeros);
    for (int i = 0; i < num_numeros; i++) {
        scanf("%d", &numeros[i]);
    }


    quicksort(numeros, 0, num_numeros - 1);

    printf("Numeros em ordem ascendente: ");
    for (int i = 0; i < num_numeros; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}