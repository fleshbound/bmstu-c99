#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_ROWS_MAX 10
#define M_COLS_MAX 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define CORRECT_INP_NUM 1

// Ввод размера массива
int input_size(size_t *const size, const size_t max_size)
{
    int exit_code = EXIT_SUCCESS;

    if (scanf("%lu", size) != CORRECT_INP_NUM)
    {
        printf("Error: Size must be integer\n");
        exit_code = ERR_VALUE;
    }
    
    if (((*size > max_size) || (*size == 0)) && (exit_code == EXIT_SUCCESS))
    {
        printf("Error: Size must be greater than zero and less than or equal to ten\n");
        exit_code = ERR_SIZE;
    }

    return exit_code;
}

// Ввод элементов матрицы с проверкой на корректность
int input_elements(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols)
{
    int exit_code = EXIT_SUCCESS;
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if ((scanf("%d", &m[i][j]) != CORRECT_INP_NUM) && (exit_code == EXIT_SUCCESS))
            {
                printf("Error: Elements must be integer\n");
                exit_code = ERR_VALUE;
            }

    return exit_code;
}

// Ввод размеров и элементов матрицы
int input_matrix(int m[N_ROWS_MAX][M_COLS_MAX], size_t *const rows, size_t *const cols)
{
    printf("Enter number of rows:\n");
    int exit_code = input_size(rows, N_ROWS_MAX);
    if (exit_code == EXIT_SUCCESS)
    {
        printf("Enter number of columns:\n");
        exit_code = input_size(cols, M_COLS_MAX);
        
        if ((*cols != *rows) && (exit_code == EXIT_SUCCESS))
            exit_code = ERR_SIZE;
        
        if (exit_code == EXIT_SUCCESS)
            exit_code = input_elements(m, *rows, *cols);
    }

    return exit_code;
}

// Вывод массива
void print_array(int *const a, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d%s", a[i], (i == size - 1) ? "\n" : " ");
}

// Вывод матрицы
void print_matrix(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        print_array(m[i], cols);
}

// Обмен элементов
void swap_gap_arrays(int *const arr1, int *const arr2, const size_t begin, const size_t end)
{
    for (size_t i = begin; i < end; i++)
    {
        int buf = arr2[i];
        arr2[i] = arr1[i];
        arr1[i] = buf;
    }
}

// Обмен элементов над диагоналями и под диагоналями
void swap_elements(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols)
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
    int exit_code = EXIT_SUCCESS;
    
    int matrix[N_ROWS_MAX][M_COLS_MAX];
    size_t rows = 0, cols = 0;
    
    exit_code = input_matrix(matrix, &rows, &cols);
    if (exit_code == EXIT_SUCCESS)
    {
        swap_elements(matrix, rows, cols);
        printf("\nResult matrix:\n");
        print_matrix(matrix, rows, cols);
    }
    
    return exit_code;
}
