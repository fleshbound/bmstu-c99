#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
#define K 4
#define CORRECT_INPUT_NUM 1
#define ERR_VALUE 1
#define ERR_SIZE 2


int get_size(size_t *const size, size_t const max_size)
{
    if (scanf("%lu", size) != CORRECT_INPUT_NUM)
        return ERR_VALUE;

    if (*size > max_size || *size == 0)
        return ERR_SIZE;

    return EXIT_SUCCESS;
}


int input_array(int *const a, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        if (scanf("%d", &a[i]) != CORRECT_INPUT_NUM)
            return ERR_VALUE;
    return EXIT_SUCCESS;
}


void print_array(const int *a, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d%s", a[i], (i == size - 1) ? "\n" : " ");
}


void print_matrix(int m[N][M], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        print_array(m[i], cols);
}


int input_matrix(int m[N][M], size_t *const rows, size_t *const cols)
{
    printf("Number of rows:\n");
    int error_size = get_size(rows, N);
    if (error_size != EXIT_SUCCESS)
        return error_size;

    printf("Number of cols:\n");
    error_size = get_size(cols, M);
    if (error_size != EXIT_SUCCESS)
        return error_size;

    if (*rows != *cols)
    {
        printf("Error: Matrix must be square\n");
        return ERR_SIZE;
    }

    printf("Elements:\n");
    for (size_t i = 0; i < *rows; i++)
    {
        int error_array = input_array(m[i], *cols);
        if (error_array != EXIT_SUCCESS)
            return error_array;
    }

    return EXIT_SUCCESS;
}


void shift_array_side(int *const a, const size_t size, const size_t q, const int code)
{
    for (size_t i = 0; i < q; i++)
        if (code < 0)
        {
            int buf = a[0];
            for (size_t j = 0; j < size - 1; j++)
                a[j] = a[j + 1];
            a[size - 1] = buf;
        }
        else if (code > 0)
        {
            int buf = a[size - 1];
            for (size_t j = size - 1; j > 0; j--)
                a[j] = a[j - 1];
            a[0] = buf;
        }
}


void transp_matrix(int m[N][M], size_t *const rows, size_t *const cols)
{
    size_t new_cols = *cols, new_rows = *rows;
    if (new_rows > new_cols)
        new_cols = new_rows;
    else
        new_rows = new_cols;

    int buf;
    for (size_t i = 0; i < new_rows; i++)
    {
        for (size_t j = i; j < new_cols; j++)
        {
            buf = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = buf;
        }
    }

    buf = *rows;
    *rows = *cols;
    *cols = buf;
}


void shift_side(const size_t num_shift, int m[N][M], const size_t rows, const size_t cols, const size_t shift)
{
    for (size_t i = 0; i < rows; i++)
        shift_array_side(m[i], cols, num_shift, shift);
}


void shift_down(const size_t num_shift, int m[N][M], size_t *const rows, size_t *const cols, const size_t shift)
{
    transp_matrix(m, rows, cols);
    for (size_t i = 0; i < *rows; i++)
        shift_array_side(m[i], *cols, num_shift, shift);
    transp_matrix(m, rows, cols);
}

void shift_matrix(int m[N][M], size_t *const rows, size_t *const cols, const int *act)
{
    shift_side(act[0], m, *rows, *cols, -1);
    shift_side(act[1], m, *rows, *cols, 1);
    shift_down(act[2], m, rows, cols, -1);
    shift_down(act[3], m, rows, cols, 1);
}


int main(void)
{
    int matrix[N][M];
    size_t rows = 0, cols = 0;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    int actions[K];
    printf("\nEnter four action codes:\n");
    error_input = input_array(actions, K);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    shift_matrix(matrix, &rows, &cols, actions);
    
    printf("\nResult:\n");
    print_matrix(matrix, rows, cols);
    
    return EXIT_SUCCESS;
}
