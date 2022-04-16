#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_ROWS_MAX 10
#define M_COLS_MAX 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_SORT 3
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
    
    if ((exit_code == EXIT_SUCCESS) && ((*size > max_size) || (*size == 0)))
    {
        printf("Error: Size must be greater than zero and less than or equal to ten\n");
        exit_code = ERR_SIZE;
    }

    return exit_code;
}

// Заполнение матрицы по спирали (по часовой) от 1 до N_ROWS_MAX*N_ROWS_MAX
void fill_elements_spiral(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols)
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
            fill_elements_spiral(m, *rows, *cols);
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

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    
    int matrix[N_ROWS_MAX][M_COLS_MAX];
    size_t rows = 0, cols = 0;
    exit_code = input_matrix(matrix, &rows, &cols);
    if (exit_code == EXIT_SUCCESS)
    {
        printf("\nResult matrix:\n");
        print_matrix(matrix, rows, cols);
    }
    
    return exit_code;
}
