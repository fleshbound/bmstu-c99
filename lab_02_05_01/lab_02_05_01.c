#include <stdio.h>
#include <stdlib.h>
#define N 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_NOPOS 3
#define ERR_NONEG 4


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


// Возвращает минимум из пары целых чисел
int get_min(int a, int b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// Возвращает pos[0]*neg[0] + ...
int get_value(int *p_begin, const int *p_end)
{
	int *pa = p_begin;
	int q = 0, p = 0;

	while (pa != p_end)
	{
		if (*pa < 0)
		{
			q += 1;
		}

		if (*pa > 0)
		{
			p += 1;
		}
	
		pa += 1;
	}

	if (p == 0)
	{
		printf("Error: Cannot get the value (no positive numbers)\n");
	
		return ERR_NOPOS;
	}

	if (q == 0)
	{
		printf("Error: Cannot get the value (no negative numbers)\n");

		return ERR_NONEG;
	}

	int k = get_min(p, q);
	int n = 2 * k;
	int curr_multi = 0, curr_sum = 0;
	int curr_pos = 0, curr_neg = 0;
	pa = p_begin;

	while (pa != p_end)
	{
		if (n == 0)
		{
			return curr_sum;
		}

		if (*pa > 0)
		{
			curr_pos = *pa;
			n -= 1;
		}

		if (*pa < 0)
		{
			curr_neg = *pa;
			n -= 1;
		}

		if ((curr_neg != 0) && (curr_pos != 0))
		{
			curr_multi = curr_neg * curr_pos;
			curr_sum += curr_multi;
			curr_neg = 0;
			curr_pos = 0;
		}

		pa += 1;
	}
	
	return curr_sum;
}


// Ввод массива
int input_array(int *p_begin, const int *p_end)
{
	int *pa = p_begin;

	printf("Enter integers:\n");

	while (pa != p_end)
	{
		int element;
		int check = scanf("%d", &element);

		if (check != 1)
		{
			printf("Error: Elements must be integer\n");

			return ERR_VALUE;
		}

		*pa = element;
		pa += 1;
	}

	return EXIT_SUCCESS;
}


// Вывод массива
void output_array(int *p_begin, const int *p_end)
{
	int *pa = p_begin;

	while (pa != p_end)
	{
		printf("%d ", *pa);
		pa += 1;
	}

	printf("\n");
}


int main(void)
{
	int array[N];
	size_t size;

	int check_size = input_size(&size);
	
	if (check_size == ERR_SIZE)
	{
		return ERR_SIZE;
	}

	int check_input = input_array(array, array + size);
	
	if (check_input == ERR_VALUE)
	{
		return ERR_VALUE;
	}

	// output_array(array, array + size);
	
	int res = get_value(array, array + size);
	
	if (res == ERR_NONEG)
	{
		return ERR_NONEG;
	}

	if (res == ERR_NOPOS)
	{
		return ERR_NOPOS;
	}

	printf("Result: %d\n", res);

	return EXIT_SUCCESS;
}

