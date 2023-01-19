#ifndef _LIST_H_
#define _LIST_H_

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

node_t *pop_end(node_t **head);
node_t *insert_elem_back(node_t *head, node_t *new_elem);
int insert_value(node_t **head, void *value);
node_t *insert_elem(node_t *head, node_t *new_elem);
void free_elem(node_t *elem);
void print_list(node_t *head);
node_t *free_list(node_t *head);
void print_int(void *data);
int compare_int(const void *a, const void *b);

// 1
void *pop_front(node_t **head);
void *pop_back(node_t **head);

// 2
int copy(node_t *head, node_t **new_head);

// 3
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

#endif
