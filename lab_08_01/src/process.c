#include <math.h>
#include "process.h"

// get indexes of maximum
void get_max_ind(int **matrix, const size_t rows, const size_t cols, element_t *res)
{
    int max_elem = matrix[0][0];
    res->row_ind = 0;
    res->col_ind = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (max_elem < matrix[i][j])
            {
                max_elem = matrix[i][j];
                res->row_ind = i;
                res->col_ind = j;
            }
}

int *get_new_max_col(int **matrix, const size_t rows, const size_t cols)
{
    int *new_col = calloc(rows, sizeof(int));

    if (new_col != NULL)
        for (size_t i = 0; i < rows; i++)
        {
            new_col[i] = matrix[i][0];
            
            for (size_t j = 0; j < cols; j++)
                if (matrix[i][j] > new_col[i])
                    new_col[i] = matrix[i][j];
        }

    return new_col;
}

int *get_new_avg_row(int ***matrix, const size_t rows, const size_t cols)
{
    int *new_row = malloc(cols * sizeof(int));
    int col_sum = 0;

    if (new_row != NULL)
        for (size_t j = 0; j < cols; j++)
        {
            col_sum = 0;
            
            for (size_t i = 0; i < rows; i++)
                col_sum += (*matrix)[i][j];

            new_row[j] = (int) floor((double) col_sum / (double) rows);
        }

    return new_row;
}

int restrict_matrix(int **matrix, size_t *const rows, size_t *const cols)
{
    element_t max_elem;

    while (*rows != *cols)
    {
        get_max_ind(matrix, *rows, *cols, &max_elem);
        
        if (*rows > *cols)
            delete_matrix_row(matrix, rows, max_elem.row_ind);
        else if (delete_matrix_col(matrix, *rows, cols, max_elem.col_ind))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int expand_matrix(int ***matrix, size_t *const size, const size_t new_size)
{
    size_t curr_rows = *size, curr_cols = *size;
    int *new_row = NULL, *new_col = NULL;

    while (curr_rows != new_size)
    {
        new_row = get_new_avg_row(matrix, curr_rows, curr_cols);
        
        if ((new_row == NULL) || (add_row_to_matrix(matrix, new_row, &curr_rows, curr_cols)))
            return EXIT_FAILURE;

        free(new_row);
    }

    while (curr_cols != new_size)
    {
        new_col = get_new_max_col(*matrix, curr_rows, curr_cols);

        if ((new_col == NULL) || (add_col_to_matrix(*matrix, new_col, curr_rows, &curr_cols)))
            return EXIT_FAILURE;

        free(new_col);
    }

    *size = new_size;
    return EXIT_SUCCESS;
}

int get_matrix(int ***matrix, size_t *const rows, size_t *const cols)
{
    if ((input_size(rows)) || (input_size(cols)))
        return ERR_SIZE;

    *matrix = allocate_matrix(*rows, *cols);

    if (*matrix == NULL)
        return ERR_MEM;

    if (input_matrix(*matrix, *rows, *cols))
    {
        free_matrix(*matrix, *rows);
        return ERR_DATA;
    }

    return EXIT_SUCCESS;
}

int frestrict_matrix(int **matrix, size_t *const rows, size_t *const cols)
{
    int rc = restrict_matrix(matrix, rows, cols);
    
    if (rc)
        free_matrix(matrix, *rows);

    return rc;
}

int make_sizes_equal(int ***matrix_a, int ***matrix_b, size_t *const size_a, size_t *const size_b)
{
    int rc = EXIT_SUCCESS;

    if (*size_a > *size_b)
    {
        rc = expand_matrix(matrix_b, size_b, *size_a);
    }
    else if (*size_a < *size_b)
        rc = expand_matrix(matrix_a, size_a, *size_b);
    
    if (rc)
    {
        free_matrix(*matrix_a, *size_a);
        free_matrix(*matrix_b, *size_b);
    }

    return rc;
}

int get_matrix_power(const size_t size, int **matrix, int ***res_matrix, const int power)
{
    *res_matrix = allocate_matrix(size, size);
    
    if (res_matrix == NULL)
        return EXIT_FAILURE;

    if (power_matrix(size, matrix, *res_matrix, power))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int multiply_powers(const size_t size, int **matrix_a, int **matrix_b, int ***res_matrix)
{
    int **new_a = NULL, **new_b = NULL;
    int power_a = 1, power_b = 1;

    if ((input_power(&power_a)) || (input_power(&power_b)))
    {
        free_matrix(matrix_a, size);
        free_matrix(matrix_b, size);
        return ERR_DATA;
    }

    if ((get_matrix_power(size, matrix_a, &new_a, power_a)) || (get_matrix_power(size, matrix_b, &new_b, power_b)))
    {
        free_matrix(matrix_a, size);
        free_matrix(matrix_b, size);
        return ERR_MEM;
    }

    *res_matrix = allocate_matrix(size, size);
    
    if (*res_matrix == NULL)
    {
        free_matrix(matrix_a, size);
        free_matrix(matrix_b, size);
        free_matrix(new_a, size);
        free_matrix(new_b, size);
        return ERR_MEM;
    }

    multiply_matrices(size, new_a, new_b, *res_matrix);
    free_matrix(new_a, size);
    free_matrix(new_b, size);

    return EXIT_SUCCESS;
}
