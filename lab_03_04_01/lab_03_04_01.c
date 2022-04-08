#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define M 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_SORT 3


// Ввод размера массива
int input_size(size_t *const size, const size_t max_size)
{
    if (scanf("%lu", size) != 1)
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


// Ввод элементов матрицы с проверкой на корректность
int input_elements(int m[N][M], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (scanf("%d", &m[i][j]) != 1)
            {
                printf("Error: Elements must be integer\n");
                return ERR_VALUE;
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

    printf("Enter elements:\n");
    int error_matrix = input_elements(m, *rows, *cols);
    if (error_matrix != EXIT_SUCCESS)
        return error_matrix;

    return EXIT_SUCCESS;
}


// Вывод массива
void output_array(int *const a, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d%s", a[i], (i == size - 1) ? "\n" : " ");
}


// Вывод матрицы
void output_matrix(int m[N][M], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        output_array(m[i], cols);
}


// Обмен элементов
void swap_gap_arrays(int *const a1, int *const a2, const size_t begin, const size_t end)
{
    for (size_t i = begin; i < end; i++)
    {
        int buf = a2[i];
        a2[i] = a1[i];
        a1[i] = buf;
    }
}


// Обмен элементов над диагоналями и под диагоналями
void swap_elements(int m[N][M], const size_t rows, const size_t cols)
{
    size_t middle = rows / 2;
    for (size_t i = 0; i < middle; i++)
    {
        size_t curr_begin = i, curr_end = cols - i;
        swap_gap_arrays(m[i], m[rows - i - 1], curr_begin, curr_end); 
    }
}


int main(void)
{
    int matrix[N][M];
    size_t rows = 0, cols = 0;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    swap_elements(matrix, rows, cols);

    printf("\nResult matrix:\n");
    output_matrix(matrix, rows, cols);

    return EXIT_SUCCESS;
}
