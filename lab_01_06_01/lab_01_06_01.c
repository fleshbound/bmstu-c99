#include <stdio.h>
#include <math.h>
#define ERR_OK 0
#define ERR_FIG 1
#define ERR_VALUE 2

int check_input(float *x, float *y)
{
	int n_var = scanf("%f %f", x, y);
	if (n_var == 2)
	{
		return ERR_OK;
	}
	else
	{
		return ERR_VALUE;
	}
}

float distance(float x1, float x2, float y1, float y2)
{
	return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main(void)
{
	float x_a, y_a, x_b, y_b, x_c, y_c;
	float dist_ab, dist_bc, dist_ac;
	int check;

	printf("Enter the coordinates of A (x, y):\n");
	check = check_input(&x_a, &y_a);
	if (check != ERR_OK)
	{
		printf("ERROR [2]: Invalid coordinates of A\n");
		return check;
	}
	
	printf("Enter the coordinates of B (x, y):\n");
	check = check_input(&x_b, &y_b);
	if (check != ERR_OK)
	{
		printf("ERROR [2]: Invalid coordinates of B\n");
	        return check;
	}

	printf("Enter the coordinates of C (x, y):\n");
	check = check_input(&x_c, &y_c);
	if (check != ERR_OK)
	{       
		printf("ERROR [2]: Invalid coordinates of C\n");
	        return check;
	}

	dist_ab = distance(x_a, x_b, y_a, y_b);
	dist_bc = distance(x_b, x_c, y_b, y_c);
	dist_ac = distance(x_a, x_c, y_a, y_c);

	int check1 = fabs(dist_ab + dist_bc) <= dist_ac;
	int check2 = fabs(dist_ab + dist_ac) <= dist_bc;
	int check3 = fabs(dist_ac + dist_bc) <= dist_ab;

	if (check1 || check2 || check3)
	{
		printf("ERROR [1]: Not a triangle\n");
		return ERR_FIG;
	}
	else
	{
		float half_per = (dist_ab + dist_bc + dist_ac) / 2;
		double area = sqrt(half_per * (half_per - dist_ab) * (half_per - dist_bc) * (half_per - dist_ac));
		printf("Area of triangle ABC: %f\n", area);
	}

	return 0;
}
