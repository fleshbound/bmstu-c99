#include <stdio.h>
#define ERR_NEG 1
#define ERR_VALUE 2

void int_division(int num1, int num2, int *div, int *mod)
{
	int i = 0;	

	while ( (num1 - num2) >= 0 )
	{
		i = i + 1;
		num1 = num1 - num2;
	}

	*div = i;
	*mod = num1;
}	

int main(void)
{
	int a, d, q, r, check_n;
	
	printf("Enter a and d (integers):\n");
	check_n = scanf("%d %d", &a, &d);

	if (check_n == 2)
	{
		if ( (a <= 0) || (d <= 0) )
		{
			printf("ERROR [%d]: Numbers must be positive\n", ERR_NEG);
			return ERR_NEG;
		}
	}					
	else
	{
		printf("ERROR [%d]: Invalid value\n", ERR_VALUE);
		return ERR_VALUE;	
	}
	
	int_division(a, d, &q, &r);
	printf("Integer division: %d ; modulus: %d \n", q, r);

	return 0;
}
