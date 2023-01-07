#include <math.h>
#include "process.h"

// get indexes of maximum
void get_max_ind(my_matrix_t matrix, element_t *res)
{
    int max_elem = matrix.data[0][0];
    res->row_ind = 0;
    res->col_ind = 0;

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            if (max_elem < matrix.data[i][j])
            {
                max_elem = matrix.data[i][j];
                res->row_ind = i;
                res->col_ind = j;
            }
}

int *get_new_max_col(my_matrix_t matrix)
{
    int *new_col = calloc(matrix.rows, sizeof(int));

    if (new_col != NULL)
        for (size_t i = 0; i < matrix.rows; i++)
        {
            new_col[i] = matrix.data[i][0];
            
            for (size_t j = 0; j < matrix.cols; j++)
                if (matrix.data[i][j] > new_col[i])
                    new_col[i] = matrix.data[i][j];
        }

    return new_col;
}

int *get_new_avg_row(my_matrix_t matrix)
{
    int *new_row = malloc(matrix.cols * sizeof(int));
    int col_sum = 0;

    if (new_row != NULL)
        for (size_t j = 0; j < matrix.cols; j++)
        {
            col_sum = 0;
            
            for (size_t i = 0; i < matrix.rows; i++)
                col_sum += matrix.data[i][j];

            new_row[j] = (int) floor((double) col_sum / (double) matrix.rows);
        }

    return new_row;
}

int restrict_matrix(my_matrix_t *matrix)
{
    element_t max_elem;

    while (matrix->rows != matrix->cols)
    {
        get_max_ind(*matrix, &max_elem);
        
        if (matrix->rows > matrix->cols)
            delete_matrix_row(matrix, max_elem.row_ind);
        else if (delete_matrix_col(matrix, max_elem.col_ind))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int expand_matrix(my_matrix_t *matrix, const size_t new_size)
{
    int *new_row = NULL, *new_col = NULL;

    while (matrix->rows != new_size)
    {
        new_row = get_new_avg_row(*matrix);
        
        if ((new_row == NULL) || (add_row_to_matrix(matrix, new_row)))
            return EXIT_FAILURE;

        free(new_row);
    }

    while (matrix->cols != new_size)
    {
        new_col = get_new_max_col(*matrix);

        if ((new_col == NULL) || (add_col_to_matrix(matrix, new_col)))
            return EXIT_FAILURE;

        free(new_col);
    }

    matrix->rows = new_size;
    matrix->cols = new_size;
    return EXIT_SUCCESS;
}

int get_matrix(my_matrix_t *matrix)
{
    if ((input_size(&matrix->rows)) || (input_size(&matrix->cols)))
        return ERR_SIZE;

    *matrix = allocate_matrix(matrix->rows, matrix->cols);

    if (matrix->data == NULL)
        return ERR_MEM;

    if (input_matrix(*matrix))
    {
        free_matrix(*matrix);
        return ERR_DATA;
    }

    return EXIT_SUCCESS;
}

int frestrict_matrix(my_matrix_t *matrix)
{
    int rc = restrict_matrix(matrix);
    
    if (rc)
        free_matrix(*matrix);

    return rc;
}

int make_sizes_equal(my_matrix_t *matrix_a, my_matrix_t *matrix_b)
{
    int rc = EXIT_SUCCESS;

    if (matrix_a->rows > matrix_b->rows)
    {
        rc = expand_matrix(matrix_b, matrix_a->rows);
    }
    else if (matrix_a->rows < matrix_b->rows)
        rc = expand_matrix(matrix_a, matrix_b->rows);
    
    if (rc)
    {
        free_matrix(*matrix_a);
        free_matrix(*matrix_b);
    }

    return rc;
}

int get_matrix_power(my_matrix_t matrix, my_matrix_t *res_matrix, const int power)
{
    *res_matrix = allocate_matrix(matrix.rows, matrix.cols);
    
    if (res_matrix == NULL)
        return EXIT_FAILURE;

    if (power_matrix(matrix, *res_matrix, power))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int multiply_powers(my_matrix_t matrix_a, my_matrix_t matrix_b, my_matrix_t *res_matrix)
{
    my_matrix_t new_a, new_b;
    int power_a = 1, power_b = 1;

    if ((input_power(&power_a)) || (input_power(&power_b)))
    {
        free_matrix(matrix_a);
        free_matrix(matrix_b);
        return ERR_DATA;
    }

    if ((get_matrix_power(matrix_a, &new_a, power_a)) || (get_matrix_power(matrix_b, &new_b, power_b)))
    {
        free_matrix(matrix_a);
        free_matrix(matrix_b);
        return ERR_MEM;
    }

    *res_matrix = allocate_matrix(matrix_a.rows, matrix_a.cols);
    
    if (res_matrix->data == NULL)
    {
        free_matrix(matrix_a);
        free_matrix(matrix_b);
        free_matrix(new_a);
        free_matrix(new_b);
        return ERR_MEM;
    }

    multiply_matrices(new_a, new_b, *res_matrix);
    free_matrix(new_a);
    free_matrix(new_b);

    return EXIT_SUCCESS;
}
