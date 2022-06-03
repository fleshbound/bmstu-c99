#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "studdelete.h"
#include "studgetput.h"

int stud_delete(char *file_in)
{
    FILE *f_in = fopen(file_in, "rt");

    if (f_in == NULL)
        return ERR_IO;

    size_t stud_count = 0;
    studinfo stud_all[INFO_COUNT];
    int err_code = get_stud_all(f_in, stud_all, &stud_count);

    if (err_code)
        return err_code;

    fclose(f_in);

    FILE *f_out = fopen(file_in, "wt");

    err_code = put_stud_delete(f_out, stud_all, stud_count);

    if (err_code)
        return err_code;

    fclose(f_out);

    return EXIT_SUCCESS;
}
