#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define N 1

int main(void)
{
    int a[N] = { 3 }, rc = EXIT_SUCCESS;
    node_t *list = NULL;

    for (size_t i = 0; i < N; i++)
    {
        rc = insert_value(&list, &a[i]);

        if (rc)
        {
            free_list(list);
            return rc;
        }
    }

    printf("List: ");
    print_list(list);
   
    node_t *list_a = NULL;

    if (copy(list, &list_a))
    {
        free_list(list);
        return EXIT_FAILURE;
    }

    printf("Copied list: ");
    print_list(list_a);
    list_a = sort(list_a, compare_int);
    printf("Sorted list: ");
    print_list(list_a); 

    free_list(list_a);

    for (size_t i = 0; i < N; i++)
    {
        printf("Pop: ");
        print_int(pop_back(&list));
        puts("");
    }
    
    printf("List: ");
    print_list(list);

    return EXIT_SUCCESS;
}
