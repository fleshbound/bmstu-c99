#include "matrix.h"

my_matrix_t init_matrix(void)
{
    my_matrix_t new = { .rows = 0, .cols = 0, .data = NULL };
    return new;
}

// free matrix
void free_matrix(my_matrix_t matrix)
{
    for (size_t i = 0; i < matrix.rows; i++)
        free(matrix.data[i]);

    free(matrix.data);
}

// allocate matrix (array of pointers to rows)
my_matrix_t allocate_matrix(const size_t rows, const size_t cols)
{
    my_matrix_t matrix = { .rows = rows, .cols = cols };
    matrix.data = calloc(rows, sizeof(int *));

    if (matrix.data != NULL)
        for (size_t i = 0; i < rows; i++)
        {
            matrix.data[i] = calloc(cols, sizeof(int));

            if (matrix.data[i] == NULL)
                free_matrix(matrix);
        }

    return matrix;
}

// put multi of matrix1 and matrix2 (square: size) in res_matrix
void multiply_matrices(my_matrix_t matrix1, my_matrix_t matrix2, my_matrix_t res_matrix)
{
    int new_elem = 0;

    for (size_t i = 0; (res_matrix.data != NULL) && (i < matrix1.rows); i++)
        for (size_t j = 0; j < matrix1.rows; j++)
        {
            new_elem = 0;

            for (size_t k = 0; k < matrix1.rows; k++)
                new_elem += matrix1.data[i][k] * matrix2.data[k][j];

            res_matrix.data[i][j] = new_elem;
        }
}

// copy src to dest
void copy_matrix(my_matrix_t dest, my_matrix_t src)
{
    for (size_t i = 0; i < src.rows; i++)
        for (size_t j = 0; j < src.cols; j++)
            dest.data[i][j] = src.data[i][j];
}

// null matrix
void null_matrix(my_matrix_t matrix)
{
    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            matrix.data[i][j] = 0;
}

// set matrix (square: size) as identity matrix
void ident_matrix(my_matrix_t matrix)
{
    null_matrix(matrix);

    for (size_t i = 0; i < matrix.rows; i++)
        matrix.data[i][i] = 1;
}

// put power of matrix (square: size) in res_matrix
int power_matrix(my_matrix_t matrix, my_matrix_t res_matrix, const int power)
{
    if (power == 0)
    {
        ident_matrix(res_matrix);
        return EXIT_SUCCESS;
    }

    copy_matrix(res_matrix, matrix);
    my_matrix_t tmp;

    if (power > 1)
    {
        tmp = allocate_matrix(matrix.rows, matrix.cols);

        if (tmp.data == NULL)
            return EXIT_FAILURE;

        for (int i = 0; i < power - 1; i++)
        {
            copy_matrix(tmp, res_matrix);
            /* output_matrix(res_matrix, size, size); */
            /* output_matrix(matrix, size, size); */
            multiply_matrices(tmp, matrix, res_matrix);
        }

        free_matrix(tmp);
    }

    return EXIT_SUCCESS;
}

// delete row by row_ind
void delete_matrix_row(my_matrix_t *matrix, const size_t row_ind)
{
    int *tmp = matrix->data[row_ind];

    for (size_t i = row_ind; i < matrix->rows - 1; i++)
        matrix->data[i] = matrix->data[i + 1];

    matrix->data[matrix->rows - 1] = tmp;

    free(matrix->data[matrix->rows - 1]);
    matrix->rows--;
}

// delete column by col_ind
int delete_matrix_col(my_matrix_t *matrix, const size_t col_ind)
{
    int *tmp = NULL;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = col_ind; j < matrix->cols - 1; j++)
            matrix->data[i][j] = matrix->data[i][j + 1];

        tmp = realloc(matrix->data[i], (matrix->cols - 1) * sizeof(int));

        if (tmp == NULL)
            return EXIT_FAILURE;

        matrix->data[i] = tmp;
    }

    matrix->cols--;

    return EXIT_SUCCESS;
}

// reallocate matrix to add new column in the end
int add_matrix_col(my_matrix_t *matrix)
{
    int *tmp = NULL;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        tmp = realloc(matrix->data[i], (matrix->cols + 1) * sizeof(int));

        if (tmp == NULL)
            return EXIT_FAILURE;

        matrix->data[i] = tmp;
    }

    matrix->cols++;

    return EXIT_SUCCESS;
}

// reallocate matrix to add new row in the end
int add_matrix_row(my_matrix_t *matrix)
{
    int **tmp = realloc(matrix->data, (matrix->rows + 1) * sizeof(int *));

    if (tmp == NULL)
        return EXIT_FAILURE;

    matrix->data = tmp;
    matrix->data[matrix->rows] = malloc(matrix->cols * sizeof(int));

    if (matrix->data[matrix->rows] == NULL)
        return EXIT_FAILURE;

    matrix->rows++;

    return EXIT_SUCCESS;
}

// add new_row in the end of matrix
int add_row_to_matrix(my_matrix_t *matrix, int *new_row)
{
    if (add_matrix_row(matrix))
        return EXIT_FAILURE;

    for (size_t j = 0; j < matrix->cols; j++)
        matrix->data[matrix->rows - 1][j] = new_row[j];

    return EXIT_SUCCESS;
}

// add new_col in the end of matrix
int add_col_to_matrix(my_matrix_t *matrix, int *new_col)
{
    if (add_matrix_col(matrix))
        return EXIT_FAILURE;

    for (size_t i = 0; i < matrix->rows; i++)
        matrix->data[i][matrix->cols - 1] = new_col[i];

    return EXIT_SUCCESS;
}
