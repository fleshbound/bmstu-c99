#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_NONE 11
#define CORRECT_INPUT_NUM 1


// Ввод массива с проверкой на корректность
int input_array(int *a, size_t size)
{
    printf("Enter integers:\n");
    
    for (int i = 0; i < size; i++)
    {
        int element;
        int check = scanf("%d", &element);
        
        if (check != CORRECT_INPUT_NUM)
        {
            printf("Error: Not an integer\n");
            return ERR_VALUE;
        }
        
        a[i] = element;
    }
    
    return EXIT_SUCCESS;
}


// Проверка на простоту числа
int is_prime(int number)
{
    if (number <= 1)
        return 0;

    for (int i = 2; i <= sqrt(number) / 1 + 1; i++)
        if ((number % i == 0) && (number != i))
            return 0;
    
    return 1;
}


// Копирование простых чисел из a в b
int insert_primes(int *b, const int *a, const size_t prime_count, const size_t size)
{
    int q = 0;
    
    if (prime_count == 0)
    {
        printf("No prime numbers were found\n");

        return ERR_NONE;
    }

    for (int i = 0; i < size; i++)
        if (is_prime(a[i]))
        {
            b[q] = a[i];
            q += 1;
        }

    return EXIT_SUCCESS;
}


// Подсчет количества простых чисел
int count_primes(const int *a, const size_t size)
{
    int q = 0;

    for (int i = 0; i < size; i++)
        if (is_prime(a[i]))
            q += 1;

    return q;
}


// Вывод массива
void output_array(const int *a, const size_t n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}


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
    
    if ((inp_s <= 0) || (inp_s > 10))
    {
        printf("Error: Size must be more than zero and less or equal to ten\n");
        return ERR_SIZE;
    }

    *size = inp_s;
    return EXIT_SUCCESS;
}


int main(void)
{
    size_t size;
    int check_size = input_size(&size);

    if (check_size == ERR_VALUE)
    {
        return ERR_VALUE;
    }

    if (check_size == ERR_SIZE)
    {
        return ERR_SIZE;
    }

    int array[N];
    int check_input = input_array(array, size);
    
    if (check_input == ERR_VALUE)
    {
        return ERR_VALUE;
    }
    
    size_t prime_count = count_primes(array, size);
    int primes[N];
    int check_insert = insert_primes(primes, array, prime_count, size);

    if (check_insert == ERR_NONE)
        return ERR_NONE;
    
    output_array(primes, prime_count);

    return EXIT_SUCCESS;
}
