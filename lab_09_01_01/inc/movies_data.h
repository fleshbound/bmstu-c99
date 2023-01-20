#ifndef _MOVIES_DATA_H_
#define _MOVIES_DATA_H_

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>

#include "info_movie.h"

#define ALLOC_START_SIZE 1
#define ALLOC_COEF 2

void free_movies_data(movies_data_t *movies);
int fill_movies_data(FILE *const f, movies_data_t *movies, const int field_code);

#endif
