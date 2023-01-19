#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(void)
{
    /* int a[5] = { 3, 2, 4, 1, 5 }, rc = EXIT_SUCCESS; */
    node_t *list = NULL;

    /* for (size_t i = 0; i < 5; i++) */
    /* { */
    /*     rc = insert_value(&list, &a[i]); */

    /*     if (rc) */
    /*     { */
    /*         free_list(list); */
    /*         return rc; */
    /*     } */
    /* } */

    print_list(list);
   
    node_t *list_a = NULL;

    if (copy(list, &list_a))
    {
        free_list(list);
        return EXIT_FAILURE;
    }

    list_a = sort(list_a, compare_int);
    print_list(list_a); 

    free_list(list_a);
    free_list(list);

    return EXIT_SUCCESS;
}
