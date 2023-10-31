/*
Escreva uma fun¸c˜ao determina se um n´umero b est´a contido num n´umero a, ambos pedidos ao utilizador:
*/



#include <stdio.h>   
#include <stdlib.h> 
#include <math.h>
#include <string.h>


/*
How an computer scientist solve things!!! (it allows numbers and strings!!)
*/
int contains(int num_1, int num_2) {
    char *str_1 = (char*) malloc((int)((ceil(log10(num_1))+1)*sizeof(char)));
    char *str_2 = (char*) malloc((int)((ceil(log10(num_2))+1)*sizeof(char)));

    sprintf(str_1, "%d", num_1);
    sprintf(str_2, "%d", num_2);

    // compare string if contains :)

    if (strstr(str_1, str_2) != NULL) {
        free(str_1);
        free(str_2);
        return 1; // contains
    }
    else {
        free(str_1);
        free(str_2);
        return 0;
    } 


}

/*
How an electrical engeniering solve things!!!
*/
int contains_number(int num_a, int num_b) {

    while (num_a != 0) {
        if (num_a % 1000 == num_b) 
            return 1;

        num_a /= 10;    // remove one number and proceed
    }
    return 0;
}


int main() {
    int num_1, num_2;
    printf("Insira o primeiro valor: ");
    scanf("%d", &num_1);

    printf("Insira o segundo  valor: ");
    scanf("%d", &num_2);


    // using string way
    if(contains(num_1, num_2)>0){
        printf("O valor %d esta contido em %d \n", num_2, num_1);

    }

    // using numeric way
    if(contains_number(num_1, num_2)>0){
        printf("O valor %d esta contido em %d \n", num_2, num_1);

    }
    

    return 0;
}