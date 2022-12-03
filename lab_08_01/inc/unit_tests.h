#ifndef __UNIT_TESTS_H__

#define __UNIT_TESTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#define start_test START_TEST
#define end_test END_TEST
#define suite Suite
#define srunner SRunner
#define tcase TCase

void test_free(int **data, const size_t rows);
int **test_alloc(const size_t rows, const size_t cols);
void test_fill(int *data, int ***test, const size_t rows, const size_t cols);
suite *get_matrix_suite(void);

#endif // __UNIT_TESTS_H__
