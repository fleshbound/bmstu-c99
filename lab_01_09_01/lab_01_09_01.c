#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERR_OK 0
#define ERR_VALUE 1
#define ERR_NEG 2

// Input check

int check_scanf(double *num)
{
	//printf("Enter x: ");
	int check = scanf("%lf", num);

	if (check != 1)
	{
		printf("Error: Invalid value.\n");
		exit(ERR_VALUE);
	}
	else
	{
		if (*num < 0)
		{
			return ERR_NEG;
		}
		else
		{
			return ERR_OK;
		}
	}
}


int main(void)
{
	int check = 0, i = 1, flag = 0;
	double x, sum = 0, g_x = 0;

	printf("Enter float positive values; negative value will end the entering\nand show the result of calculating:\n");
	while (check == ERR_OK)
	{
		check = check_scanf(&x);
		if (x >= 0)
		{
			flag = 1;
			sum += sqrt(x / i);
			i++;
		}
	}

	if (flag == 0)
	{
		printf("Error: No value has been entered.\n");
		return ERR_VALUE;
	}

	g_x = sin(sum);
	printf("g(x): %lf \n", g_x);

	return 0;
}
