/*
 * Вариант 1
 * Удаление строк/столбцов с максимальным элементом по матрице
 * Добавление строк: целое от среднего арифметического по столбцам (в меньшую сторону)
 * Добавление столбцов: максимумы по строкам
 */


#include <stdio.h>
#include <stdlib.h>
#include "process.h"

#define MAX_POWER 100

int get_matrices(my_matrix_t *matrix_a, my_matrix_t *matrix_b)
{
    int err_code = get_matrix(matrix_a);
    
    if (err_code)
        return err_code;

    err_code = get_matrix(matrix_b);
    
    if (err_code)
    {
        free_matrix(*matrix_a);
        return err_code;
    }

    return err_code;
}

int restrict_matrices(my_matrix_t *matrix_a, my_matrix_t *matrix_b)
{
    int err_code = frestrict_matrix(matrix_a);
    
    if (err_code)
    {
        free_matrix(*matrix_b);
        return err_code;
    }
    
    err_code = frestrict_matrix(matrix_b);
    
    if (err_code)
    {
        free_matrix(*matrix_a);
        return err_code;
    }
    
    return err_code;
}

int main(void)
{
    my_matrix_t matrix_a = init_matrix();
    my_matrix_t matrix_b = init_matrix();
    
    int rc = get_matrices(&matrix_a, &matrix_b);

    if (rc)
        return rc;

    rc = restrict_matrices(&matrix_a, &matrix_b);
    
    if (rc)
        return rc;

    rc = make_sizes_equal(&matrix_a, &matrix_b);
    
    if (rc)
        return rc;

    my_matrix_t res_matrix = init_matrix();
    rc = multiply_powers(matrix_a, matrix_b, &res_matrix);
    
    if (rc)
        return rc;

    free_matrix(matrix_a);
    free_matrix(matrix_b);

    output_matrix(res_matrix);
    free_matrix(res_matrix);

    return EXIT_SUCCESS;
}
