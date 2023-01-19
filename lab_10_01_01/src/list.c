#include <stdio.h>
#include <stdlib.h>

#include "list.h"

node_t *alloc_elem(void *value)
{
    node_t *elem = malloc(sizeof(struct node));

    if (elem != NULL)
    {
        elem->next = NULL;
        elem->data = value;
    }

    return elem;
}

node_t *free_list(node_t *head)
{
    node_t *curr = head, *tmp;

    while (curr != NULL)
    {
        tmp = curr->next;
        free_elem(curr);
        curr = tmp;
    }

    return NULL;
}

void print_int(void *data)
{
    if (data != NULL)
        printf("%d ", *((int *) data));
}

void print_list(node_t *head)
{
    if (head == NULL)
    {
        puts("List is empty");
        return;
    }

    node_t *curr = head;

    while (curr != NULL)
    {
        print_int(curr->data);
        curr = curr->next;
    }
    
    puts("");
}

int insert_value(node_t **head, void *value)
{
    node_t *new_elem = alloc_elem(value);

    if (new_elem == NULL)
        return EXIT_FAILURE;

    *head = insert_elem(*head, new_elem);

    return EXIT_SUCCESS;
}

node_t *insert_elem(node_t *head, node_t *new_elem)
{
    new_elem->next = head;
    return new_elem;
}

node_t *insert_elem_back(node_t *head, node_t *new_elem)
{
    if (head == NULL)
        return new_elem;

    node_t *curr = head;

    while (curr->next != NULL)
        curr = curr->next;

    curr->next = new_elem;

    return head;
}

void free_elem(node_t *elem)
{
    free(elem);
}

void *pop_front(node_t **head)
{
    if (head == NULL)
        return NULL;

    if (*head == NULL)
        return NULL;

    node_t *front = *head;
    void *ret_data = front->data;

    *head = (*head)->next;
    free_elem(front);

    return ret_data;
}

void *pop_back(node_t **head)
{
    if (*head == NULL || head == NULL)
        return NULL;

    void *ret_data = NULL;

    if ((*head)->next == NULL)
    {
        ret_data = (*head)->data;
        free_elem(*head);
        *head = NULL;
        return ret_data;
    }

    node_t *curr = *head, *prev = NULL;

    while (curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    ret_data = curr->data;
    free_elem(curr);
    prev->next = NULL;

    return ret_data;
}

int copy(node_t *head, node_t **new_head)
{
    if (head == NULL)
        return EXIT_FAILURE;

    *new_head = NULL;
    node_t *curr = head, *new_elem;

    while (curr != NULL)
    {
        new_elem = alloc_elem(curr->data);

        if (new_elem == NULL)
        {
            free_list(*new_head);
            return EXIT_FAILURE;
        }

        *new_head = insert_elem_back(*new_head, new_elem);
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

int compare_int(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *new_head = NULL, *curr = head, *next;

    while (curr != NULL)
    {
        next = curr->next;
        sorted_insert(&new_head, curr, comparator);
        curr = next;
    }

    return new_head;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    node_t *curr = *head, *prev = curr;

    while ((curr != NULL) && (comparator(element->data, curr->data) > 0))
    {
        prev = curr;
        curr = curr->next;
    }

    if (prev != NULL)
    {
        if (prev != curr)
        {
            prev->next = element;
            element->next = curr;
        }
        else
        {
            element->next = prev;
            *head = element;
        }
    }
    else
    {
        *head = element;
        element->next = NULL;
    }
}
