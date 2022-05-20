#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "fileio.h"
#include "errors.h"

int main(void)
{
    FILE *f;

    f = fopen("in.txt", "w");

    if (f == NULL)
        return ERR_IO;

    finput_int(f);
    fclose(f);

    f = fopen("in.txt", "r"); 
    int res_max_1, res_max_2;
    int err_proc = process(f, &res_max_1, &res_max_2);

    fclose(f);
    if (err_proc)
        return err_proc;

    return EXIT_SUCCESS;
}
