#include "unit_tests.h"
#include "matrix.h"
#include "input.h"

static int **test_data1 = NULL, **test_data2 = NULL, **res_data = NULL;

void init_multi_test(const size_t rows, const size_t cols, int *data1, int *data2)
{
    test_fill(data1, &test_data1, rows, cols);
    test_fill(data2, &test_data2, rows, cols);
    res_data = test_alloc(rows, cols);
}

void init_test(const size_t rows, const size_t cols, int *data1)
{
    test_fill(data1, &test_data1, rows, cols);
    res_data = test_alloc(rows, cols);
}

void free_test_data(const size_t rows)
{
    test_free(test_data1, rows);

    if (test_data2 != NULL)
        test_free(test_data2, rows);

    test_free(res_data, rows);
}

int cmp_res_data(const size_t rows, const size_t cols, int *data1, int **data2)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (data1[i * cols + j] != data2[i][j])
                return data1[i * cols + j] - data2[i][j];

    return 0;
}

start_test (multi_unitlen_success)
{
    int data1[1] = { 1 }, data2[1] = { 2 }, correct_res[1] = { 2 };
    size_t size = 1;
    
    init_multi_test(size, size, data1, data2);
    res_data = test_alloc(size, size);
    
    if (res_data == NULL)
        ck_abort();

    multiply_matrices(size, test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);

    free_test_data(size);
}
end_test

start_test (multi_identmatrix_success)
{
    int data1[4] = { 1, 2, 3, 4 },
        data2[4] = { 1, 0, 0, 1 },
        correct_res[4] = { 1, 2, 3, 4 };
    size_t size = 2;
    
    init_multi_test(size, size, data1, data2);
    res_data = test_alloc(size, size);
    
    if (res_data == NULL)
        ck_abort();

    multiply_matrices(size, test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);

    free_test_data(size);
}
end_test

start_test (multi_nullmatrix_success)
{
    int data1[4] = { 0, 0, 0, 0 },
        data2[4] = { 1, 2, 3, 4 },
        correct_res[4] = { 0, 0, 0, 0 };
    size_t size = 2;
    
    init_multi_test(size, size, data1, data2);
    res_data = test_alloc(size, size);
    
    if (res_data == NULL)
        ck_abort();

    multiply_matrices(size, test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);

    free_test_data(size);
}
end_test

start_test (multi_similarmatrices_success)
{
    int data1[4] = { 1, 1, 1, 1 },
        data2[4] = { 1, 1, 1, 1 },
        correct_res[4] = { 2, 2, 2, 2 };
    size_t size = 2;
    
    init_multi_test(size, size, data1, data2);
    res_data = test_alloc(size, size);
    
    if (res_data == NULL)
        ck_abort();

    multiply_matrices(size, test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);

    free_test_data(size);
}
end_test

start_test (power_nillpower_success)
{
    int data[4] = { 1, 2, 3, 4 },
        correct_res[4] = { 1, 0, 0, 1 },
        power = 0;
    size_t size = 2;

    init_test(size, size, data);
    int rc = power_matrix(size, test_data1, res_data, power);
    
    if (rc)
        ck_abort();

    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);
    free_test_data(size);
}
end_test

start_test (power_onepower_success)
{
    int data[4] = { 1, 2, 3, 4 },
        correct_res[4] = { 1, 2, 3, 4 },
        power = 1;
    size_t size = 2;

    init_test(size, size, data);
    int rc = power_matrix(size, test_data1, res_data, power);
    
    if (rc)
        ck_abort();

    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);
    free_test_data(size);
}
end_test

start_test (power_forthpower_success)
{
    int data[4] = { 1, 1, 1, 1 },
        correct_res[4] = { 8, 8, 8, 8 },
        power = 4;
    size_t size = 2;

    init_test(size, size, data);
    int rc = power_matrix(size, test_data1, res_data, power);
    
    if (rc)
        ck_abort();

    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);
    free_test_data(size);
}
end_test

start_test (power_identmatrix_success)
{
    int data[4] = { 1, 0, 0, 1 },
        correct_res[4] = { 1, 0, 0, 1 },
        power = 4;
    size_t size = 2;

    init_test(size, size, data);
    int rc = power_matrix(size, test_data1, res_data, power);
    
    if (rc)
        ck_abort();

    ck_assert(cmp_res_data(size, size, correct_res, res_data) == 0);
    free_test_data(size);
}
end_test

suite *get_matrix_suite(void)
{
    suite *s;
    tcase *tc_multi, *tc_power;
    s = suite_create("matrix.c");

    tc_multi = tcase_create("multiply_matrices");
    tcase_add_test(tc_multi, multi_unitlen_success);
    tcase_add_test(tc_multi, multi_identmatrix_success);
    tcase_add_test(tc_multi, multi_nullmatrix_success);
    tcase_add_test(tc_multi, multi_similarmatrices_success);

    tc_power = tcase_create("power_matrix");
    tcase_add_test(tc_power, power_onepower_success);
    tcase_add_test(tc_power, power_nillpower_success);
    tcase_add_test(tc_power, power_forthpower_success);
    tcase_add_test(tc_power, power_identmatrix_success);
    
    suite_add_tcase(s, tc_multi);
    suite_add_tcase(s, tc_power);

    return s;
}
