#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#define READ_COUNT 1

int fget_min_max(FILE *f, double *const min, double *const max)
{
    double num, curr_max, curr_min;

    if (fscanf(f, "%lf", &curr_min) != READ_COUNT)
    {
        fprintf(stderr, "Data error\n");
        return ERR_EMPTY;
    }

    curr_max = curr_min;

    while (fscanf(f, "%lf", &num) == READ_COUNT)
    {
        if (num >= curr_max)
            curr_max = num;
        else if (num <= curr_min)
            curr_min = num;
    }
    
    if (!feof(f))
    {
        fprintf(stderr, "Error: Double numbers were excepted\n");
        return ERR_INPUT;
    }
    
    *min = curr_min;
    *max = curr_max;

    return EXIT_SUCCESS;
}
