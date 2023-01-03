#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "argch.h"
#include "errors.h"
#include "movies_data.h"
#include "mov_proc.h"

int show_all_movies(char *const filename, const int field_code)
{
    FILE *f = fopen(filename, "rt");

    if (f == NULL)
        return ERR_IO;

    movies_data_t movies = { .size = 0, .max_size = 0, .data = NULL };
    int err_code = fill_movies_data(f, &movies, field_code);
    
    if (fclose(f) == EOF)
    {
        free_movies_data(&movies);
        return ERR_IO;
    }

    if (err_code)
    {
        free_movies_data(&movies);
        return err_code;
    }

    for (size_t i = 0; i < movies.size; i++)
        show_movie(movies.data[i], stdout);

    free_movies_data(&movies);

    return EXIT_SUCCESS;
}

int check_key(const int field_code, char *const value)
{
    if ((YEAR_CODE == field_code) && ((strtol(value, NULL, 10) <= 0) ||
        (errno == ERANGE)))
        return ERR_ARGS;

    return EXIT_SUCCESS;
}

int binary_search_movie(movies_data_t movies, const int field_code, char *value)
{
    int right = movies.size - 1, left = 0, middle;
    info_movie_t tmp_m = create_movie(value, value, strtol(value, NULL, 10));

    if (tmp_m == NULL)
        return -1;

    while (left <= right)
    {
        middle = (right + left) / 2;

        if (compare(movies.data[middle], tmp_m, field_code, TRUE))
            right = middle - 1;
        else if (compare(tmp_m, movies.data[middle], field_code, TRUE))
            left = middle + 1;
        else
        {
            free_movie(&tmp_m); 
            return middle;
        }
    }

    free_movie(&tmp_m);

    return movies.size;
}

int search_movie(char *const filename, const int field_code, char *const key_value)
{
    int err_code = check_key(field_code, key_value);
    
    if (err_code)
        return err_code;
    
    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return ERR_IO;

    movies_data_t movies = { .size = 0, .max_size = 0, .data = NULL };
    err_code = fill_movies_data(f, &movies, field_code);
    
    if (fclose(f) == EOF)
    {
        free_movies_data(&movies);
        return ERR_IO;
    }

    if (err_code)
    {
        free_movies_data(&movies);
        return err_code;
    }
    
    int desired_mov_i = binary_search_movie(movies, field_code, key_value);

    if (desired_mov_i == (int) movies.size)
        fprintf(stderr, "Not found");
    else if (desired_mov_i == -1)
        fprintf(stderr, "Memory error");
    else 
        show_movie(movies.data[desired_mov_i], stdout);

    free_movies_data(&movies);

    return EXIT_SUCCESS;
}
