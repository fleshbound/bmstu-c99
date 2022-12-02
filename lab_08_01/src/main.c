#include <stdio.h>
#include <stdlib.h>
#include "process.h"

#define MAX_POWER 100

int main(void)
{
    size_t rows_a = 0, rows_b = 0, cols_a = 0, cols_b = 0;
    int **matrix_a = NULL, **matrix_b = NULL;
    
    int err_code = get_matrix(&matrix_a, &rows_a, &cols_a);
    if (err_code) return err_code;

    err_code = get_matrix(&matrix_b, &rows_b, &cols_b);
    if (err_code) return err_code;

    err_code = frestrict_matrix(matrix_a, &rows_a, &cols_a);
    if (err_code) return err_code;
    
    err_code = frestrict_matrix(matrix_b, &rows_b, &cols_b);
    if (err_code) return err_code;
    
    size_t size_a = rows_a, size_b = rows_b;
    err_code = make_sizes_equal(&matrix_a, &matrix_b, &size_a, &size_b);
    if (err_code) return err_code;

    int **res_matrix = NULL;
    size_t size = size_a;
    err_code = multiply_powers(size, matrix_a, matrix_b, &res_matrix);
    if (err_code) return err_code;

    free_matrix(matrix_a, size);
    free_matrix(matrix_b, size);
    output_matrix(res_matrix, size, size);
    free_matrix(res_matrix, size);

    return EXIT_SUCCESS;
}
