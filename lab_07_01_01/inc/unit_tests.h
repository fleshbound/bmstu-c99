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

suite *get_filter_suite(void);

suite *get_sort_suite(void);

#endif // __UNIT_TESTS_H__
