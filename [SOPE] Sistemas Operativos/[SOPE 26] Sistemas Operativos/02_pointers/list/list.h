/* definition of new type list */
typedef struct anode {
    int val;
    struct anode* next;
} node;

typedef struct {
    int size;
    node* first;
} list;

/* definition of the list API */
node* node_new(int, node*);
list* list_new();
list* list_new_random(int, int);
void list_add_first(int, list *);
void list_add_last(int, list *);
int list_get_first(list *);
int list_get_last(list *);
void list_remove_first(list *);
void list_remove_last(list *);
int list_size(list *);
void list_print(list *);
void list_free(list *);
void list_add_at(int, int, list *l);
