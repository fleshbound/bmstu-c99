#include <stdio.h>
#include <stdlib.h>

#include "fmath.h"
#include "fgetc.h"
#include "errors.h"

void print_result(const size_t res)
{
    printf("Result: %lu\n", res);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return ERR_ARG;

    FILE *f;
    f = fopen(argv[1], "r");
    
    if (f == NULL)
        return ERR_IO;

    double max, min;
    int err_code = fget_min_max(f, &min, &max);

    if (err_code)
        return err_code;

    double avg = (max + min) / 2;
    rewind(f);
    size_t count = fget_bigger_count(f, avg);
    fclose(f);

    print_result(count);

    return EXIT_SUCCESS;
}
