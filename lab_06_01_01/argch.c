#include <stdlib.h>
#include <string.h>

#include "argch.h"
#include "errors.h"

int check_args(const int argc, char *const field, int *const field_code, int *const mode_code)
{
    if (argc == ARGC_SHOW)
        *mode_code = SHOW_CODE;
    
    if (argc == ARGC_SEARCH)
        *mode_code = SEARCH_CODE;

    if (*mode_code == NO_CODE)
        return ERR_ARGS;

    if (!strcmp(field, "title"))
        *field_code = TITLE_CODE;

    if (!strcmp(field, "name"))
        *field_code = NAME_CODE;

    if (!strcmp(field, "year"))
        *field_code = YEAR_CODE;

    if (*field_code == NO_CODE)
        return ERR_ARGS;

    return EXIT_SUCCESS;
}
