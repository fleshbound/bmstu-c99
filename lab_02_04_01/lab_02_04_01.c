#include <stdio.h>
#include <stdlib.h>

#define N 10
#define ERR_EMPTY 1
#define ERR_FULL 100
#define CORRECT_INPUT_NUM 1

// Сортировка массива вставками (по возрастанию)
void sort_insert(int *a, const size_t size)
{
    if (size > 1)
    {
        for (int i = 1; i < size; i++)
        {
            int curr_element = a[i];
            int j = i - 1;
            
            while ((j >= 0) && (a[j] > curr_element))
            {
                a[j + 1] = a[j];
                j -= 1;
            }

            a[j + 1] = curr_element;
        }
    }
}


// Ввод массива с проверкой на корректность
int input_array(int *a, size_t *size)
{
    printf("Enter integers:\n");

    int check = 1;
    int code = EXIT_SUCCESS;
    int i = -1;

    while (code == EXIT_SUCCESS)
    {
        int element;
        check = scanf("%d", &element);
        
        if ((check != CORRECT_INPUT_NUM) && (i < 0))
            code = ERR_EMPTY;
        
        i += 1;
        if ((i == N) && (check == CORRECT_INPUT_NUM))
                code = ERR_FULL;
        else
            a[i] = element;
    }

    *size = i;

    if (code == ERR_FULL)
        return ERR_FULL;

    if (code == ERR_EMPTY)
    {
        printf("Error: Array must contain one element at least.\n");
        return ERR_EMPTY;
    }

    return EXIT_SUCCESS;
}


// Вывод массива
void output_array(const int *a, const size_t size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main(void)
{
    int array[N];
    size_t size;
    int error_input = input_array(array, &size);
    if ((error_input != EXIT_SUCCESS) && (error_input != ERR_FULL))
        return error_input;

    sort_insert(array, size);
    output_array(array, size);

    if (error_input == ERR_FULL)
        return ERR_FULL;

    return EXIT_SUCCESS;
}
