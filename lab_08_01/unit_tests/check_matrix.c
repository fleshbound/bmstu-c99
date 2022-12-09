#include "unit_tests.h"
#include "matrix.h"
#include "input.h"

int cmp_res_data(int *data1, my_matrix_t data2)
{
    for (size_t i = 0; i < data2.rows; i++)
        for (size_t j = 0; j < data2.cols; j++)
            if (data1[i * data2.cols + j] != data2.data[i][j])
                return data1[i * data2.cols + j] - data2.data[i][j];

    return 0;
}

start_test (multi_unitlen_success)
{
    size_t size = 1;
    my_matrix_t test_data1, test_data2, res_data;
    int data1[1] = { 1 }, data2[1] = { 2 }, correct_res[1] = { 2 };
    
    int rc = test_fill(data1, &test_data1, size, size);

    if (rc)
        ck_abort();

    rc = test_fill(data2, &test_data2, size, size);

    if (rc)
    {
        test_free(test_data1);
        ck_abort();
    }

    res_data = test_alloc(size, size);        

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        test_free(test_data2);
        ck_abort();
    }
   
    multiply_matrices(test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(correct_res, res_data) == 0);

    test_free(test_data1);
    test_free(test_data2);
    test_free(res_data);
}
end_test

start_test (multi_identmatrix_success)
{
    my_matrix_t test_data1, test_data2, res_data;

    int data1[4] = { 1, 2, 3, 4 },
        data2[4] = { 1, 0, 0, 1 },
        correct_res[4] = { 1, 2, 3, 4 };
    size_t size = 2;
    int rc = test_fill(data1, &test_data1, size, size);

    if (rc)
        ck_abort();

    rc = test_fill(data2, &test_data2, size, size);

    if (rc)
    {
        test_free(test_data1);
        ck_abort();
    }

    res_data = test_alloc(size, size);        

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        test_free(test_data2);
        ck_abort();
    }
  
    multiply_matrices(test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(correct_res, res_data) == 0);
    
    test_free(test_data1);
    test_free(test_data2);
    test_free(res_data);
}
end_test

start_test (multi_nullmatrix_success)
{
    my_matrix_t test_data1, test_data2, res_data;

    int data1[4] = { 0, 0, 0, 0 },
        data2[4] = { 1, 2, 3, 4 },
        correct_res[4] = { 0, 0, 0, 0 };
    size_t size = 2;
    
    int rc = test_fill(data1, &test_data1, size, size);

    if (rc)
        ck_abort();

    rc = test_fill(data2, &test_data2, size, size);

    if (rc)
    {
        test_free(test_data1);
        ck_abort();
    }

    res_data = test_alloc(size, size);        

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        test_free(test_data2);
        ck_abort();
    }
  
    multiply_matrices(test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(correct_res, res_data) == 0);
    
    test_free(test_data1);
    test_free(test_data2);
    test_free(res_data);
}
end_test

start_test (multi_similarmatrices_success)
{
    my_matrix_t test_data1, test_data2, res_data;

    int data1[4] = { 1, 1, 1, 1 },
        data2[4] = { 1, 1, 1, 1 },
        correct_res[4] = { 2, 2, 2, 2 };
    size_t size = 2;

    int rc = test_fill(data1, &test_data1, size, size);

    if (rc)
        ck_abort();

    rc = test_fill(data2, &test_data2, size, size);

    if (rc)
    {
        test_free(test_data1);
        ck_abort();
    }

    res_data = test_alloc(size, size);        

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        test_free(test_data2);
        ck_abort();
    }

    multiply_matrices(test_data1, test_data2, res_data);
    ck_assert(cmp_res_data(correct_res, res_data) == 0);
    
    test_free(test_data1);
    test_free(test_data2);
    test_free(res_data);
}
end_test

start_test (power_nillpower_success)
{
    my_matrix_t test_data1, res_data;

    int data[4] = { 1, 2, 3, 4 },
        correct_res[4] = { 1, 0, 0, 1 },
        power = 0;
    size_t size = 2;

    int rc = test_fill(data, &test_data1, size, size);
    
    if (rc)
        ck_abort();
    
    res_data = test_alloc(size, size);

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        ck_abort();
    }

    rc = power_matrix(test_data1, res_data, power);
    
    if (rc)
    {
        test_free(test_data1);
        test_free(res_data);
        ck_abort();
    }

    ck_assert(cmp_res_data(correct_res, res_data) == 0);
     
    test_free(test_data1);
    test_free(res_data);
}
end_test

start_test (power_onepower_success)
{
    my_matrix_t test_data1, res_data;

    int data[4] = { 1, 2, 3, 4 },
        correct_res[4] = { 1, 2, 3, 4 },
        power = 1;
    size_t size = 2;

    int rc = test_fill(data, &test_data1, size, size);
    
    if (rc)
        ck_abort();
    
    res_data = test_alloc(size, size);

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        ck_abort();
    }

    rc = power_matrix(test_data1, res_data, power);
    
    if (rc)
    {
        test_free(test_data1);
        test_free(res_data);
        ck_abort();
    }
    
    ck_assert(cmp_res_data(correct_res, res_data) == 0);
     
    test_free(test_data1);
    test_free(res_data);
}
end_test

start_test (power_forthpower_success)
{
    my_matrix_t test_data1, res_data;

    int data[4] = { 1, 1, 1, 1 },
        correct_res[4] = { 8, 8, 8, 8 },
        power = 4;
    size_t size = 2;

    int rc = test_fill(data, &test_data1, size, size);
    
    if (rc)
        ck_abort();
    
    res_data = test_alloc(size, size);

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        ck_abort();
    }

    rc = power_matrix(test_data1, res_data, power);
    
    if (rc)
    {
        test_free(test_data1);
        test_free(res_data);
        ck_abort();
    }

    ck_assert(cmp_res_data(correct_res, res_data) == 0);
     
    test_free(test_data1);
    test_free(res_data);
}
end_test

start_test (power_identmatrix_success)
{
    my_matrix_t test_data1, res_data;

    int data[4] = { 1, 0, 0, 1 },
        correct_res[4] = { 1, 0, 0, 1 },
        power = 4;
    size_t size = 2;

    int rc = test_fill(data, &test_data1, size, size);
    
    if (rc)
        ck_abort();
    
    res_data = test_alloc(size, size);

    if (res_data.data == NULL)
    {
        test_free(test_data1);
        ck_abort();
    }

    rc = power_matrix(test_data1, res_data, power);
    
    if (rc)
    {
        test_free(test_data1);
        test_free(res_data);
        ck_abort();
    }

    ck_assert(cmp_res_data(correct_res, res_data) == 0);
     
    test_free(test_data1);
    test_free(res_data);
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
