#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_VALUE 1
#define ERR_BYTE 2


int power(int base, int power_n)
{	
	int result = 1;

	if (power_n == 0)
	{
		return result;
	}
	else
	{
		while (power_n > 0)
		{
			result *= base; 
			power_n--;
		}
	}

	return result;
}


// Function gets a decimal number (int)
// and returns its binary form (long long)

long long switch_to_bin(int numb_dec)
{
	long long result = 0, digit = 0;

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

void print_byte(long long number_bin)
{
	for (int i = 7; i >= 0; i--)
	{
		int div = number_bin / pow(10, i);
		number_bin %= power(10, i);

		printf("%d", div);
	}
}


// Function prints formatted byte-zip-result

void print_bin(long long b1, long long b2, long long b3, long long b4)
{
	print_byte(b1);
	print_byte(b2);
	print_byte(b3);
	print_byte(b4);
}


// Function gets a binary number (long long)
// and returns its decimal form (int)

int switch_to_dec(long long numb)
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

void check_scanf(int *b)
{
	int check = scanf("%d", b);

	if (check != 1)
	{
		printf("Error: Invalid value.\n");
		exit(ERR_VALUE);
	}
	else
	{
		if (*b > 255 || *b < 0)
		{
			printf("Error: Invalid byte.\n");
			exit(ERR_BYTE);
		}
	}
}

int main(void)
{
	int dec_b1, dec_b2, dec_b3, dec_b4;
	long long b1, b2, b3, b4;
	int uz1, uz2, uz3, uz4;

	printf("Enter four bytes of unsigned number (zero<=x<two-five-six)\n");
	
	printf("First byte: ");
	check_scanf(&dec_b1);

	printf("Second byte: ");
	check_scanf(&dec_b2);

	printf("Third byte: ");
	check_scanf(&dec_b3);

	printf("Fourth byte: ");
	check_scanf(&dec_b4);

	b1 = switch_to_bin(dec_b1);
	b2 = switch_to_bin(dec_b2);
	b3 = switch_to_bin(dec_b3);
	b4 = switch_to_bin(dec_b4);
	
	printf("Result: ");
	print_bin(b1, b2, b3, b4);

	uz1 = switch_to_dec(b1);
	uz2 = switch_to_dec(b2);
	uz3 = switch_to_dec(b3);
	uz4 = switch_to_dec(b4);

	printf(" %d %d %d %d\n", uz1, uz2, uz3, uz4);

	return 0;
}
