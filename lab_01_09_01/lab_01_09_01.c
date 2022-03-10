#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CODE_OK 0
#define ERR_VALUE 1
#define ERR_NEG 2

// Input check

int check_scanf(double *num)
{
	//printf("Enter x: ");
	int check = scanf("%lf", num);

	if (check != 1)
	{
		return ERR_VALUE;
	}
	
	if (*num < 0)
	{
		return ERR_NEG;
	}
	
	return CODE_OK;
}


double get_sum(int *code)
{
	int i = 1, check = CODE_OK, flag = 0;
	double x, sum = 0;

	while (check == CODE_OK)
	{
		check = check_scanf(&x);
		
		if (check == ERR_VALUE)
		{
			*code = ERR_VALUE;
			printf("Error: Invalid value\n");
			return ERR_VALUE;
		}

		if (check != ERR_NEG)
		{
			flag = 1;
			sum += sqrt(x / i);
			i++;
		}
	}

        if (flag == 0)
        {
		*code = ERR_VALUE;
		printf("Error: No value was entered\n");
		return ERR_VALUE;
        }

	return sum;
}


int main(void)
{
	int code = 0;

	printf("Enter float positive values; negative value will end the entering\nand show the result of calculating:\n");

	double sum = get_sum(&code);
	
	if (code == ERR_VALUE)
	{
		return ERR_VALUE;
	}

	double g_x = sin(sum);
	printf("g(x): %lf \n", g_x);

	return CODE_OK;
}

