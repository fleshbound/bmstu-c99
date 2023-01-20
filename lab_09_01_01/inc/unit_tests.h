#ifndef _UNIT_TESTS_H_
#define _UNIT_TESTS_H_

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "info_movie.h"

#define start_test START_TEST
#define end_test END_TEST
#define suite Suite
#define srunner SRunner
#define tcase TCase

#define TITLE_CODE 1
#define NAME_CODE 2
#define YEAR_CODE 3

void free_test(info_movie_t *test);
suite *get_movies_suite(void);

#endif
