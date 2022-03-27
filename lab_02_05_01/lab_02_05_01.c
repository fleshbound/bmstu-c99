#include <stdio.h>
#include <stdlib.h>
#define N 10
#define ERR_VALUE 1
#define ERR_SIZE 2
#define ERR_EMPTY 3


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


// Возвращает минимум из пары целых чисел
int get_min(const int a, const int b)
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


// Возвращает минимальное количество положительных и отрицательных
// элементов, из которых будет складываться сумма
int get_min_length(int *p_begin, const int *p_end)
{
	int *pa = p_begin;
	int q_neg = 0, q_pos = 0;

	while (pa != p_end)
	{
		if (*pa < 0)
		{
			q_neg += 1;
		}

		if (*pa > 0)
		{
			q_pos += 1;
		}

		pa += 1;
	}

	return get_min(q_neg, q_pos);
}


// Получить значение знака числа
int get_sign(const int number)
{
	if (number > 0)
	{
		return 1;
	}

	if (number < 0)
	{
		return -1;
	}

	return 0;
}

// Получение суммы neg[0] * pos[0] + ... (позитивные в обратном порядке)
int get_sum(int *p_begin, const int *p_end)
{
	int k = get_min_length(p_begin, p_end);

	if (k == 0)
	{
		printf("Error: No negative and/or no positive numbers\n");

		return ERR_EMPTY;
	}

	int sum = 0;
	
	int q_neg = 0;
	int last_pos_ind = p_end - p_begin;
	int *pa = p_begin;
	
	while (q_neg < k)
	{
		int curr_elem = *pa; 
		int curr_neg = 0;
		int flag_need_pos = 0;
		
		if (curr_elem < 0)
		{
			curr_neg = curr_elem;
			flag_need_pos = 1;
			q_neg += 1;
		}
		
		int i = last_pos_ind;
		int *pa_pos = p_begin + i;
		int curr_pos = 0;

		while ((pa_pos >= p_begin) && (flag_need_pos))
		{
			pa_pos -= 1;
			i -= 1;

			int elem = *pa_pos;
			if ((elem > 0) && (i < last_pos_ind))
			{
				last_pos_ind = i;
				curr_pos = elem;
				flag_need_pos = 0;
			}
		}

		int curr_multi = curr_neg * curr_pos;
		sum += curr_multi;

		pa += 1;
	}

	return sum;
}

int main(void)
{
	int array[N];
	
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

	int check_input = input_array(array, array + size);

	if (check_input == ERR_VALUE)
	{
		return ERR_VALUE;
	}

	int result = get_sum(array, array + size);

	if (result == ERR_EMPTY)
	{
		return ERR_EMPTY;
	}

	printf("Result: %d\n", result);

	return EXIT_SUCCESS;
}

