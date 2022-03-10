#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define CODE_OK 0
#define ERR_VALUE 1
#define ERR_BYTE 2
#define BITES 255

int power(int base, int power_n)
{	
	int result = 1;

	while (power_n > 0)
	{
		result *= base; 
		power_n--;
	}

	return result;
}


// Function gets a decimal number (int)
// and returns its binary form (long long)

uint32_t switch_to_bin(int numb_dec)
{
	uint32_t result = 0, digit = 0;

	int i = 0;
	while (numb_dec > 0)
	{
		digit = (numb_dec % 2) * pow(10, i);
		numb_dec /= 2;	
		
		result += digit;
		i += 1;
	}

	return result;
}


// Function prints (formatted) binary number (long long) in 8 places

void print_byte(uint32_t number_bin)
{
	for (int i = 7; i >= 0; i--)
	{
		int div = number_bin / pow(10, i);
		number_bin %= power(10, i);

		printf("%d", div);
	}
}


// Function prints formatted byte-zip-result

void print_bin(uint32_t b1, uint32_t b2, uint32_t b3, uint32_t b4)
{
	print_byte(b1);
	print_byte(b2);
	print_byte(b3);
	print_byte(b4);
}


// Function gets a binary number (long long)
// and returns its decimal form (int)

int switch_to_dec(uint32_t numb)
{
	int result = 0, i = 0;

	while (numb > 0)
	{
		int digit = numb % 10;
		result += power(2, i) * digit;

		numb /= 10;
		i++;
	}

	return result;
}


// Input check

int check_scanf(int *b)
{
	int check = scanf("%d", b);

	if (check != 1)
	{
		return ERR_VALUE;
	}

	if (*b > BITES || *b < 0)
		{
			return ERR_BYTE;
		}

	return CODE_OK;
}

int all_check_scanf(int *b1, int *b2, int *b3, int *b4)
{
	
	printf("First byte: ");
        int check = check_scanf(b1);
        if (check == ERR_VALUE)
        {
                printf("Error: Invalid value.\n");
                return ERR_VALUE;
        }
        if (check == ERR_BYTE)
        {
                printf("Error: Invalid byte.\n");
                return ERR_BYTE;
        }

        printf("Second byte: ");
        check = check_scanf(b2);
        if (check == ERR_VALUE)
        {
                printf("Error: Invalid value.\n");
                return ERR_VALUE;
        }
        if (check == ERR_BYTE)
        {
                printf("Error: Invalid byte.\n");
                return ERR_BYTE;
        }

        printf("Third byte: ");
        check = check_scanf(b3);
        if (check == ERR_VALUE)
        {
                printf("Error: Invalid value.\n");
                return ERR_VALUE;
        }
        if (check == ERR_BYTE)
        {
                printf("Error: Invalid byte.\n");
                return ERR_BYTE;
        }

        printf("Fourth byte: ");
        check = check_scanf(b4);
        if (check == ERR_VALUE)
        {
                printf("Error: Invalid value.\n");
                return ERR_VALUE;
        }
        if (check == ERR_BYTE)
        {
                printf("Error: Invalid byte.\n");
                return ERR_BYTE;
        }

	return CODE_OK;
}


int main(void)
{
	int dec_b1, dec_b2, dec_b3, dec_b4;

	printf("Enter four bytes of unsigned number (zero<=x<two-five-six)\n");
	
	int all_check = all_check_scanf(&dec_b1, &dec_b2, &dec_b3, &dec_b4);

	if (all_check == ERR_VALUE)
		return ERR_VALUE;
	if (all_check == ERR_BYTE)
		return ERR_BYTE;

	uint32_t b1 = switch_to_bin(dec_b1);
	uint32_t b2 = switch_to_bin(dec_b2);
	uint32_t b3 = switch_to_bin(dec_b3);
	uint32_t b4 = switch_to_bin(dec_b4);
	
	printf("Result: ");
	print_bin(b1, b2, b3, b4);

	int unzipped1 = switch_to_dec(b1);
	int unzipped2 = switch_to_dec(b2);
	int unzipped3 = switch_to_dec(b3);
	int unzipped4 = switch_to_dec(b4);

	printf(" %d %d %d %d\n", unzipped1, unzipped2, unzipped3, unzipped4);

	return CODE_OK;
}

