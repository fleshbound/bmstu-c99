#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_INDEX 3
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


// Ввод элементов матрицы с проверкой на корректность
int input_elements(int m[N][M], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (scanf("%d", &m[i][j]) != CORRECT_INP_NUM)
            {
                printf("Error: Elements must be integer\n");
                return ERR_VALUE;
            }
        }
    }

    return EXIT_SUCCESS;
}


// Проверка массива на симметричность
int is_symmetric(const int *a, const size_t size)
{
    size_t middle = size / 2;

    for (size_t i = 0; i < middle; i++)
        if (a[i] != a[size - i - 1])
            return 0;

    return 1;
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

    int error_matrix = input_elements(m, *rows, *cols);
    if (error_matrix != EXIT_SUCCESS)
        return error_matrix;
    
    return EXIT_SUCCESS;
}


int main(void)
{
    int matrix[N][M];
    size_t rows, cols;
    int error_input = input_matrix(matrix, &rows, &cols);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    int array[M];
    fill_array(matrix, array, rows, cols);

    printf("\nResult array: ");
    print_array(array, rows);
    
    return EXIT_SUCCESS;
}
