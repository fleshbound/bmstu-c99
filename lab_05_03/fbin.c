#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "errors.h"
#include "fbin.h"

#define MAX_COUNT 10
#define INPUT_COUNT 1
#define READ_COUNT 1
#define ZERO_POS 0

int init_rand_bin(FILE *const fb)
{
    srand(time(NULL));

    for (size_t i = 0; i < MAX_COUNT; i++)
    {
        int rand_int = rand() % 10;
    
        if (fwrite(&rand_int, sizeof(int), INPUT_COUNT, fb) != INPUT_COUNT)
            return ERR_WRITE;
    }

    return EXIT_SUCCESS;
}

int fmake_bin(const char *const file_name)
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

    if (size <= 0)
        return ERR_EMPTY;

    if (size % sizeof(int) != 0)
        return ERR_DATA;

    *len = size / sizeof(int);
    
    if (fseek(fb, ZERO_POS, SEEK_SET))
        return ERR_IO;
    
    return EXIT_SUCCESS;
}

int fprint_bin(const char *const file_name)
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
        
        printf("%d%s", num, (i == len - 1) ? "\n" : " ");
    }

    fclose(fb);

    return EXIT_SUCCESS;
}

int get_number_by_pos(FILE *const fb, const long int pos, int *const num)
{
    if (fseek(fb, pos * sizeof(int), SEEK_SET))
        return ERR_IO;
    
    if (fread(num, sizeof(int), READ_COUNT, fb) != READ_COUNT)
        return ERR_READ;

    return EXIT_SUCCESS;
}

int put_number_by_pos(FILE *const fb, const long int pos, const int *const num)
{
    if (fseek(fb, pos * sizeof(int), SEEK_SET))
        return ERR_IO;
    
    if (fwrite(num, sizeof(int), INPUT_COUNT, fb) != INPUT_COUNT)
        return ERR_WRITE;

    return EXIT_SUCCESS;
}

int fswap_bin(FILE *const fb, const size_t pos1, const size_t pos2)
{
    int a, b;
    int err_code = EXIT_SUCCESS;
    
    err_code = get_number_by_pos(fb, pos1, &a);

    if (err_code)
        return err_code;

    err_code = get_number_by_pos(fb, pos2, &b);

    if (err_code)
        return err_code;

    err_code = put_number_by_pos(fb, pos1, &b);

    if (err_code)
        return err_code;

    err_code = put_number_by_pos(fb, pos2, &a);

    return err_code;
}

int fsort_bin(const char *const file_name)
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
            
            err_code = get_number_by_pos(fb, j, &num1);
            
            if (err_code)
                return err_code;
            
            err_code = get_number_by_pos(fb, j + 1, &num2);

            if (err_code)
                return err_code;

            if (num1 > num2)
                err_code = fswap_bin(fb, j, j + 1);
    
            if (err_code)
                return err_code;
        }

    fclose(fb);

    printf("File was sorted.\n");

    return EXIT_SUCCESS;
}
