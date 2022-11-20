#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "process.h"

#define MAX_POWER 100

int frestrict_matrix(int **matrix, size_t *const rows, size_t *const cols)
{
    int rc = restrict_matrix(matrix, rows, cols);
    
    if (rc)
        free_matrix(matrix, *rows);

    return rc;
}

int make_sizes_equal(int ***matrix_A, int ***matrix_B, size_t *const size_A, size_t *const size_B)
{
    int rc = EXIT_SUCCESS;

    if (*size_A > *size_B)
    {
        rc = expand_matrix(matrix_B, size_B, *size_A);
    }
    else
        rc = expand_matrix(matrix_A, size_A, *size_B);
    
    if (rc)
    {
        free_matrix(*matrix_A, *size_A);
        free_matrix(*matrix_B, *size_B);
    }

    return rc;
}

int get_matrix_power(const size_t size, int **matrix, int ***res_matrix, const size_t power)
{
    *res_matrix = allocate_matrix(size, size);
    
    if (res_matrix == NULL)
        return EXIT_FAILURE;

    power_matrix(size, matrix, *res_matrix, power);

    return EXIT_SUCCESS;
}

int multiply_powers(const size_t size, int **matrix_A, int **matrix_B, int ***res_matrix)
{
    int **new_A = NULL, **new_B = NULL;
    size_t power_A = 1, power_B = 1;

    if ((input_nonneg(&power_A)) | (input_nonneg(&power_B)))
    {
        free_matrix(matrix_A, size);
        free_matrix(matrix_B, size);
        return ERR_DATA;
    }

    if ((get_matrix_power(size, matrix_A, &new_A, power_A)) || (get_matrix_power(size, matrix_B, &new_B, power_B)))
    {
        free_matrix(matrix_A, size);
        free_matrix(matrix_B, size);
        return ERR_MEM;
    }
    /* power_matrix(size, matrix_A, matrix_A, power_A); */
    /* output_matrix(matrix_A, size, size); */
    /* power_matrix(size, matrix_B, matrix_B, power_B); */
    /* output_matrix(matrix_B, size, size); */

    *res_matrix = allocate_matrix(size, size);
    
    if (*res_matrix == NULL)
    {
        free_matrix(matrix_A, size);
        free_matrix(matrix_B, size);
        return ERR_MEM;
    }

    multiply_matrices(size, new_A, new_B, *res_matrix);
    free_matrix(new_A, size);
    free_matrix(new_B, size);

    return EXIT_SUCCESS;
}

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
