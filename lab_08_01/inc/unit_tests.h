#ifndef __UNIT_TESTS_H__

#define __UNIT_TESTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "matrix.h"

#define start_test START_TEST
#define end_test END_TEST
#define suite Suite
#define srunner SRunner
#define tcase TCase

void test_free(my_matrix_t test);
my_matrix_t test_alloc(const size_t rows, const size_t cols);
int test_fill(int *data, my_matrix_t *test, const size_t rows, const size_t cols);
suite *get_matrix_suite(void);

#endif // __UNIT_TESTS_H__
