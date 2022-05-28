#include <stdio.h>
#include <stdlib.h>

#include ""

#define ARG_COUNT 3

#define ERR_ARGC 1

int main(int argc, char *argv)
{
    int err_code = EXIT_SUCCESS;

    if (argc != ARG_COUNT)
        err_code = ERR_ARGC;
    
    if (!err_code)
        err_code = get_pairs(argv[1], argv[2]);

    return err_code;
}
