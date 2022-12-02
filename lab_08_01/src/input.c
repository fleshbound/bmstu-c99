#include "input.h"

int finput_nonneg(FILE *const f, size_t *const numb)
{
    /* printf("input's here!\n"); */

    if (fscanf(f, "%zu", numb) != READ_COUNT)
    {
        /* printf("uh-oh...\n"); */
        return EXIT_FAILURE;
    }

    if (*numb > MAX_SIZE)
        return EXIT_FAILURE;
    /* printf("got it!\n"); */

    return EXIT_SUCCESS;
}

int finput_size(FILE *const f, size_t *const size)
{
    if (finput_nonneg(f, size))
        return EXIT_FAILURE;

    if ((*size == 0) || (*size > MAX_SIZE))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int finput_matrix(FILE *const f, int **matrix, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (fscanf(f, "%d", &matrix[i][j]) != READ_COUNT)
                return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int input_size(size_t *const size)
{
    return finput_size(stdin, size);
}

int input_nonneg(size_t *const numb)
{
    return finput_nonneg(stdin, numb);
}

int input_matrix(int **matrix, const size_t rows, const size_t cols)
{
    return finput_matrix(stdin, matrix, rows, cols);
}

void foutput_matrix(FILE *const f, int **matrix, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            fprintf(f, "%d%s", matrix[i][j], (j == cols - 1) ? "\n" : " ");
}

void output_matrix(int **matrix, const size_t rows, const size_t cols)
{
    foutput_matrix(stdout, matrix, rows, cols);
}
