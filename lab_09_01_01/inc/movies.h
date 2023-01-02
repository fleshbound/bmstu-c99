#ifndef _MOVIES_H_
#define _MOVIES_H_

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>

#define FALSE 0
#define TRUE 1

struct info_movie
{
    char *title;
    char *name;
    int year;
};

typedef struct info_movie *info_movie_t;
typedef int bool;

typedef struct movies_data
{
    size_t size;
    size_t max_size;
    info_movie_t *data;
} movies_data_t;

int fget_movies(FILE *const f, movies_data_t *movies, const int field_code);
void show_movie(info_movie_t movie, FILE *const f);
bool compare(info_movie_t mov1, info_movie_t mov2, const int code, const bool strict);

#endif // #ifndef __MOVIES_H__
