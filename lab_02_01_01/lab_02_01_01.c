#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_MULTI 3
#define CORRECT_INPUT_NUM 1


// Ввод массива
int input_array(int *arr, size_t size)
{
    printf("Enter integers:\n");

    for (int i = 0; i < size; i++)
    {
        int element;
        int check = scanf("%d", &element);

        if (check != CORRECT_INPUT_NUM)
        {
            printf("Error: Numbers must be integer.\n");
            return ERR_VALUE;
        }

        arr[i] = element;
    }

    return EXIT_SUCCESS;
}


int get_odd_multi(const int *a, const size_t size, int *const multi)
{
    int curr_multi = 1;
    int no_odd = 1;

    for (size_t i = 0; i < size; i++)
        if (abs(a[i]) % 2 == 1)
        {
            curr_multi *= a[i];
            no_odd = 0;
        }
    
    if (no_odd)
    {
        printf("Error: No odd numbers were found\n");
        return ERR_MULTI;
    }

    *multi = curr_multi;    
    return EXIT_SUCCESS;
}


// Ввод размера массива
int input_size(size_t *size)
{
    size_t inp_s;
    
    printf("Enter size of array:\n");
    int check = scanf("%lu", &inp_s);

    if (check != CORRECT_INPUT_NUM)
    {
        printf("Error: Size must be an integer\n");
        return ERR_VALUE;
    }

    if ((inp_s > 10) || (inp_s == 0))
    {
        printf("Error: Size must be more than zero and less or equal to ten\n");
        return ERR_SIZE;
    }

    *size = inp_s;
    return EXIT_SUCCESS;
}


int main(void)
{
    int a[N];
    
    size_t size = 0;
    int error_size = input_size(&size);
    if (error_size == ERR_VALUE)
        return error_size;

    int error_input = input_array(a, size);
    if (error_input != EXIT_SUCCESS)
        return error_input;

    int multi = 0;
    int error_multi = get_odd_multi(a, size, &multi);
    if (error_multi != EXIT_SUCCESS)
        return error_multi;

    printf("%d\n", multi);
    return EXIT_SUCCESS;
}
