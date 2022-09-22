#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "movies.h"
#include "errors.h"
#include "argch.h"

bool is_space_str(char *const string)
{
    for (size_t i = 0; i < strlen(string) - 1; i++)
        if (!isspace(string[i]))
            return FALSE;
    
    return TRUE;
}

int read_movie(FILE *const f, info_movie_t *const movie, int *const end_flag)
{
    // if cannot read the title then it's eof
    if (fgets(movie->title, LEN_TITLE, f) == NULL)
    {
        *end_flag = TRUE;
        return EXIT_SUCCESS;
    } 
    // wrong input OR blank space
    else if ((movie->title[strlen(movie->title) - 1] != '\n') 
        || (is_space_str(movie->title)))
        return ERR_DATA;

    // wrong input OR blank space OR last symbol isn't \n
    if ((fgets(movie->name, LEN_NAME, f) == NULL) 
        || (is_space_str(movie->name))
        || (movie->name[strlen(movie->name) - 1] != '\n'))
        return ERR_DATA;

    // wrong input OR negative number
    if ((fscanf(f, "%d", &movie->year) < 0)
        || (movie->year < 0))
        return ERR_DATA;

    // skipping \n after fscanf'ing the year
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

size_t max_length(char *const str1, char *const str2)
{
    return (strlen(str1) > strlen(str2)) ? strlen(str1) : strlen(str2);
}

bool is_first_bigger(info_movie_t mov1, info_movie_t mov2, const int code, const bool strict)
{
    switch (code) 
    {
        case TITLE_CODE:
            if ((strict) && (strncmp(mov1.title, mov2.title, max_length(mov1.title, mov2.title) - 1) <= 0))
                return FALSE;
            if ((!strict) && (strncmp(mov1.title, mov2.title, max_length(mov1.title, mov2.title) - 1) < 0))
                return FALSE;
            break;
        case NAME_CODE:
            if ((strict) && (strncmp(mov1.name, mov2.name, max_length(mov1.name, mov2.name) - 1) <= 0))
                return FALSE;
            if ((!strict) && (strncmp(mov1.name, mov2.name, max_length(mov1.name, mov2.name) - 1) < 0))
                return FALSE;
            break;
        case YEAR_CODE:
            if ((strict) && (mov1.year <= mov2.year))
                return FALSE;
            if ((!strict) && (mov1.year < mov2.year))
                return FALSE;
            break;
    }

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

    while ((i < size - 1) && (size > 1) && (is_first_bigger(movie, movies[i], field_code, FALSE)))
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

    if ((!is_end) && (q > ALL_COUNT))
        return ERR_DATA;

    *size = q;
    
    if (*size == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}

