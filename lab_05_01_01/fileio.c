#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

void finput_int(FILE *f)
{
    rewind(f);

    int num;

    printf("Enter integers:\n");

    while (scanf("%d", &num) == 1)
        fprintf(f, "%d\n", num);
}
