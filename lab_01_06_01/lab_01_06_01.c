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
	return sqrtf( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}

int main(void)
{
	float x_A, y_A, x_B, y_B, x_C, y_C;
	float dist_AB, dist_BC, dist_AC;
	int check;

	printf("Enter the coordinates of A (x, y):\n");
	check = check_input(&x_A, &y_A);
	if (check != ERR_OK)
	{
		printf("ERROR [2]: Invalid coordinates of A\n");
		return check;
	}
	
	printf("Enter the coordinates of B (x, y):\n");
        check = check_input(&x_B, &y_B);
        if (check != ERR_OK)
        {
		printf("ERROR [2]: Invalid coordinates of B\n");
                return check;
        }

	printf("Enter the coordinates of C (x, y):\n");
        check = check_input(&x_C, &y_C);
        if (check != ERR_OK)
        {       
                printf("ERROR [2]: Invalid coordinates of C\n");
                return check;
        }
        
	dist_AB = distance(x_A, x_B, y_A, y_B);
	dist_BC = distance(x_B, x_C, y_B, y_C);
	dist_AC = distance(x_A, x_C, y_A, y_C);

	int check1 = fabs(dist_AB + dist_BC) <= dist_AC;
	int check2 = fabs(dist_AB + dist_AC) <= dist_BC;
	int check3 = fabs(dist_AC + dist_BC) <= dist_AB;

	if (check1 || check2 || check3)
	{
		printf("ERROR [1]: Not a triangle\n");
		return ERR_FIG;
	}
	else
	{
		float half_per = (dist_AB + dist_BC + dist_AC) / 2;
		float area  = sqrt( half_per * (half_per - dist_AB) 
				* (half_per - dist_BC) * (half_per - dist_AC) );
		printf("Area of triangle ABC: %f\n", area);
	}

	return 0;
}
