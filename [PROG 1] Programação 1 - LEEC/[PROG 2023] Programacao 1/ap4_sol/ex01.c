/*
Escreva um programa que leia uma data composta pelo mˆes e o ano de acordo com o Calend´ario Gregoriano.
Como sa´ıda, indique o n´umero de dias desse mˆes (28, 29, 30 ou 31 dias), tendo aten¸c˜ao aos anos bissextos

*/

 #include <stdio.h>


int cal_number_days(int year, int month){
   
    if (month == 2){
        if( (year %4 == 0 && year %100 != 0) || year % 400 ==0)
            return 29;
        else
            return 28;
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11){
                return 30;
            }
            
        else{
            return 31;

        }
            
}


// main 
int main (int argc, char *argv[]){
    int year, month;

    while (1){

        printf("Insert month: ");
        scanf("%d", &month);

        if ( month < 1 || month > 12){
            printf("Invalid Month\n");
            continue;
        }
            

        printf("Insert year: ");
        scanf("%d", &year);

        if ( year < 0 ){
            printf("Invalid Year\n");
            continue;
        }
         
        int n_days = cal_number_days(year, month);
        printf("O mes %d  de %d  tem %d dias \n", month, year, n_days);



    }

    return 0;



}


