#include <stdio.h>
#include <math.h>
#define CODE_OK 0
#define ERR_FIG -1
#define ERR_VALUE 2

int check_input(float *x, float *y)
{
	int n_var = scanf("%f %f", x, y);
	if (n_var == 2)
	{
		return CODE_OK;
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

double get_area(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float dist12 = distance(x1, x2, y1, y2);
	float dist23 = distance(x2, x3, y2, y3);
	float dist31 = distance(x3, x1, y3, y1);

	int check1 = fabs(dist12 + dist23) <= dist31;
	int check2 = fabs(dist12 + dist31) <= dist23;
	int check3 = fabs(dist23 + dist31) <= dist12;

	if (check1 || check2 || check3)
	{
		return ERR_FIG;
	}

	float half_per = (dist12 + dist23 + dist31) / 2;
	double area = sqrt(half_per * (half_per - dist12) * (half_per - dist23) * (half_per - dist31));

	return area;
}

int main(void)
{
	float x_a, y_a, x_b, y_b, x_c, y_c;
	int check;

	printf("Enter the coordinates of A (x, y):\n");
	check = check_input(&x_a, &y_a);
	if (check != CODE_OK)
	{
		printf("ERROR [2]: Invalid coordinates of A\n");
		return ERR_VALUE;
	}
	
	printf("Enter the coordinates of B (x, y):\n");
	check = check_input(&x_b, &y_b);
	if (check != CODE_OK)
	{
		printf("ERROR [2]: Invalid coordinates of B\n");
		return ERR_VALUE;
	}

	printf("Enter the coordinates of C (x, y):\n");
	check = check_input(&x_c, &y_c);
	if (check != CODE_OK)
	{       
		printf("ERROR [2]: Invalid coordinates of C\n");
		return ERR_VALUE;
	}

	double area = get_area(x_a, y_a, x_b, y_b, x_c, y_c);
	if (area < 0)
	{
		printf("ERROR [1]: Not a triangle\n");
		return ERR_FIG;
	}

	printf("Area of triangle ABC: %f\n", area);

	return CODE_OK;
}

