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
            return ERR_INPUT;
    }

    return EXIT_SUCCESS;
}

int fmake_bin(const char *file_name)
{
    FILE *fb;
    fb = fopen(file_name, "wb");

    if (fb == NULL)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    int err_init = init_rand_bin(fb);

    if (err_init)
        return err_init;

    fclose(fb);

    printf("File %s was created\n", file_name);

    return EXIT_SUCCESS;
}

int fget_length(const char *file_name, size_t *const len)
{
    FILE *fb = fopen(file_name, "rb");
    
    if (fb == NULL)
        return ERR_IO;

    fseek(fb, ZERO_POS, SEEK_END);
    long int size = ftell(fb);

    fclose(fb);

    if (size == -1L)
        return ERR_IO;

    *len = size / sizeof(int);
    
    return EXIT_SUCCESS;
}

int fprint_bin(const char *file_name)
{
    size_t len = 0;
    int err_code = fget_length(file_name, &len);

    if (err_code)
    {
        printf("I/O error\n");
        return err_code;
    }    

    // printf("%lu\n", len);

    FILE *fb;
    fb = fopen(file_name, "rb");

    for (size_t i = 0; i < len; i++)
    {
        int num;

        if (fread(&num, sizeof(int), READ_COUNT, fb) != READ_COUNT)
        {
            printf("Error while reading bin file\n");
            return ERR_IO;
        }
        else
            printf("%d ", num);
    }

    printf("\n");
    fclose(fb);

    return EXIT_SUCCESS;
}

int get_number_by_pos(const char *file_name, const long int pos, int *const num)
{
    FILE *fb = fopen(file_name, "rb");

    if (fb == NULL)
        return ERR_IO;

    fseek(fb, pos * sizeof(int), SEEK_SET);
    
    if (fread(num, sizeof(int), READ_COUNT, fb) != READ_COUNT)
        return ERR_IO;

    fclose(fb);
    
    return EXIT_SUCCESS;
}

int put_number_by_pos(const char *file_name, const long int pos, const int *const num)
{
    FILE *fb = fopen(file_name, "r+b");
    
    if (fb == NULL)
        return ERR_IO;

    fseek(fb, pos * sizeof(int), SEEK_SET);
    
    if (!fwrite(num, sizeof(int), INPUT_COUNT, fb))
        return ERR_IO;

    fclose(fb);

    return EXIT_SUCCESS;
}

int fswap_bin(const char *file_name, const size_t pos1, const size_t pos2)
{
    int a, b;
    int err_code = get_number_by_pos(file_name, pos1, &a);
    err_code = get_number_by_pos(file_name, pos2, &b);

    err_code = put_number_by_pos(file_name, pos1, &b);
    err_code = put_number_by_pos(file_name, pos2, &a);

    if (err_code)
        return err_code;

    return EXIT_SUCCESS;
}

int fsort_bin(const char *file_name)
{
    size_t len = 0;
    int err_file = fget_length(file_name, &len);
    
    if (err_file)
    {
        printf("I/O error\n");
        return err_file;
    }

    for (size_t i = 0; i < len; i++)
        for (size_t j = 0; j < len - i - 1; j++)
        {
            int num1 = 0, num2 = 0;
            int err_code = get_number_by_pos(file_name, j, &num1);
            err_code = get_number_by_pos(file_name, j + 1, &num2);
            // printf("%lu: %d, %d\n", j, num1, num2);

            if (num1 > num2)
                err_code = fswap_bin(file_name, j, j + 1);
            
            if (err_code)
                return err_code;
        }

    printf("File %s was sorted\n", file_name);

    return EXIT_SUCCESS;
}
