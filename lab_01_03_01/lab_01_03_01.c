#include <stdio.h>
#include <math.h>

int main(void)
{
	float value1, value2, temp1, temp2;
	
	printf("Введите объем (л) и температуру воды в 1-й емкости:\n");	
	scanf("%f%f", &value1, &temp1);

	printf("Введите объем (л) и температуру воды в 2-й емкости:\n");
        scanf("%f%f", &value2, &temp2);

	float value = value1 + value2;
	float temp = (value1 * temp1 + value2 * temp2) / value;

	printf("Объем смеси (л): %f ; температура смеси: %f\n", value, temp);

	return 0;
}
