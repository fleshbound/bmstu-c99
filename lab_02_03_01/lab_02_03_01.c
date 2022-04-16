#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 10
#define N_MAX 20
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_NONE 101
#define NUMBER_OF_INPUT_INT 1

// Вставка элемента в массив на позицию pos
void insert_element(int *const a, const size_t size, const size_t pos, const int element)
{
    for (int i = size - 1; i > pos; i--) 
        a[i] = a[i - 1];
    a[pos] = element;
}

// Вставка чисел Фибоначчи в массив
int insert_fibo(int *const a, const size_t size)
{
    int last_fibo = 1, curr_fibo = 0, temp_fibo;
    
    size_t curr_size = size;
    size_t i = 0;
    while (i < curr_size)
    {
        if (a[i] % 3 == 0)
        {
            curr_size++;
            insert_element(a, curr_size, i + 1, curr_fibo);
            i++;

            temp_fibo = curr_fibo;
            curr_fibo = last_fibo + temp_fibo;
            last_fibo = temp_fibo;
        }
        i++;
    }

    return curr_size;
}

// Ввод массива с проверкой на корректность
int input_array(int *const a, const size_t size)
{
    printf("Enter integers:\n");
    
    for (int i = 0; i < size; i++)
    {
        int element;
        int check = scanf("%d", &element);
        
        if (check != NUMBER_OF_INPUT_INT)
        {
            printf("Error: Not an integer\n");
            
            return ERR_VALUE;
        }
        
        a[i] = element;
    }
    
    return EXIT_SUCCESS;
}

// Ввод размера массива
int get_size(size_t *const size)
{
    size_t n;

    printf("Enter the size of array: ");
    int check = scanf("%lu", &n);
    
    if (check != NUMBER_OF_INPUT_INT) 
    {
        printf("Size must be integer\n");
        return ERR_VALUE;
    }
    
    if ((n > 10) || (n <= 0))
    {
        printf("Size must be positive and less or equal to ten\n");
        return ERR_SIZE;
    }
    
    *size = n;
    return EXIT_SUCCESS;
}

// Вывод массива
void print_array(const int *a, const size_t size)
{
    for (int i = 0; i < size; i++) 
        printf("%d%s", a[i], (i == size - 1) ? "\n" : " ");
}

int main(void)
{
    size_t size;
    int error_size = get_size(&size);
    
    if (error_size != EXIT_SUCCESS)
        return error_size;
    
    int array[N_MAX];
    int error_array = input_array(array, size);
    
    if (error_array != EXIT_SUCCESS) 
        return error_array;
    
    int new_size = insert_fibo(array, size);
    print_array(array, new_size);

    return EXIT_SUCCESS;
}
