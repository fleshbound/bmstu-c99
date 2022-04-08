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

// Сортировка строк по убыванию максимумов
int sort_matrix_by_max(int m[N][M], const size_t rows, const size_t cols)
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
        {
            // printf("%lu (before swap):\n", i);
            // output_matrix(m, rows, cols);

            int buf[M];
            copy_rows_second_to_first(cols, buf, m[ind_max]);
            for (size_t k = ind_max; k > i; k--)
                copy_rows_second_to_first(cols, m[k], m[k - 1]);
            copy_rows_second_to_first(cols, m[i], buf);
            
            // printf("%lu (after swap):\n", i);
            // output_matrix(m, rows, cols);
        }
    }

    if (sorted)
    {
        printf("Error: Matrix is already sorted\n");
        return ERR_SORT;
    }

    return EXIT_SUCCESS;
}


int main(void)
{
    int matrix[N][M];
    size_t rows = 0, cols = 0;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;
    
    int error_sort = sort_matrix_by_max(matrix, rows, cols);
    if (error_sort != EXIT_SUCCESS)
        return error_sort;

    printf("\nResult matrix:\n");
    output_matrix(matrix, rows, cols);

    return EXIT_SUCCESS;
}
