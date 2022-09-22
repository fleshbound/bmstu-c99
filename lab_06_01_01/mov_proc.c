#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "movies.h"
#include "argch.h"

void show_movie(info_movie_t movie, FILE *const f)
{
    fprintf(f, "%s%s%d\n", movie.title, movie.name, movie.year);
}

void init_movies(info_movie_t *const movies)
{
    for (size_t i = 0; i < ALL_COUNT; i++)
        null_info(&movies[i]);
}

int show_all_movies(char *const filename, const int field_code)
{
    FILE *f = fopen(filename, "rt");

    if (f == NULL)
        return ERR_IO;

    info_movie_t movies[ALL_COUNT];
    init_movies(movies);
    size_t size = 0;

    int err_code = get_all_movies(f, movies, &size, field_code);

    if (err_code)
        return err_code;

    fclose(f);

    for (size_t i = 0; i < size; i++)
        show_movie(movies[i], stdout);

    return EXIT_SUCCESS;
}

int check_key(const int field_code, char *const value)
{
    switch (field_code)
    {
        case TITLE_CODE:
            if (strlen(value) > LEN_TITLE - 2)
                return ERR_ARGS;
            
            break;

        case NAME_CODE:
            if (strlen(value) > LEN_NAME - 2)
                return ERR_ARGS;
            
            break;
        
        case YEAR_CODE:
            if (atoi(value) <= 0)
                return ERR_ARGS;

            break;
    }

    return EXIT_SUCCESS;
}

void init_tmp_movie(info_movie_t *const dest, char *const value, const int field_code)
{
    null_info(dest);

    switch (field_code)
    {
        case TITLE_CODE:
            strncpy(dest->title, value, LEN_TITLE - 1);
            dest->title[strlen(value)] = '\n';
            break;

        case NAME_CODE:
            strncpy(dest->name, value, LEN_NAME - 1);
            dest->name[strlen(value)] = '\n';
            break;

        case YEAR_CODE:
            dest->year = atoi(value);
            break;
    }
}

int binary_search_movie(info_movie_t *const movies, const size_t size, 
        const int field_code, char *const value)
{
    int right = size - 1, left = 0, middle;
    info_movie_t tmp_m;
    init_tmp_movie(&tmp_m, value, field_code);

    while (left <= right)
    {
        middle = (right + left) / 2;

        if (is_first_bigger(movies[middle], tmp_m, field_code))
            right = middle - 1;
        else if (is_first_bigger(tmp_m, movies[middle], field_code))
            left = middle + 1;
        else 
            return middle;
    }

    return ALL_COUNT + 1;
}

int search_movies(char *const filename, 
        const int field_code, char *const key_value)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return ERR_IO;

    int err_code = check_key(field_code, key_value);

    if (err_code)
        return err_code;

    info_movie_t movies[ALL_COUNT];
    size_t size = 0;
    init_movies(movies);
    err_code = get_all_movies(f, movies, &size, field_code);
    
    fclose(f);

    if (err_code)
        return err_code;
    
    size_t desired_mov_i = binary_search_movie(movies, size, field_code, key_value);

    if (desired_mov_i >= ALL_COUNT)
        return ERR_EMPTY;
    
    show_movie(movies[desired_mov_i], stdout);

    return EXIT_SUCCESS;
}
