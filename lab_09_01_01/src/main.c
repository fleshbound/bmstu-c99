#include <stdlib.h>

#include "argch.h"
#include "mov_proc.h"

int main(int argc, char *argv[])
{
    int field_code = NO_CODE, mode_code = NO_CODE;
    int err_code = check_args(argc, argv[2], &field_code, &mode_code);

    if (err_code)
        return err_code;

    if (SHOW_CODE == mode_code)
        // file, field
        return show_all_movies(argv[1], field_code);

    if (SEARCH_CODE == mode_code)
        // file, field, key
        return search_movie(argv[1], field_code, argv[3]);
    
    return EXIT_SUCCESS;
}
