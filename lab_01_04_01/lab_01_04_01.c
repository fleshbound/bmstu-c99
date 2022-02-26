#include <stdio.h>

int main(void)
{
	int curr_flat, n_floor = 9, n_flat = 4;

	printf("Введите номер квартиры:\n");
	scanf("%d", &curr_flat);

	int curr_entr = (curr_flat - 1) / (n_floor * n_flat) + 1;
	int curr_floor = ( (curr_flat - 1) % (n_floor * n_flat) ) / n_flat + 1;

	printf("Текущий подъезд: %d ; текущий этаж: %d\n", curr_entr, curr_floor);

	return 0;
}
