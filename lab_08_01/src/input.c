#include "input.h"

int finput_nonneg(FILE *const f, size_t *const numb)
{
    if (fscanf(f, "%zu", numb) != READ_COUNT)
        return EXIT_FAILURE;

    if (*numb >= MAX_SIZE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int finput_size(FILE *const f, size_t *const size)
{
    if (finput_nonneg(f, size))
        return EXIT_FAILURE;

    if (*size == 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int finput_power(FILE *const f, int *const power)
{
    if (fscanf(f, "%d", power) != READ_COUNT)
        return EXIT_FAILURE;

    if (*power < 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int finput_matrix(FILE *const f, my_matrix_t matrix)
{
    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            if (fscanf(f, "%d", &matrix.data[i][j]) != READ_COUNT)
                return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int input_power(int *const power)
{
    return finput_power(stdin, power);
}

int input_size(size_t *const size)
{
    return finput_size(stdin, size);
}

int input_nonneg(size_t *const numb)
{
    return finput_nonneg(stdin, numb);
}

int input_matrix(my_matrix_t matrix)
{
    return finput_matrix(stdin, matrix);
}

void foutput_matrix(FILE *const f, my_matrix_t matrix)
{
    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            fprintf(f, "%d%s", matrix.data[i][j], (j == matrix.cols - 1) ? "\n" : " ");
}

void output_matrix(my_matrix_t matrix)
{
    foutput_matrix(stdout, matrix);
}
