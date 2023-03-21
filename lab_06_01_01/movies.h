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
    char title[LEN_TITLE];
    char name[LEN_NAME];
    int year;
} info_movie_t;

typedef int bool;

int get_all_movies(FILE *const f, info_movie_t movies[ALL_COUNT], size_t *const size, const int field_code);

int show_all_movies(char *const filename, const int field_code);

int search_movie(char *const filename, const int field_code, char *const key_value);

void null_info(info_movie_t *const movie);

bool compare(info_movie_t mov1, info_movie_t mov2, const int code, const bool strict);

#endif // #ifndef __MOVIES_H__
