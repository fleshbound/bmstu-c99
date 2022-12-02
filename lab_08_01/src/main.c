#include <stdio.h>
#include <stdlib.h>
#include "process.h"

#define MAX_POWER 100

int main(void)
{
    size_t rows_A = 0, rows_B = 0, cols_A = 0, cols_B = 0;
    int **matrix_A = NULL, **matrix_B = NULL;
    
    int err_code = get_matrix(&matrix_A, &rows_A, &cols_A);
    if (err_code) return err_code;

    err_code = get_matrix(&matrix_B, &rows_B, &cols_B);
    if (err_code) return err_code;

    err_code = frestrict_matrix(matrix_A, &rows_A, &cols_A);
    if (err_code) return err_code;
    
    err_code = frestrict_matrix(matrix_B, &rows_B, &cols_B);
    if (err_code) return err_code;
    
    size_t size_A = rows_A, size_B = rows_B;
    err_code = make_sizes_equal(&matrix_A, &matrix_B, &size_A, &size_B);
    if (err_code) return err_code;

    int **res_matrix = NULL;
    size_t size = size_A;
    err_code = multiply_powers(size, matrix_A, matrix_B, &res_matrix);
    if (err_code) return err_code;

    free_matrix(matrix_A, size);
    free_matrix(matrix_B, size);
    output_matrix(res_matrix, size, size);
    free_matrix(res_matrix, size);

    return EXIT_SUCCESS;
}
