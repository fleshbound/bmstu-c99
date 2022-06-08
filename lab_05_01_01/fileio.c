#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

#define READ_COUNT 1

void finput_int(FILE *const f)
{
    int num;

    printf("Enter integers:\n");

    while (scanf("%d", &num) == READ_COUNT)
        fprintf(f, "%d\n", num);
}
