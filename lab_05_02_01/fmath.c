#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

int fget_min_max(FILE *f, double *const min, double *const max)
{
    double num, curr_max, curr_min;

    if (fscanf(f, "%lf", &curr_min) != 1)
    {
        printf("Data error\n");
        return ERR_EMPTY;
    }

    curr_max = curr_min;

    while (!feof(f))
    {
        if (fscanf(f, "%lf", &num) == 1)
        {
	    	if (num >= curr_max)
                curr_max = num;
            else if (num <= curr_min)
                curr_min = num;
        }
        else if (!feof(f))
        {
            printf("Error: Double numbers were excepted\n");
            return ERR_INPUT;
        }
    }
    *min = curr_min;
    *max = curr_max;

    return EXIT_SUCCESS;
}
