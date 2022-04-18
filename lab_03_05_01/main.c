#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_ROWS_MAX 10
#define M_COLS_MAX 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_NONE 3
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

// Сумма цифр числа
int get_digit_sum(const int number)
{
    int sum = 0, n = abs(number);

    while (n > 0)
    {
        sum = sum + n % 10;
        n = n / 10;
    }

    return sum;
}

// Заполнение массива числами, сумма цифр которых > 10
int fill_array(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols, int *const array, size_t *size)
{
    int exit_code = EXIT_SUCCESS;
    
    size_t new_size = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (get_digit_sum(m[i][j]) > 10)
            {
                array[new_size] = m[i][j];
                new_size++;
            }
            
    if (new_size == 0)
    {
        printf("Error: No numbers with digit sum more than ten\n");
        exit_code = ERR_NONE;
    }
    else
        *size = new_size;
    
    return exit_code;
}

// Сдвиг массива на shift_q позиций ВЛЕВО
void shift_array(int *const array, const size_t size, const size_t shift_q)
{
    for (size_t i = 0; i < shift_q; i++)
    {
        int buf = array[0];

        for (size_t j = 0; j < size - 1; j++)
            array[j] = array[j + 1];
        
        array[size - 1] = buf;
    }
}

// Вставка массива в матрицу
void insert_array_in_matrix(int m[N_ROWS_MAX][M_COLS_MAX], const size_t rows, const size_t cols, const int *array)
{
    size_t insert_index = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (get_digit_sum(m[i][j]) > 10)
                m[i][j] = array[insert_index++];
}

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    
    int matrix[N_ROWS_MAX][M_COLS_MAX];
    size_t rows = 0, cols = 0;

    exit_code = input_matrix(matrix, &rows, &cols);

    if (exit_code == EXIT_SUCCESS)
    {
        int array[N_ROWS_MAX * M_COLS_MAX];
        size_t size = 0;
        exit_code = fill_array(matrix, rows, cols, array, &size);

        if (exit_code == EXIT_SUCCESS)
        {
            int shift_q = 3;
            shift_array(array, size, shift_q);
            insert_array_in_matrix(matrix, rows, cols, array);

            printf("\nResult matrix:\n");
            print_matrix(matrix, rows, cols);
        }
    }
    
    return exit_code;
}
