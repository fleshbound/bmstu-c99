#ifndef __ARGCH_H__

#define __ARGCH_H__

#define ARGC_SHOW 3
#define ARGC_SEARCH 4

#define NO_CODE 0
#define SHOW_CODE 1
#define SEARCH_CODE 2

#define TITLE_CODE 1
#define NAME_CODE 2
#define YEAR_CODE 3

int check_args(const int argc, char *const field, int *const field_code, int *const mode_code);

#endif // #ifndef __ARGCH_H__
