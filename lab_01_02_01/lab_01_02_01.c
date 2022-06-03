#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define CODE_OK 0
#define DEGREES 180.0

int main(void)
{
	float a, b, phi;

	printf("Введите основания a, b и угол фи (град.):\n");
	scanf("%f %f %f", &a, &b, &phi);

	float phi_rad = phi * M_PI / DEGREES;
	float height = fabs(b - a) / 2 * tanf(phi_rad);
	float space = (a + b) / 2 * height;

	printf("Площадь трапеции: %f \n", space);

	return CODE_OK;
}

