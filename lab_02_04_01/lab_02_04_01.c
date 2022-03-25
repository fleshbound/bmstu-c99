#include <stdio.h>
#include <stdlib.h>
#define N 10
#define ERR_EMPTY 1
#define ERR_FULL 100

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

	while (check == 1)
	{
		int element;
		check = scanf("%d", &element);

		if (check == 1)
		{
			i += 1;

			a[i] = element;
			if (i == N - 1)
			{
				check = 0;
				code = ERR_FULL;
			}
		}
	}

	*size = i + 1;

	if (code == ERR_FULL)
	{
		return ERR_FULL;
	}

	if ((check != 1) && (*size == 0))
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
	{
		printf("%d ", a[i]);
	}

	printf("\n");
}

int main(void)
{
	int array[N];
	size_t size;
	int check_input = input_array(array, &size);

	if (check_input == ERR_EMPTY)
	{
		return ERR_EMPTY;
	}

	sort_insert(array, size);

	output_array(array, size);

	if (check_input == ERR_FULL)
	{
		return ERR_FULL;
	}

	return EXIT_SUCCESS;
}

