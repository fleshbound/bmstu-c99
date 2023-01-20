#ifndef _LIST_H_
#define _LIST_H_

typedef struct node *list_t;

struct node
{
    void *data;
    list_t next;
};

list_t insert_elem_back(list_t head, list_t new_elem);
int insert_value(list_t *head, void *value);
list_t insert_elem(list_t head, list_t new_elem);
void free_elem(list_t elem, void (*free_data)(void *));
void print_list(list_t head, void (*print_data)(void *));
list_t free_list(list_t head, void (*free_data)(void *));
int compare_int(const void *a, const void *b);
list_t alloc_elem(void *value);
void sorted_insert(list_t *head, list_t element, int (*comparator)(const void *, const void *));

// 1
void *pop_front(list_t *head);
void *pop_back(list_t *head);

// 2
int copy(list_t head, list_t *new_head, void (*free_data)(void *));

// 3
list_t sort(list_t head, int (*comparator)(const void *, const void *));
void sorted_insert(list_t *head, list_t element, int (*comparator)(const void *, const void *));

#endif
