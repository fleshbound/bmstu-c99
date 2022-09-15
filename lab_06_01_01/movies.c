#include <stdio.h>
#include <stdlib.h>

#include "movies.h"
#include "errors.h"



int get_all_movies(FILE *const f, info_movie_t movies[ALL_COUNT], size_t *const size, const int field_code)
{
    size_t q = 0;
    int is_end = FALSE;
    int err_code = EXIT_SUCCESS;
    info_movie_t curr_movie;

    while (!is_end)
    {
        null_info(&curr_movie);
        err_code = read_movie(&curr_movie, &is_end);

        if (err_code)
            return err_code;

        if (!is_end)
            add_movie(movies, curr_movie, q++);
    }

    *size = q;

    return EXIT_SUCCESS;
}
