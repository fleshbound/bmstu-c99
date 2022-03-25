#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_MULTI 4

// ^ ERR_MULTI can be an any other not-odd number

// Inputs array
// Returns code > 0 if input is invalid
int input_array(int *arr, size_t size)
{
	printf("Enter integers:\n");

	for (int i = 0; i < size; i++)
	{
		int element;
		int check = scanf("%d", &element);

		if (check != 1)
		{
			printf("Error: Numbers must be integer.\n");
			
			return ERR_VALUE;
		}

		arr[i] = element;
	}

	return EXIT_SUCCESS;
}


// Returns multiply of odd elements
int get_multi(const int *a, int size)
{
	int multi = 1;
	int no_odd = 1;

	for (int i = 0; i < size; i++)
	{
		if (abs(a[i]) % 2 == 1)
		{
			multi *= a[i];
			no_odd = 0;
		}
	}
	
	if (no_odd)
	{
		printf("Error: No odd numbers were found\n");

		return ERR_MULTI;
	}
	
	return multi;
}


// Inputs array's size
// Returns code > 0 if input is invalid
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

	if ((10 < inp_s) || (0 >= inp_s))
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

	int check_input = input_array(a, size);

	if (check_input == ERR_VALUE)
	{
		return ERR_VALUE;
	}

	int multi = get_multi(a, size);

	if (multi == ERR_MULTI)
	{
		return ERR_MULTI;
	}

	printf("%d\n", multi);

	return EXIT_SUCCESS;
}

