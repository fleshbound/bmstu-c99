#include "matrix.h"

// free matrix
void free_matrix(int **matrix, const size_t rows)
{
    for (size_t i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}

// allocate matrix (array of pointers to rows)
int **allocate_matrix(const size_t rows, const size_t cols)
{
    int **matrix = calloc(rows, sizeof(int *));

    if (matrix != NULL)
        for (size_t i = 0; i < rows; i++)
        {
            matrix[i] = calloc(cols, sizeof(int));

            if (matrix[i] == NULL)
            {
                free_matrix(matrix, rows);
                return NULL;
            }
        }

    return matrix;
}

// put multi of matrix1 and matrix2 (square: size) in res_matrix
void multiply_matrices(const size_t size, int **matrix1, int **matrix2, int **res_matrix)
{
    int new_elem = 0;

    for (size_t i = 0; (res_matrix != NULL) && (i < size); i++)
        for (size_t j = 0; j < size; j++)
        {
            new_elem = 0;

            for (size_t k = 0; k < size; k++)
                new_elem += matrix1[i][k] * matrix2[k][j];
            
            res_matrix[i][j] = new_elem;
        }
}

// copy src to dest
void copy_matrix(int **dest, int **src, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            dest[i][j] = src[i][j];
}

// null matrix
void null_matrix(int **matrix, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            matrix[i][j] = 0;
}

// set matrix (square: size) as identity matrix
void ident_matrix(int **matrix, const size_t size)
{
    null_matrix(matrix, size, size);

    for (size_t i = 0; i < size; i++)
        matrix[i][i] = 1;
}

// put power of matrix (square: size) in res_matrix
void power_matrix(const size_t size, int **matrix, int **res_matrix, const size_t power)
{
    if (power == 0)
    {
        ident_matrix(res_matrix, size);
        return;
    }

    if (power == 1)
    {
        copy_matrix(res_matrix, matrix, size, size);
        return;
    }

    // 0
    multiply_matrices(size, matrix, matrix, res_matrix);

    for (size_t i = 1; i < power - 1; i++)
        multiply_matrices(size, res_matrix, matrix, res_matrix);
}

// delete row by row_ind
void delete_matrix_row(int **matrix, size_t *const rows, const size_t row_ind)
{
    int *tmp = matrix[row_ind];

    for (size_t i = row_ind; i < *rows - 1; i++)
        matrix[i] = matrix[i + 1];

    matrix[*rows - 1] = tmp;

    free(matrix[*rows - 1]);
    (*rows)--;
}

// delete column by col_ind
int delete_matrix_col(int **matrix, const size_t rows, size_t *const cols, const size_t col_ind)
{
    int *tmp = NULL;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = col_ind; j < *cols - 1; j++)
           matrix[i][j] = matrix[i][j + 1];
        
        tmp = realloc(matrix[i], (*cols - 1) * sizeof(int));

        if (tmp == NULL)
            return EXIT_FAILURE;

        matrix[i] = tmp;
    }

    (*cols)--;

    return EXIT_SUCCESS;
}

// reallocate matrix to add new column in the end
int add_matrix_col(int **matrix, const size_t rows, size_t *const cols)
{
    int *tmp = NULL;

    for (size_t i = 0; i < rows; i++)
    {
        tmp = realloc(matrix[i], (*cols + 1) * sizeof(int));

        if (tmp == NULL)
            return EXIT_FAILURE;

        matrix[i] = tmp;
    }

    (*cols)++;

    return EXIT_SUCCESS;
}

// reallocate matrix to add new row in the end
int add_matrix_row(int ***matrix, size_t *const rows, const size_t cols)
{
    int **tmp = realloc(*matrix, (*rows + 1) * sizeof(int *));

    if (tmp == NULL)
        return EXIT_FAILURE;

    *matrix = tmp;
    (*matrix)[*rows] = malloc(cols * sizeof(int));

    if ((*matrix)[*rows] == NULL)
        return EXIT_FAILURE;

    (*rows)++;

    return EXIT_SUCCESS;
}

// add new_row in the end of matrix
int add_row_to_matrix(int ***matrix, int *new_row, size_t *const rows, const size_t cols)
{
    if (add_matrix_row(matrix, rows, cols))
        return EXIT_FAILURE;

    for (size_t j = 0; j < cols; j++)
        (*matrix)[*rows - 1][j] = new_row[j];

    return EXIT_SUCCESS;
}

// add new_col in the end of matrix
int add_col_to_matrix(int **matrix, int *new_col, const size_t rows, size_t *const cols)
{
    if (add_matrix_col(matrix, rows, cols))
        return EXIT_FAILURE;

    for (size_t i = 0; i < rows; i++)
        matrix[i][*cols - 1] = new_col[i];

    return EXIT_SUCCESS;
}
