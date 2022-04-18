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

    for (size_t i = 0; (i < rows) && (exit_code == EXIT_SUCCESS); i++)
        for (size_t j = 0; (j < cols) && (exit_code == EXIT_SUCCESS); j++)
            if (scanf("%d", &m[i][j]) != CORRECT_INP_NUM)
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

// Поиск максимального элемента в массиве
int get_maximum(const int *array, const size_t size)
{
    int max = array[0];

    for (size_t i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];
    
    return max;
}

// Копирование второго массива в первый
void copy_rows_second_to_first(const size_t size, int *const first, const int *second)
{
    for (size_t j = 0; j < size; j++)
        first[j] = second[j];
}

// "Безопасная" вставка строки index_from на index_to (с сохранением относительного положения)
void insert_safely(int m[N_ROWS_MAX][M_COLS_MAX], const size_t cols, const size_t index_from, const size_t index_to)
{
    int buf[M_COLS_MAX];
    copy_rows_second_to_first(cols, buf, m[index_from]);

    for (size_t k = index_from; k > index_to; k--)
        copy_rows_second_to_first(cols, m[k], m[k - 1]);

    copy_rows_second_to_first(cols, m[index_to], buf);
}

// Сортировка строк по убыванию максимумов
void sort_matrix_by_max(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols)
{
    int sorted = 1;

    for (size_t i = 0; i < rows - 1; i++)
    {
        size_t ind_max = i;
        for (size_t j = i + 1; j < rows; j++)
            if (get_maximum(m[j], cols) > get_maximum(m[ind_max], cols))
            {
                sorted = 0;
                ind_max = j;
            }

        if (sorted == 0)
            insert_safely(m, cols, ind_max, i);
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
        sort_matrix_by_max(matrix, rows, cols);
        printf("\nResult matrix:\n");
        print_matrix(matrix, rows, cols);
    }

    return exit_code;
}
