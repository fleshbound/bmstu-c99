#include <stdio.h>
#include <stdlib.h>

#include "fgetc.h"

size_t fget_bigger_count(FILE *const f, const double low_limit)
{
    size_t q = 0;
    double num;

    while (!feof(f))
        if (fscanf(f, "%lf", &num) == 1)
            if (num > low_limit)
                q++;

    return q;
}
