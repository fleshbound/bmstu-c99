// Сортировка пузырьком, тип int, упорядочивание по возрастанию

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "fbin.h"

#define ARG_COUNT 3

int main(int argc, char *argv[])
{
    if (argc != ARG_COUNT)
        return ERR_ARGS;

    int err_code = EXIT_SUCCESS;

    if (!strcmp(argv[1], "c"))
        err_code = fmake_bin(argv[2]);

    if (!strcmp(argv[1], "p"))
        err_code = fprint_bin(argv[2]);

    if (!strcmp(argv[1], "s"))
        err_code = fsort_bin(argv[2]);

    return err_code;
}
