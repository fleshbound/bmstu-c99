#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define ERR_VALUE 1
#define ERR_NEG 3
#define ERR_SIZE 2
#define ERR_NONE 11


// Ввод массива с проверкой на корректность
int input_array(int *a, size_t size)
{
	printf("Enter integers:\n");
	
	for (int i = 0; i < size; i++)
	{
		int element;
		int check = scanf("%d", &element);
		
		if (check != 1)
		{
			printf("Error: Not an integer\n");
			
			return ERR_VALUE;
		}
		
		if (element <= 0)
		{
			printf("Error: Numbers must be positive\n");
		
			return ERR_NEG;
		}
		
		a[i] = element;
	}
	
	return EXIT_SUCCESS;
}


// Проверка на простоту числа
int is_prime(int number)
{
	if (number == 1)
	{
		return 0;
	}

	for (int i = 2; i <= sqrt(number) / 1 + 1; i++)
	{
		if ((number % i == 0) && (i != number))
		{
			return 0;
		}
	}
	
	return 1;
}


// Вывод простых чисел
int output_prime(const int *a, size_t size)
{
	int q = 0;
	
	printf("Primes:\n");

	for (int i = 0; i < size; i++)
	{
		if (is_prime(a[i]))
		{
			printf("%d ", a[i]);
		}
	}
	
	if (q == 0)
	{
		printf("No prime numbers were found\n");
		
		return ERR_NONE;
	}
	
	return EXIT_SUCCESS;
}


// Вывод массива
void output_array(const int *a, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	
	printf("\n");
}


int input_size(size_t *size)
{
	size_t inp_s;

	printf("Enter size of array:\n");
	int check = scanf("%lu", &inp_s);

	if (check != 1)
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
	
	if (check_input == ERR_NEG)
	{
		return ERR_NEG;
	}
    
	int check_output = output_prime(array, size);

	if (check_output == ERR_NONE)
	{
		return ERR_NONE;
	}
	
	return EXIT_SUCCESS;
}

