#include <stdlib.h>

#include "errors.h"
#include "string.h"
#include "argch.h"

int check_argc(const int argc)
{
    if ((argc != ARGC_SORT) && (argc != ARGC_MATCH) && (argc != ARGC_DEL))
        return ERR_ARGS;
    
    return EXIT_SUCCESS;
}

int check_argv(const int argc, char *const argv[], int *const key_code)
{
    int is_sort_key = ((!strcmp(argv[1], "st")) && (argc == ARGC_SORT));
    int is_form_key = ((!strcmp(argv[1], "ft")) && (argc == ARGC_MATCH));
    int is_del_key = ((!strcmp(argv[1], "dt")) && (argc == ARGC_DEL));

    if ((!is_sort_key) && (!is_form_key) && (!is_del_key))
        return ERR_ARGS;

    if (is_sort_key)
        *key_code = SORT_CODE;
 
    if (is_form_key)
        *key_code = MATCH_CODE;
 
    if (is_del_key)
        *key_code = DEL_CODE;
    
    return EXIT_SUCCESS;
}
