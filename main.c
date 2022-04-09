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

    if (size > max_size || size == 0)
        return ERR_SIZE;

    return EXIT_SUCCESS;
}


int input_array(int *const a, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        if (scanf("%d", a[i]) != CORRECT_INPUT_NUM)
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
    error_size = get_size(cols, M)
    if (error_size != EXIT_SUCCESS)
        return error_size;

    printf("Elements:\n");
    for (size_t i = 0; i < rows; i++)
    {
        int error_array = input_array(m[i], cols);
        if (error_array != EXIT_SUCCESS)
            return error_array;
    }
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
        else if (code < 0)
        {
            int buf = a[size - 1];
            for (size_t j = size - 1; j > 0; j++)
                a[j] = a[j - 1];
            a[0] = a[size - 1];
        }
}


void transp_matrix(int m[N][M], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        
    }
}


void shift_side(const size_t num_shift, int m[N][M], const size_t rows, const size_t cols, const size_t shift)
{
    for (size_t i = 0; i < rows; i++)
        shift_array_side(m[i], cols, num_shift, code);
}


void shift_down(const size_t num_shift, int m[N][M], const size_t rows, const size_t cols, const size_t shift)
{
    transp_matrix(m);
    for (size_t i = 0; i < rows; i++)
        shift_array_side(m[i], cols, num_shift, code);
    transp_matrix(m);
}

void shift_matrix(int m[N][M], const size_t rows, const size_t cols, const int *act)
{
    shift_side(act[0], m, rows, cols, -1);
    shift_side(act[1], m, rows, cols, 1);
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
    int error_input = input_array(actions, K);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    shift_matrix(matrix, rows, cols, actions);
    
    printf("\nResult:\n");
    print_matrix(matrix, rows, cols);
    
    return EXIT_SUCCESS;
}
