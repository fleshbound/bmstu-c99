#include <stdlib.h>
#include <string.h>

#include "argch.h"
#include "errors.h"

int check_args(const int argc, char *const field, int *const field_code, int *const mode_code)
{
    if (argc == ARGC_SHOW)
        *mode_code = SHOW_CODE;
    else if (argc == ARGC_SEARCH)
        *mode_code = SEARCH_CODE;
    else 
        return ERR_ARGS;

    if (!strncmp(field, FIELD_TITLE, LEN_FIELD_MAX))
        *field_code = TITLE_CODE;

    if (!strncmp(field, FIELD_NAME, LEN_FIELD_MIN))
        *field_code = NAME_CODE;

    if (!strncmp(field, FIELD_YEAR, LEN_FIELD_MIN))
        *field_code = YEAR_CODE;

    if (*field_code == NO_CODE)
        return ERR_ARGS;

    return EXIT_SUCCESS;
}
