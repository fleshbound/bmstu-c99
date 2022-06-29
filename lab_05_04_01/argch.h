#ifndef __ARGCH_H__
  
#define __ARGCH_H__

#define ARGC_SORT 3
#define ARGC_MATCH 5
#define ARGC_DEL 3

#define NO_CODE 0
#define SORT_CODE 1
#define MATCH_CODE 2
#define DEL_CODE 3

int check_argv(const int argc, char *const argv[], int *const key_code);

int check_argc(const int argc);

#endif // #ifndef __ARGCH_H__
