#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "argch.h"
#include "errors.h"
#include "info_movie.h"

info_movie_t create_movie(char *title, char *name, const int year)
{
    info_movie_t movie = calloc(1, sizeof(struct info_movie));

    if (movie != NULL)
    {
        movie->title = title;
        movie->name = name;
        movie->year = year;
    }

    return movie;
}

void free_movie(info_movie_t *movie)
{
    free((*movie)->title);
    free((*movie)->name);
    free(*movie);
}

void show_movie(info_movie_t movie, FILE *const f)
{
    fprintf(f, "%s%s%d\n", movie->title, movie->name, movie->year);
}

bool is_space_str(char *const string)
{
    if (strlen(string) == 0)
        return TRUE;

    for (size_t i = 0; i < strlen(string) - 1; i++)
        if (!isspace(string[i]))
            return FALSE;
    
    return TRUE;
}

// allocates movie if title, name and year are read successfully
info_movie_t read_movie(FILE *const f, int *const end_flag)
{
    size_t len = 0;
    char *title = NULL, *name = NULL;
    int year;

    // if cannot read the title then it's eof
    if (getline(&title, &len, f) == -1)
    {
        free(title);
        *end_flag = TRUE;
        return NULL;
    } 
    // wrong input OR blank space
    else if (is_space_str(title))
    {
        free(title);
        return NULL;
    }

    // wrong input OR blank space
    if ((getline(&name, &len, f) == -1) || (is_space_str(name)))
    {
        free(title);
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

bool compare_titles(info_movie_t mov1, info_movie_t mov2, const bool strict)
{
    if ((strict) && (strcmp(mov1->title, mov2->title) <= 0))
        return FALSE;
    
    if ((!strict) && (strcmp(mov1->title, mov2->title) < 0))
        return FALSE;

    return TRUE;
}

bool compare_names(info_movie_t mov1, info_movie_t mov2, const bool strict)
{
    if ((strict) && (strcmp(mov1->name, mov2->name) <= 0))
        return FALSE;
    
    if ((!strict) && (strcmp(mov1->name, mov2->name) < 0))
        return FALSE;

    return TRUE;
}

bool compare_years(info_movie_t mov1, info_movie_t mov2, const bool strict)
{
    if ((strict) && (mov1->year <= mov2->year))
        return FALSE;
        
    if ((!strict) && (mov1->year < mov2->year))
        return FALSE;

    return TRUE;
}

// TRUE -- 1st is 'bigger'
// strict is a flag that equals to 1 if comparison's needed to be strict
bool compare(info_movie_t mov1, info_movie_t mov2, const int code, const bool strict)
{
    if (TITLE_CODE == code)
        return compare_titles(mov1, mov2, strict);

    if (NAME_CODE == code)
        return compare_names(mov1, mov2, strict);
    
    return compare_years(mov1, mov2, strict);
}
