#include <stdlib.h>

#include "argch.h"
#include "movies.h"

int main(int argc, char *argv[])
{
    int field_code = NO_CODE, mode_code = NO_CODE;
    int err_code = check_args(argc, argv[2], &field_code, &mode_code);

    if (err_code)
        return err_code;

    if (mode_code == SHOW_CODE)
        // file, field
        return show_movies(argv[1], field_code);

    if (mode_code == SEARCH_CODE)
        // file, field, key
        return search_movies(argv[1], field_code, argv[3]);
    
    return EXIT_SUCCESS;
}
