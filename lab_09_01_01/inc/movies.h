#include <stdio.h>
#ifndef __MOVIES_H__

#define __MOVIES_H__

#define ALL_COUNT 15
#define LEN_TITLE 25 + 2
#define LEN_NAME 25 + 2
#define LEN_MIN 5
#define FALSE 0
#define TRUE 1

typedef struct info_movie
{
    char *title;
    char *name;
    int year;
} info_movie_t;

typedef int bool;
typedef int (*cmp_func_ptr)(void *mem1, void *mem2);

typedef struct movies_data
{
    size_t size;
    cmp_func_ptr cmp_title;
    cmp_func_ptr cmp_name;
    cmp_func_ptr cmp_year;
    info_movie_t data[];
} movies_data_t;

int fget_movies(FILE *const f, info_movie_t *movies, size_t *const size, const int field_code);

int show_movies(char *const filename, const int field_code);

int search_movie(char *const filename, const int field_code, char *const key_value);

void null_info(info_movie_t *const movie);

#endif // #ifndef __MOVIES_H__
