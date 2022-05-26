#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "errors.h"
#include "fbin.h"

#define MAX_COUNT 10
#define INPUT_COUNT 1
#define READ_COUNT 1
#define ZERO_POS 0

int init_rand_bin(FILE *fb)
{
    srand(time(NULL));

    for (size_t i = 0; i < MAX_COUNT; i++)
    {
        int rand_int = rand() % 10;
    
        if (!fwrite(&rand_int, sizeof(int), INPUT_COUNT, fb))
            return ERR_WRITE;
    }

    return EXIT_SUCCESS;
}

int fmake_bin(const char *file_name)
{
    FILE *fb = fopen(file_name, "wb");

    if (fb == NULL)
        return ERR_IO;

    int err_init = init_rand_bin(fb);

    if (err_init)
        return err_init;

    fclose(fb);

    printf("File %s was created\n", file_name);

    return EXIT_SUCCESS;
}

int fget_length(FILE *const fb, size_t *const len)
{
    if (fseek(fb, ZERO_POS, SEEK_END))
        return ERR_IO;

    long int size = ftell(fb);

    fseek(fb, ZERO_POS, SEEK_SET);

    if (size <= 0)
        return ERR_EMPTY;

    if (size % sizeof(int) == 0)
        *len = size / sizeof(int);
    else
        return ERR_DATA;
    
    return EXIT_SUCCESS;
}

int fprint_bin(const char *file_name)
{
    size_t len = 0;
    FILE *fb = fopen(file_name, "rb");
    
    if (fb == NULL)
        return ERR_IO;

    int err_code = fget_length(fb, &len);

    if (err_code)
        return err_code;

    for (size_t i = 0; i < len; i++)
    {
        int num;

        if (fread(&num, sizeof(int), READ_COUNT, fb) != READ_COUNT)
            return ERR_READ;
        else
            printf("%d%s", num, (i == len - 1) ? "\n" : " ");
    }

    fclose(fb);

    return EXIT_SUCCESS;
}

int get_number_by_pos(FILE *const fb, const long int pos, int *const num)
{
    fseek(fb, pos * sizeof(int), SEEK_SET);
    
    if (fread(num, sizeof(int), READ_COUNT, fb) != READ_COUNT)
        return ERR_READ;

    return EXIT_SUCCESS;
}

int put_number_by_pos(FILE *const fb, const long int pos, const int *const num)
{
    fseek(fb, pos * sizeof(int), SEEK_SET);
    
    if (!fwrite(num, sizeof(int), INPUT_COUNT, fb))
        return ERR_WRITE;

    return EXIT_SUCCESS;
}

int fswap_bin(FILE *const fb, const size_t pos1, const size_t pos2)
{
    int a, b;
    int err_code = get_number_by_pos(fb, pos1, &a);
    err_code = get_number_by_pos(fb, pos2, &b);

    err_code = put_number_by_pos(fb, pos1, &b);
    err_code = put_number_by_pos(fb, pos2, &a);

    if (err_code)
        return err_code;

    return EXIT_SUCCESS;
}

int fsort_bin(const char *file_name)
{
    size_t len = 0;
    FILE *fb = fopen(file_name, "rb+");

    if (fb == NULL)
        return ERR_IO;

    int err_code = fget_length(fb, &len);
    
    if (err_code)
        return err_code;

    for (size_t i = 0; i < len; i++)
        for (size_t j = 0; j < len - i - 1; j++)
        {
            int num1 = 0, num2 = 0;
            int err_code = get_number_by_pos(fb, j, &num1);
            err_code = get_number_by_pos(fb, j + 1, &num2);

            if ((num1 > num2) && (!err_code))
                err_code = fswap_bin(fb, j, j + 1);
            
            if (err_code)
                return err_code;
        }

    fclose(fb);

    printf("File %s was sorted\n", file_name);

    return EXIT_SUCCESS;
}
