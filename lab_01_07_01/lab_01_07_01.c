#include <stdio.h>
#include <math.h>
#define ERR_OK 0
#define ERR_EPS 1
#define ERR_VALUE 2

float get_sum(float x, float epsilon)
{
	float sum = x, curr_x = x;
	int i = 1;

	while ( fabs(curr_x) >= epsilon )
	{
		i += 2;
		curr_x *= pow(-1, i) * (x * x) / (i * (i - 1));
		sum += curr_x;
	}

	return sum;
}

int check_input(float *x, float *eps)
{
	int n_var = scanf("%f %f", x, eps);
	if (n_var == 2)
	{
		if (*eps <= 0.0 || *eps > 1.0)
		{
			return ERR_EPS;
		}

		return ERR_OK;
	}
	else
	{
		return ERR_VALUE;
	}
}

int main(void)
{
	float x, epsilon;
	
	printf("Enter the x and the epsilon:\n");
	int check = check_input(&x, &epsilon);
	
	if (check != ERR_OK)
	{	
		if (check == ERR_EPS)
			printf("ERROR: Invalid value of epsilon\n");		
		else
			printf("ERROR: Invalid input\n");	
		return check;
	}
	
	float sum = get_sum(x, epsilon), f_value = sin(x);
	float delta = fabs(f_value - sum);
	float rel_error;
	
	if (f_value == 0.0)
		rel_error = 0.0;
	else
		rel_error = delta / fabs(f_value);

	printf("s(x) = %f; f(x) = %f;\ndelta: %f; relative error: %f\n", sum, f_value, delta, rel_error);

	return 0;
}
