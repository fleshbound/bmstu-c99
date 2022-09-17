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

int show_all_movies(char *const filename, const int field_code)
{
    FILE *f = fopen(filename, "rt");

    if (f == NULL)
        return ERR_IO;

    info_movie_t movies[ALL_COUNT];
    size_t size = 0;

    for (size_t i = 0; i < ALL_COUNT; i++)
        null_info(&movies[i]);

    int err_code = get_all_movies(f, movies, &size, field_code);

    if (err_code)
        return err_code;

    fclose(f);

    for (size_t i = 0; i < size; i++)
        show_movie(movies[i], stdout);

    return EXIT_SUCCESS;
}

int is_result(info_movie_t movie, const int field_code, char *const value, int *const err_code)
{
    if (field_code == TITLE_CODE)
    {
        if (strlen(value) > LEN_TITLE - 2)
        {
            *err_code = ERR_ARGS;
            return FALSE;
        }

        if (strncmp(movie.title, value, strlen(movie.title) - 1))
            return FALSE;
    }    
    if (field_code == NAME_CODE)
    {
        if (strlen(value) > LEN_NAME - 2)
        {
            *err_code = ERR_ARGS;
            return FALSE;
        }

        if (strncmp(movie.name, value, strlen(movie.name) - 1))
            return FALSE;
    }

    if (field_code == YEAR_CODE)
    {
        int key = atoi(value);
        
        if (key <= 0)
        {
            *err_code = ERR_ARGS;
            return FALSE;
        }
        else if (movie.year != key)
            return FALSE;
    }

    return TRUE;
}

int search_movies(char *const filename, const int field_code, char *const key_value)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return ERR_IO;

    info_movie_t movies[ALL_COUNT];
    size_t size = 0;
 
    for (size_t i = 0; i < ALL_COUNT; i++)
        null_info(&movies[i]);
 
    int err_code = get_all_movies(f, movies, &size, field_code);

    if (err_code)
        return err_code;

    fclose(f);

    int printed_movies = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (is_result(movies[i], field_code, key_value, &err_code))
        {
            show_movie(movies[i], stdout);
            printed_movies++;
        }
        else if (err_code)
            return err_code;
    }

    if (printed_movies == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}
