#include <stdio.h>
#include <stdlib.h>

#include "fgetc.h"

size_t fget_bigger_count(FILE *const f, const double low_limit)
{
    size_t q = 0;
    double num;

    while (fscanf(f, "%lf", &num))
        if (num > low_limit)
            q++;

    return q;
}
