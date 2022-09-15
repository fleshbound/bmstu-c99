#ifndef __MOVIES_H__

#define __MOVIES_H__

#define ALL_COUNT 15
#define LEN_TITLE 26
#define LEN_NAME 26

#define NO_CODE 0
#define SHOW_CODE 1
#define SEARCH_CODE 2

#define TITLE_CODE 1
#define NAME_CODE 2
#define YEAR_CODE 3

#define FALSE 0
#define TRUE 1

typedef struct info_movie
{
    char title[LEN_TITLE];
    char name[LEN_NAME];
    int year;
} info_movie_t;

#endif // #ifndef __MOVIES_H__
