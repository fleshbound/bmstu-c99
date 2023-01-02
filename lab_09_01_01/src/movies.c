#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "alloc.h"
#include "argch.h"
#include "errors.h"
#include "movies.h"

void show_movie(info_movie_t movie, FILE *const f)
{
    fprintf(f, "%s%s%d\n", movie->title, movie->name, movie->year);
}

bool is_space_str(char *const string)
{
    for (size_t i = 0; i < strlen(string) - 1; i++)
        if (!isspace(string[i]))
            return FALSE;
    
    return TRUE;
}

int copy_movie(info_movie_t dst, info_movie_t src)
{
    char *title = strdup(src->title);

    if (title == NULL)
        return EXIT_FAILURE;

    free(dst->title);
    dst->title = title;

    char *name = strdup(src->name);

    if (name == NULL)
        return EXIT_FAILURE;

    free(dst->name);
    dst->name = name;

    dst->year = src->year;

    return EXIT_SUCCESS;
}

info_movie_t read_movie(FILE *const f, int *const end_flag)
{
    size_t len = 0;
    char *title = NULL, *name = NULL;
    int year;

    // if cannot read the title then it's eof
    if (getline(&title, &len, f) == -1)
    {
        *end_flag = TRUE;
        return NULL;
    } 
    // wrong input OR blank space
    else if ((title[len - 1] - 1 != '\n') || (is_space_str(title)))
    {
        free(title);
        return NULL;
    }

    // wrong input OR blank space OR last symbol isn't \n
    if ((getline(&name, &len, f) == -1) || (is_space_str(name)) ||
        (name[len - 1] == '\n'))
    {
        free(title);

        if (name != NULL)
            free(name);

        return NULL;
    }

    // wrong input OR negative number
    if ((fscanf(f, "%d", &year) < 0) || (year < 0))
    {
        free(title);
        free(name);
        return NULL;
    }

    // skipping \n after fscanf'ing the year
    fgetc(f);

    info_movie_t movie = create_movie(title, name, year);

    return movie;
}

size_t max_length(char *const str1, char *const str2)
{
    return (strlen(str1) > strlen(str2)) ? strlen(str1) : strlen(str2);
}

// strict - flag; equals to 1 if comparison's needed to be strict
bool compare(info_movie_t mov1, info_movie_t mov2, const int code, const bool strict)
{
    if (TITLE_CODE == code)
    {
        if ((strict) && (strncmp(mov1->title, mov2->title, max_length(mov1->title, mov2->title) - 1) <= 0))
            return FALSE;
        
        if ((!strict) && (strncmp(mov1->title, mov2->title, max_length(mov1->title, mov2->title) - 1) < 0))
            return FALSE;
    }

    if (NAME_CODE == code)
    {
        if ((strict) && (strncmp(mov1->name, mov2->name, max_length(mov1->name, mov2->name) - 1) <= 0))
            return FALSE;
        
        if ((!strict) && (strncmp(mov1->name, mov2->name, max_length(mov1->name, mov2->name) - 1) < 0))
            return FALSE;
    }
    
    if (YEAR_CODE == code)
    {
        if ((strict) && (mov1->year <= mov2->year))
            return FALSE;
        
        if ((!strict) && (mov1->year < mov2->year))
            return FALSE;
    }

    return TRUE;
}

int add_movie(movies_data_t *movies_data, info_movie_t movie, const int field_code)
{
    if (movies_data->size == movies_data->max_size)
    {
        movies_data->data = realloc_movies_data(movies_data->data, &movies_data->max_size);
        
        if (movies_data->data == NULL)
            return ERR_MEM;
    } 

    size_t i = 0;

    while ((i < movies_data->size - 1) && (1 < movies_data->size) &&
           (compare(movie, movies_data->data[i], field_code, FALSE)))
        i++;

    for (size_t j = movies_data->size - 1; (j > i) && (1 < movies_data->size); j--)
        if (copy_movie(movies_data->data[j], movies_data->data[j - 1]))
            return ERR_MEM;
    
    if (copy_movie(movies_data->data[i], movie))
        return ERR_MEM;

    movies_data->size++;
    return EXIT_SUCCESS;
}

int fget_movies(FILE *const f, movies_data_t *movies, const int field_code)
{
    int is_end = FALSE;
    info_movie_t curr_movie = NULL;

    while (!is_end)
    {
        curr_movie = read_movie(f, &is_end);

        if ((curr_movie == NULL) && (!is_end))
            return ERR_MEM;

        if (!is_end)
            if (add_movie(movies, curr_movie, field_code))
                return ERR_MEM;
    }

    if (!is_end)
        return ERR_DATA;

    if (movies->size == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}
