#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define M 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_NONE 3


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

    printf("Enter elements:\n");
    int error_matrix = input_elements(m, *rows, *cols);
    if (error_matrix != EXIT_SUCCESS)
        return error_matrix;

    return EXIT_SUCCESS;
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
int fill_array(int m[N][M], const size_t rows, const size_t cols, int *const array, size_t *size)
{
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
        return ERR_NONE;
    }
    
    *size = new_size;
    return EXIT_SUCCESS;
}


// Сдвиг массива на q позиций
void shift_array(int *const array, const size_t size, const size_t q)
{
    for (size_t i = 0; i < q; i++)
    {
        int buf = array[size - 1];
        for (size_t j = size - 1; j > 0; j--)
            array[j] = array[j - 1];
        array[0] = buf;
    }
}


// Вставка массива в матрицу
void insert_array_in_matrix(int m[N][M], const size_t rows, const size_t cols, const int *array)
{
    size_t insert_index = 0;
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (get_digit_sum(m[i][j]) > 10)
                m[i][j] = array[insert_index++];
}

int main(void)
{
    int matrix[N][M];
    size_t rows = 0, cols = 0;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;
    
    int array[N * M];
    size_t size = 0;
    int error_fill = fill_array(matrix, rows, cols, array, &size);
    if (error_fill != EXIT_SUCCESS)
        return error_fill;
    
    int q = 3;
    shift_array(array, size, q);
    insert_array_in_matrix(matrix, rows, cols, array);

    printf("\nResult matrix:\n");
    output_matrix(matrix, rows, cols);

    return EXIT_SUCCESS;
}
