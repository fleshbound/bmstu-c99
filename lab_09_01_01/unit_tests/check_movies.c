#include <assert.h>

#include "unit_tests.h"

static FILE *stream;

/* COMPARE */

start_test (compare_year_true)
{
    struct info_movie test_1 = { .name = "1", .title = "1", .year = 1 };
    struct info_movie test_2 = { .name = "2", .title = "2", .year = 0 };

    ck_assert(compare(&test_1, &test_2, YEAR_CODE, TRUE) == TRUE);
}
end_test

start_test (compare_s_year_false)
{
    struct info_movie test_1 = { .name = "1", .title = "1", .year = 1 };
    struct info_movie test_2 = { .name = "2", .title = "2", .year = 1 };

    ck_assert(compare(&test_1, &test_2, YEAR_CODE, TRUE) == FALSE);
}
end_test

start_test (compare_year_false)
{
    struct info_movie test_1 = { .name = "1", .title = "1", .year = 1 };
    struct info_movie test_2 = { .name = "2", .title = "2", .year = 2 };

    ck_assert(compare(&test_1, &test_2, YEAR_CODE, FALSE) == FALSE);
}
end_test

start_test (compare_title_true)
{
    struct info_movie test_1 = { .name = "1", .title = "3", .year = 1 };
    struct info_movie test_2 = { .name = "2", .title = "2", .year = 2 };

    ck_assert(compare(&test_1, &test_2, TITLE_CODE, FALSE) == TRUE);
}

start_test (compare_title_false)
{
    struct info_movie test_1 = { .name = "1", .title = "aaa", .year = 1 };
    struct info_movie test_2 = { .name = "2", .title = "bbb", .year = 2 };

    ck_assert(compare(&test_1, &test_2, TITLE_CODE, FALSE) == FALSE);
}

start_test (compare_name_true)
{
    struct info_movie test_1 = { .name = "3", .title = "1", .year = 1 };
    struct info_movie test_2 = { .name = "2", .title = "2", .year = 2 };

    ck_assert(compare(&test_1, &test_2, NAME_CODE, FALSE) == TRUE);
}

start_test (compare_name_false)
{
    struct info_movie test_1 = { .name = "aaa", .title = "1", .year = 1 };
    struct info_movie test_2 = { .name = "bbb", .title = "2", .year = 2 };

    ck_assert(compare(&test_1, &test_2, NAME_CODE, FALSE) == FALSE);
}

/* READ_MOVIE */

void open_testfile(char *filename)
{
    stream = fopen(filename, "rt");
    assert(stream);
}

void close_testfile(void)
{
    int rc = fclose(stream);
    assert(rc != EOF);
}

start_test (read_movie_empty_null)
{
    open_testfile("./unit_tests/empty.txt");
    int end_flag = 0;
    info_movie_t res = read_movie(stream, &end_flag);
    ck_assert(res == NULL);
    close_testfile();
}
end_test

start_test (read_movie_noname_null)
{
    open_testfile("./unit_tests/noname.txt");
    int end_flag = 0;
    info_movie_t res = read_movie(stream, &end_flag);
    ck_assert(res == NULL);
    close_testfile();
}
end_test

start_test (read_movie_noyear_null)
{
    open_testfile("./unit_tests/noyear.txt");
    int end_flag = 0;
    info_movie_t res = read_movie(stream, &end_flag);
    ck_assert(res == NULL);
    close_testfile();
}
end_test

start_test (read_movie_full_notnull)
{
    open_testfile("./unit_tests/full.txt");
    int end_flag = 0;
    info_movie_t res = read_movie(stream, &end_flag);
    ck_assert(res != NULL);
    close_testfile();
    free_test(&res);
}
end_test

/* CREATING SUITE */

suite *get_movies_suite(void)
{
    suite *s;
    tcase *tc_compare, *tc_read_movie;
    s = suite_create("movies.c");

    tc_compare = tcase_create("compare");
    tcase_add_test(tc_compare, compare_year_true);
    tcase_add_test(tc_compare, compare_s_year_false);
    tcase_add_test(tc_compare, compare_year_false);
    tcase_add_test(tc_compare, compare_title_true);
    tcase_add_test(tc_compare, compare_title_false);
    tcase_add_test(tc_compare, compare_name_true);
    tcase_add_test(tc_compare, compare_name_false);

    tc_read_movie = tcase_create("read_movie");
    tcase_add_test(tc_read_movie, read_movie_empty_null);
    tcase_add_test(tc_read_movie, read_movie_noname_null);
    tcase_add_test(tc_read_movie, read_movie_noyear_null);
    tcase_add_test(tc_read_movie, read_movie_full_notnull);

    suite_add_tcase(s, tc_compare);
    suite_add_tcase(s, tc_read_movie);

    return s;
}
