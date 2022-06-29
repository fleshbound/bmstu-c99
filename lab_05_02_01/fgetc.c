#include <stdio.h>
#include <stdlib.h>

#include "fgetc.h"

#define READ_COUNT 1

size_t fget_bigger_count(FILE *const f, const double low_limit)
{
    fseek(f, 0, SEEK_SET);

    size_t q = 0;
    double num;

    while (fscanf(f, "%lf", &num) == READ_COUNT)
        if (num > low_limit)
            q++;

    return q;
}
