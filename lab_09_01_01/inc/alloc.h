#ifndef _ALLOC_H_
#define _ALLOC_H_

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>

#include "movies.h"

#define ALLOC_START_SIZE 1
#define ALLOC_COEF 2

info_movie_t create_movie(char *title, char *name, const int year);
void free_movie(info_movie_t *movie);
void free_movies_data(movies_data_t *movies);
info_movie_t *realloc_movies_data(info_movie_t **old_data, size_t *const size);

#endif
