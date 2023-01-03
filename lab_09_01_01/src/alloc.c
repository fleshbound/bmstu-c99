#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "alloc.h"
#include "errors.h"

/* static int alloc_count, free_count; */

info_movie_t create_movie(char *title, char *name, const int year)
{
    info_movie_t movie = calloc(1, sizeof(struct info_movie));

    if (movie != NULL)
    {
        movie->title = strdup(title);

        if (movie->title == NULL)
        {
            free_movie(&movie);
            return NULL;
        }

        movie->name = strdup(name);

        if (movie->name == NULL)
        {
            free_movie(&movie);
            return NULL;
        }

        movie->year = year;
    }

    return movie;
}

void free_movie(info_movie_t *movie)
{
    if (*movie == NULL)
        return;

    if ((*movie)->title != NULL)
        free((*movie)->title);

    if ((*movie)->name != NULL)
        free((*movie)->name);

    free(*movie);
    *movie = NULL;
}

void free_movies_data(movies_data_t *movies)
{
    if (movies->data == NULL)
        return;

    for (size_t i = 0; i < movies->size; i++)
        free_movie(&movies->data[i]);

    free(movies->data);
    movies->size = 0;
    movies->max_size = 0;
}

info_movie_t *realloc_movies_data(info_movie_t **old_data, size_t *const size)
{
    info_movie_t *data = NULL;
    void *tmp;

    if ((*size == 0) && (*old_data == NULL))
    {
        *size = ALLOC_START_SIZE;
        data = calloc(ALLOC_START_SIZE, sizeof(info_movie_t));
    }

    if ((*size != 0) && (*old_data != NULL))
    {
        tmp = realloc(*old_data, *size * ALLOC_COEF * sizeof(info_movie_t));
    
        if (tmp == NULL)
        {
            for (size_t i = 0; i < *size; i++)
                free(*old_data[i]);

            free(*old_data);
            
            return NULL;
        }

        data = tmp;
        *size = *size * ALLOC_COEF;
    }

    return data;
}
