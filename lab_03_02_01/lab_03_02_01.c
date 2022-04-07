#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define M 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_INDEX 3


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


// Получение номеров строки и столбца, в которых элемент с мин. суммой цифр
void get_min_elem_index(int m[N][M], const size_t rows, const size_t cols, size_t *const ind_row, size_t *const ind_col)
{
    int min_sum = 0, t_i = 0, t_j = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if ((get_digit_sum(m[i][j]) < min_sum) || ((i == 0) && (j == 0)))
            {
                t_i = i;
                t_j = j;
                min_sum = get_digit_sum(m[i][j]);
            }

    *ind_row = t_i;
    *ind_col = t_j;
}


// Удаление строки index из матрицы
void delete_row(int m[N][M], size_t *const rows, const size_t cols, const size_t index)
{
    for (size_t j = 0; j < cols; j++)
        for (size_t i = index; i < *rows - 1; i++)
            m[i][j] = m[i + 1][j];
    *rows = *rows - 1;
}


// Удаление столбца index из матрицы
void delete_column(int m[N][M], const size_t rows, size_t *const cols, const size_t index)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = index; j < *cols - 1; j++)
            m[i][j] = m[i][j + 1];
    *cols = *cols - 1;
}


// Удаление строки и столбца, на пересек. кот. есть элемент с мин. суммой цифр
void delete_min_sum_elem(int m[N][M], size_t *const rows, size_t *const cols)
{
    size_t del_row_index = 0, del_col_index = 0;
    get_min_elem_index(m, *rows, *cols, &del_row_index, &del_col_index);

    delete_row(m, rows, *cols, del_row_index);
    delete_column(m, *rows, cols, del_col_index);
}


int main(void)
{
    int matrix[N][M];
    size_t rows = 0, cols = 0;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;
    
    delete_min_sum_elem(matrix, &rows, &cols);

    if ((rows == 0) || (cols == 0))
    {
        printf("Error: Empty result matrix\n");
        return ERR_SIZE;
    }

    printf("\nResult matrix:\n");
    output_matrix(matrix, rows, cols);

    return EXIT_SUCCESS;
}
