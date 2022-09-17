#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movies.h"
#include "errors.h"
#include "argch.h"

int read_movie(FILE *const f, info_movie_t *const movie, int *const end_flag)
{
    /*if (count == ALL_COUNT)
    {
        is_end = TRUE;
        return ERR_DATA;
    }*/

    if (fgets(movie->title, LEN_TITLE, f) == NULL)
    {
        *end_flag = TRUE;
        return EXIT_SUCCESS;
    }

    if (movie->title[strlen(movie->title) - 1] != '\n')
        return ERR_DATA;

    if (fgets(movie->name, LEN_NAME, f) == NULL)
        return ERR_DATA;

    if (movie->name[strlen(movie->name) - 1] != '\n')
        return ERR_DATA;

    if (fscanf(f, "%d", &movie->year) < 0)
        return ERR_DATA;

    if (movie->year < 0)
        return ERR_DATA;

    char tmp[LEN_MIN] = "";

    if (fgets(tmp, LEN_MIN, f) == NULL)
        EXIT_SUCCESS;

    return EXIT_SUCCESS;
}

void copy_movie_1to2(info_movie_t *const mov1, info_movie_t *const mov2)
{
    strncpy(mov2->title, mov1->title, LEN_TITLE);
    strncpy(mov2->name, mov1->name, LEN_NAME);
    mov2->year = mov1->year;
}

int is_first_bigger(info_movie_t mov1, info_movie_t mov2, const int code)
{
    if (code == TITLE_CODE)
        if (strncmp(mov1.title, mov2.title, (strlen(mov1.title) > strlen(mov2.title)) ? strlen(mov1.title) : strlen(mov2.title)) < 0)
            return FALSE;

    if (code == NAME_CODE)
        if (strncmp(mov1.name, mov2.name, (strlen(mov1.name) > strlen(mov2.name)) ? strlen(mov1.name) : strlen(mov2.name)) < 0)
            return FALSE;

    if (code == YEAR_CODE)
        if (mov1.year < mov2.year)
            return FALSE;

    return TRUE;
}

void null_info(info_movie_t *const movie)
{
    memset(movie->title, '\0', LEN_TITLE);
    memset(movie->name, '\0', LEN_NAME);
    movie->year = 0;
}

void add_movie(info_movie_t movies[ALL_COUNT], info_movie_t movie, const size_t size, const int field_code)
{
    size_t i = 0;

    while ((i < size - 1) && (size > 1) && (is_first_bigger(movie, movies[i], field_code)))
        i++;

    for (size_t j = size - 1; (j > i) && (size > 1); j--)
        copy_movie_1to2(&movies[j - 1], &movies[j]);
    
    copy_movie_1to2(&movie, &movies[i]);
}

int get_all_movies(FILE *const f, info_movie_t movies[ALL_COUNT], size_t *const size, const int field_code)
{
    size_t q = 0;
    int is_end = FALSE;
    int err_code = EXIT_SUCCESS;
    info_movie_t curr_movie;

    while ((!is_end) && (q < ALL_COUNT))
    {
        null_info(&curr_movie);
        err_code = read_movie(f, &curr_movie, &is_end);

        if (err_code)
            return err_code;

        if (!is_end)
            add_movie(movies, curr_movie, ++q, field_code);
    }

    *size = q;

    return EXIT_SUCCESS;
}
