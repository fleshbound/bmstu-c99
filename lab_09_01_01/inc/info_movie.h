#ifndef _INFO_MOVIE_H_
#define _INFO_MOVIE_H_

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

void show_movie(info_movie_t movie, FILE *const f);
bool compare(info_movie_t mov1, info_movie_t mov2, const int code, const bool strict);
info_movie_t read_movie(FILE *const f, int *const end_flag);
info_movie_t create_movie(char *title, char *name, const int year);
void free_movie(info_movie_t *movie);

#endif // #ifndef __MOVIES_H__
