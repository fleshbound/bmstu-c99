#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define N 10
#define N_MAX 20
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_NONE 101


// Вставка чисел Фибоначчи в массив
int insert_fibo(int *a, const size_t size)
{
	int temp[N_MAX];
	int q_fibo = 0;
	int last_fibo = 1, curr_fibo = 0;
	int temp_fibo;

	for (int i = 0; i < size; i++)
	{
		temp[i + q_fibo] = a[i];

		if (a[i] % 3 == 0)
		{
			temp[i + q_fibo + 1] = curr_fibo;

			q_fibo += 1;

			temp_fibo = curr_fibo;
			curr_fibo = last_fibo + temp_fibo;
			last_fibo = temp_fibo;
		}
	}

	int curr_size = size + q_fibo;

	for (int i = 0; i < curr_size; i++)
	{
		a[i] = temp[i];
	}

	return curr_size;
}

// Ввод массива с проверкой на корректность
int input_array(int *a, const size_t size)
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
		
		a[i] = element;
	}
	
	return EXIT_SUCCESS;
}


// Ввод размера массива
int input_size(size_t *size)
{
	size_t n;

	printf("Enter the size of array: ");
	int check = scanf("%lu", &n);
	
	if (1 != check) 
	{
		printf("Size must be integer\n");
	
		return ERR_VALUE;
	}
	
	if ((10 < n) || (0 >= n))
	{
		printf("Size must be positive and less or equal to ten\n");
		
		return ERR_SIZE;
	}
	
	*size = n;

	return EXIT_SUCCESS;
}


// Вывод массива
void output_array(const int *a, const size_t size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");
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
	
	int array[N_MAX];
	int check_array = input_array(array, size);
	
	if (check_array == ERR_VALUE)
	{
		return ERR_VALUE;
	}
	
	int new_size = insert_fibo(array, size);

	output_array(array, new_size);

	return EXIT_SUCCESS;
}
