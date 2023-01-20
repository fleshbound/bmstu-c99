#include "../inc/unit_tests.h"
#include "../inc/filter.h"

// KEY TESTING
start_test (key_nullbeg_src_error)
{
    int *pb_src = NULL, *pe_src = (int *) 0xDEADBEEF;
    int *pb_dest = NULL, *pe_dest = NULL;

    ck_assert(key(pb_src, pe_src, &pb_dest, &pe_dest) != EXIT_SUCCESS);
}
end_test

start_test (key_nullend_src_error)
{
    int *pb_src = (int *) 0xDEADBEEF, *pe_src = NULL;
    int *pb_dest = NULL, *pe_dest = NULL;

    ck_assert(key(pb_src, pe_src, &pb_dest, &pe_dest) != EXIT_SUCCESS);
}
end_test

start_test (key_eqbegend_src_error)
{
    int *pb_src = (int *) 0xDEADBEEF, *pe_src = pb_src;
    int *pb_dest = NULL, *pe_dest = NULL;

    ck_assert(key(pb_src, pe_src, &pb_dest, &pe_dest) != EXIT_SUCCESS);
}
end_test

start_test (key_emptyresult_error)
{
    int *a = malloc(2 * sizeof(int));
    int *pb_dest = NULL, *pe_dest = NULL;

    if (a == NULL)
        ck_abort();

    a[0] = 1;
    a[1] = 2;

    ck_assert(key(a, a + 2, &pb_dest, &pe_dest) != EXIT_SUCCESS);

    free(a);
}
end_test

start_test (key_endafterbeg_success)
{
    size_t n = 5, m = 3;
    int *a = malloc(n * sizeof(int)), *b = malloc(m * sizeof(int));
    int *pb_dest = NULL, *pe_dest = NULL;
    
    if ((a == NULL) || (b == NULL))
        ck_abort();

    for (size_t i = 0; i < n; i++)
        a[i] = i + 1;
    
    b[0] = 2;
    b[1] = 3;
    b[2] = 4;

    int rc = key(a, a + 5, &pb_dest, &pe_dest);
    
    if (rc)
        ck_abort();

    ck_assert(0 == memcmp(b, pb_dest, m));

    free(a);
    free(b);
    free(pb_dest);
}
end_test

suite *get_filter_suite(void)
{
    suite *s;
    tcase *tc_key;

    s = suite_create("filter.c");

    // key case
    tc_key = tcase_create("key");
    tcase_add_test(tc_key, key_nullbeg_src_error);
    tcase_add_test(tc_key, key_nullend_src_error);
    tcase_add_test(tc_key, key_eqbegend_src_error);
    tcase_add_test(tc_key, key_emptyresult_error);
    tcase_add_test(tc_key, key_endafterbeg_success);
    suite_add_tcase(s, tc_key);
    
    return s;
}

