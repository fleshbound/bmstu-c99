#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int main(void)
{
	float a, b, phi;

	printf("Введите основания a, b и угол фи (град.):\n");
	scanf("%f %f %f", &a, &b, &phi);

	float phi_rad = phi * M_PI / 180.0, delta = fabs( a - b ) / 2;
	float height = delta * tanf(phi_rad);
	float space = 2 * 0.5 * delta * height + ( a + b - 2 * delta ) / 2 * height;

	printf("Площадь трапеции: %f \n", space);

	return 0;
}
