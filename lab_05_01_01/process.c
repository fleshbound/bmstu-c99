#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "errors.h"

void swap_int(int *const a, int *const b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

// Поиск первого и второго максимумов в файле
int process(FILE *const f, int *const res_1, int *const res_2)
{
    rewind(f);

    int num = 0, max_1 = 0, max_2 = 0;

    if (fscanf(f, "%d", &max_1) != 1)
    {
        printf("No input numbers were found\n");
        return ERR_EMPTY;
    }

    if (fscanf(f, "%d", &max_2) != 1)
    {
        printf("At least two numbers were expected\n");
        return ERR_NOT_ENOUGH;
    }

    if (max_2 > max_1)
        swap_int(&max_1, &max_2);

    while (fscanf(f, "%d", &num) == 1)
    {
        if (num > max_2)
            max_2 = num;

        if (max_2 > max_1)
            swap_int(&max_1, &max_2);
    }

    *res_1 = max_1;
    *res_2 = max_2;

    printf("Result: %d %d\n", *res_1, *res_2);

    return EXIT_SUCCESS;
}
