#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// STATUS: TESTED

/* Main function for testing */
int main() {
    list* my_list = list_new();
    
    list_add_first(10, my_list);
    list_add_first(20, my_list);
    list_add_last(30, my_list);
    //list_add_at(80, 2, my_list);
    list_add_last(40, my_list);

    printf("List contents: \n");
    list_print(my_list);

    printf("\nFirst element: %d\n", list_get_first(my_list));
    printf("Last element: %d\n", list_get_last(my_list));

    list_remove_first(my_list);
    printf("\nAfter removing first element:\n");
    list_print(my_list);

    list_remove_last(my_list);
    printf("\nAfter removing last element:\n");
    list_print(my_list);

    printf("\nFinal size: %d\n", list_size(my_list));

    list_free(my_list);
    return 0;
}