#include "../inc/unit_tests.h"
#include "../inc/sort.h"

// MYSORT TESTING
start_test (mysort_increasing_success)
{
    size_t n = 5;
    int *a = malloc(n * sizeof(int)), *b = malloc(n * sizeof(int));

    if ((a == NULL) || (b == NULL))
        ck_abort();

    for (size_t i = 0; i < n; i++)
    {
        a[i] = i + 1;
        b[i] = i + 1;
    }

    mysort(a, n, sizeof(int), cmp_int);

    ck_assert(0 == memcmp(a, b, n));

    free(a);
    free(b);
}
end_test

start_test (mysort_decreasing_success)
{
    size_t n = 5;
    int *a = malloc(n * sizeof(int)), *b = malloc(n * sizeof(int));

    if ((a == NULL) || (b == NULL))
        ck_abort();

    for (size_t i = 0; i < n; i++)
    {
        a[i] = n - i;
        b[i] = i + 1;
    }

    mysort(a, n, sizeof(int), cmp_int);

    ck_assert(0 == memcmp(a, b, n));

    free(a);
    free(b);
}
end_test

start_test (mysort_equal_success)
{
    size_t n = 5;
    int *a = malloc(n * sizeof(int)), *b = malloc(n * sizeof(int));
    
    if ((a == NULL) || (b == NULL))
        ck_abort();
    
    for (size_t i = 0; i < n; i++)
    {
        a[i] = n;
        b[i] = n;                                               
    }
                                                                    
    mysort(a, n, sizeof(int), cmp_int);
    
    ck_assert(0 == memcmp(a, b, n));

    free(a);
    free(b);
}                                                                   
end_test

start_test (mysort_randomsigned_success)
{
    size_t n = 3;
    int *a = malloc(n * sizeof(int)), *b = malloc(n * sizeof(int));

    if ((a == NULL) || (b == NULL))
        ck_abort();

    a[0] = -5;
    a[1] = -225;
    a[2] = -1;

    b[0] = -225;
    b[1] = -5;
    b[2] = -1;

    mysort(a, n, sizeof(int), cmp_int);

    ck_assert(0 == memcmp(a, b, n));
    
    free(a);
    free(b);
}
end_test

suite *get_sort_suite(void)
{
    suite *s;
    tcase *tc_mysort;

    s = suite_create("sort.c");

    // mysort case
    tc_mysort = tcase_create("mysort");
    tcase_add_test(tc_mysort, mysort_increasing_success);
    tcase_add_test(tc_mysort, mysort_decreasing_success);
    tcase_add_test(tc_mysort, mysort_equal_success);
    tcase_add_test(tc_mysort, mysort_randomsigned_success);
    suite_add_tcase(s, tc_mysort);
    
    return s;
}
