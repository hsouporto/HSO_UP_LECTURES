#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#include <stdio.h>
#include <stdlib.h>


/* Creates a new node */
node* node_new(int val, node* p) {
    node* q = (node*)malloc(sizeof(node));
    q->val = val;
    q->next = p;
    return q;
}

/* Creates a new empty list */
list* list_new() {
    list* l = (list*) malloc(sizeof(list));
    l->size = 0;
    l->first = NULL;
    return l;
}

/* Creates a new list with random values */
list* list_new_random(int size, int range) {
    list* l = list_new();
    for(int i = 0; i < size; i++) {
        list_add_first(rand() % range, l);
    }
    return l;
}

/* Adds a node at the beginning */
void list_add_first(int val, list *l) {
    node* new_node = node_new(val, l->first);
    l->first = new_node;
    l->size++;
}

/* Adds a node at the end */
void list_add_last(int val, list *l) {
    node* p = node_new(val, NULL);
    if (l->size == 0) {
        l->first = p;
    } else {
        node* q = l->first;
        while (q->next != NULL)
            q = q->next;
        q->next = p;
    }
    l->size++;
}

/* Retrieves the first element (assumes list is not empty) */
int list_get_first(list *l) {
    return l->first->val;
}

/* Retrieves the last element */
int list_get_last(list *l) {
    if (l->size == 0) {
        printf("List is empty\n");
        return -1;
    }

    node* q = l->first;
    while (q->next != NULL)
        q = q->next;
    return q->val;
}

/* Removes the first element (assumes list is not empty) */
void list_remove_first(list *l) {
    if (l->size == 0) return;

    node* p = l->first;
    l->first = l->first->next;
    free(p);
    l->size--;
}

/* Removes the last element */
void list_remove_last(list *l) {
    if (l->size == 0) return;

    if (l->size == 1) { // If there's only one element
        free(l->first);
        l->first = NULL;
    } else {
        node* q = l->first;
        while (q->next->next != NULL)
            q = q->next;
        
        free(q->next);
        q->next = NULL;
    }
    l->size--;
}

/* Returns the size of the list */
int list_size(list *l) {
    return l->size;
}

/* Prints the list */
void list_print(list* l) {
    if (l->size == 0) {
        printf("Empty List\n\n");
        return;
    }

    node* q = l->first;
    while (q != NULL) {
        printf("Value: %d -> ", q->val);
        q = q->next;
    }
    printf("NULL\n");
}


void list_add_at(int val, int pos, list *l) {
    if (pos < 0 || pos > l->size) {
        printf("Invalid position\n");
        return;
    }

    if (pos == 0) {
        list_add_first(val, l);
        return;
    }

    if (pos == l->size) {
        list_add_last(val, l);
        return;
    }

    node *new_node = node_new(val, NULL);
    node *current = l->first;

    // Traverse to the node before the desired position
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }

    // Insert the new node at the desired position
    new_node->next = current->next;
    current->next = new_node;
    l->size++;
}


/* Frees all memory allocated for the list */
void list_free(list* l) {
    node* current = l->first;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    free(l);
}

