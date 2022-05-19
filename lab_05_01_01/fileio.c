#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

#define ERR_IO 1

void finput_int(FILE *f)
{
    rewind(f);

    int num;

    printf("Enter integers:\n");

    while (scanf("%d", &num) == 1)
        fprintf(f, "%d\n", num);
}
