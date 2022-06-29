#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "errors.h"

#define READ_COUNT 1
#define SWAP(type, a, b) { type c = a;  a = b; b = c; }

// Поиск первого и второго максимумов в файле (стандартный поток ввода)
int process(FILE *const f, int *const res_1, int *const res_2)
{
    int num = 0, max_1 = 0, max_2 = 0;

    if (fscanf(f, "%d", &max_1) != READ_COUNT)
    {
        fprintf(stderr, "No input numbers were found\n");
        return ERR_EMPTY;
    }

    if (fscanf(f, "%d", &max_2) != READ_COUNT)
    {
        fprintf(stderr, "At least two numbers were expected\n");
        return ERR_NOT_ENOUGH;
    }

    if (max_2 > max_1)
        SWAP(int, max_1, max_2);

    while (fscanf(f, "%d", &num) == READ_COUNT)
    {
        if (num > max_2)
            max_2 = num;

        if (max_2 > max_1)
            SWAP(int, max_1, max_2);
    }

    *res_1 = max_1;
    *res_2 = max_2;

    return EXIT_SUCCESS;
}
