#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
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
    
    if ((exit_code == EXIT_SUCCESS) && ((*size > max_size) || (*size == 0)))
    {
        printf("Error: Size must be greater than zero and less than or equal to ten\n");
        exit_code = ERR_SIZE;
    }

    return exit_code;
}

// Ввод элементов матрицы с проверкой на корректность
int input_elements(int m[N][M], const size_t rows, const size_t cols)
{
    int exit_code = EXIT_SUCCESS;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if ((exit_code == EXIT_SUCCESS) && (scanf("%d", &m[i][j]) != CORRECT_INP_NUM))
            {
                printf("Error: Elements must be integer\n");
                exit_code = ERR_VALUE;
            }
        }
    }

    return exit_code;
}

// Ввод размеров и элементов матрицы
int input_matrix(int m[N][M], size_t *const rows, size_t *const cols)
{
    printf("Enter number of rows:\n");
    int exit_code = input_size(rows, N);
    if (exit_code == EXIT_SUCCESS)
    {
        printf("Enter number of columns:\n");
        exit_code = input_size(cols, M);
        if (exit_code == EXIT_SUCCESS)
            exit_code = input_elements(m, *rows, *cols);
    }

    return exit_code;
}

// Проверка массива на симметричность
int is_symmetric(const int *a, const size_t size)
{
    size_t middle = size / 2;
    int symm_flag = 1;

    for (size_t i = 0; i < middle; i++)
        if (a[i] != a[size - i - 1])
            symm_flag = 0;

    return symm_flag;
}

// Заполнение массива матрицей с учетом симметрии строки index
void fill_array(int m[N][M], int *const a, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        a[i] = 0;
        if (is_symmetric(m[i], cols))
            a[i] = 1;
    }
}

// Вывод массива
void print_array(int *const a, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
        printf("%d%s", a[i], (i == size - 1) ? "\n" : " ");
}

int main(void)
{
    int exit_code = EXIT_SUCCESS;

    int matrix[N][M];
    size_t rows, cols;

    exit_code = input_matrix(matrix, &rows, &cols);
    if (exit_code == EXIT_SUCCESS)
    {
        int array[M];
        fill_array(matrix, array, rows, cols);
        printf("\nResult array: ");
        print_array(array, rows);
    }

    return exit_code;
}
