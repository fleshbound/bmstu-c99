#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define M 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_SORT 3
#define CORRECT_INP_NUM 1

// Ввод размера массива
int input_size(size_t *const size, const size_t max_size)
{
    if (scanf("%lu", size) != CORRECT_INP_NUM)
    {
        printf("Error: Size must be integer\n");
        return ERR_VALUE;
    }

    if ((*size > max_size) || (*size == 0))
    {
        printf("Error: Size must be greater than zero and less than or equal to ten\n");
        return ERR_SIZE;
    }

    return EXIT_SUCCESS;
}


// Ввод элементов матрицы в виде спирали по часовой с проверкой на корректность
int fill_elements_spiral(int m[N][M], const size_t rows, const size_t cols)
{
    size_t i = 0, j = 0, n = 1;
    size_t i_begin = 0, i_end = 0, j_begin = 0, j_end = 0;

    while (n <= rows * cols)
    { 
        m[i][j] = n;

        if ((j < cols - j_end - 1) && (i == i_begin))
            j++;
        else if ((j == cols - j_end - 1) && (i < rows - i_end - 1))
            i++;
        else if ((j > j_begin) && (i == rows - i_begin - 1))
            j--;
        else
            i--;

        if ((i == i_begin + 1) && (j == j_begin) && (j_begin != cols - j_end - 1))
        {
            i_begin++;
            i_end++;
            j_begin++;
            j_end++;
        }

        n++;
    }
    return EXIT_SUCCESS;
}


// Ввод размеров и элементов матрицы
int input_matrix(int m[N][M], size_t *const rows, size_t *const cols)
{
    printf("Enter number of rows:\n");
    int error_size = input_size(rows, N);
    if (error_size != EXIT_SUCCESS)
        return error_size;

    printf("Enter number of columns:\n");
    error_size = input_size(cols, M);
    if (error_size != EXIT_SUCCESS)
        return error_size;

    if (*cols != *rows)
    {
        printf("Error: Matrix must be square\n");
        return ERR_SIZE;
    }

    fill_elements_spiral(m, *rows, *cols);

    return EXIT_SUCCESS;
}


// Вывод массива
void print_array(int *const a, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d%s", a[i], (i == size - 1) ? "\n" : " ");
}


// Вывод матрицы
void print_matrix(int m[N][M], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        print_array(m[i], cols);
}


int main(void)
{
    int matrix[N][M];
    size_t rows = 0, cols = 0;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    printf("\nResult matrix:\n");
    print_matrix(matrix, rows, cols);

    return EXIT_SUCCESS;
}
