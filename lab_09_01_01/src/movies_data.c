#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "movies_data.h"
#include "errors.h"

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

int init_movies_data(movies_data_t *movies)
{
    info_movie_t *data = calloc(ALLOC_START_SIZE, sizeof(info_movie_t));
    
    if (data == NULL)
        return EXIT_FAILURE;

    movies->data = data;
    movies->max_size = ALLOC_START_SIZE;
    movies->size = 0;
    
    return EXIT_SUCCESS;
}

int realloc_movies_data(movies_data_t *movies)
{
    void *tmp = realloc(movies->data, movies->max_size * ALLOC_COEF * sizeof(info_movie_t));
    
    if (tmp == NULL)
        return EXIT_FAILURE;

    movies->data = tmp;
    movies->max_size = movies->max_size * ALLOC_COEF;

    return EXIT_SUCCESS;
}

void sorted_add_movie(movies_data_t *movies, info_movie_t movie, const int field_code)
{
    size_t i = 0;

    while ((i < movies->size - 1) && (1 < movies->size) && (compare(movie, movies->data[i], field_code, FALSE)))
        i++;

    for (size_t j = movies->size - 1; (j > i) && (1 < movies->size); j--)
        movies->data[j] = movies->data[j - 1];
 
    movies->data[i] = movie;
}

int realloc_add_movie(movies_data_t *movies, info_movie_t movie, const int field_code)
{
    if (movies->size == movies->max_size)
        if (realloc_movies_data(movies))
            return EXIT_FAILURE;
    
    movies->size++;
    sorted_add_movie(movies, movie, field_code);

    return EXIT_SUCCESS;
}

int fill_movies_data(FILE *const f, movies_data_t *movies, const int field_code)
{
    int is_end = FALSE;
    info_movie_t curr_movie = NULL;

    if (init_movies_data(movies))
        return ERR_MEM_INIT;

    while (!is_end)
    {
        curr_movie = read_movie(f, &is_end);

        if (curr_movie == NULL)
            if (!is_end)
                return ERR_DATA;
        
        if (!is_end)
            if (realloc_add_movie(movies, curr_movie, field_code))
            {
                free_movie(&curr_movie);
                return ERR_REALLOC;
            }
    }

    if (movies->size == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}
