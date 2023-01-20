#include <stdlib.h>
#include <string.h>

#include "../inc/argch.h"
#include "../inc/errors.h"

int check_args(const int argc, char *const argv[], int *const mode_code)
{
    if (argc == ARGC_F)
        *mode_code = F_CODE;
    else if (argc == ARGC_NOF)
        *mode_code = NO_CODE;
    else 
        return ERR_ARGS;

    if ((argc == ARGC_F) && (strncmp(argv[ARGC_F - 1], STR_KEY_F, LEN_KEY_F)))
        return ERR_ARGS;

    return EXIT_SUCCESS;
}
