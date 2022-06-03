#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "studfprint.h"
#include "studgetput.h"

int put_matches(FILE *const f, studinfo stud_all[INFO_COUNT], const size_t all_count, char *const substr)
{
    size_t count = 0;

    for (size_t i = 0; i < all_count; i++)
        if (strstr(stud_all[i].surname, substr) == stud_all[i].surname)
        {
            int err_code = put_stud(f, stud_all[i]);

            if (err_code)
                return err_code;

            count++;
        }

    if (count == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}

int stud_fprint(char *const file_in, char *const file_out, char *const sub_str)
{
    if (strlen(sub_str) > NAME_LEN - 1)
        return ERR_ARGS;

    FILE *f_in = fopen(file_in, "rt");

    if (f_in == NULL)
        return ERR_IO;

    studinfo stud_all[INFO_COUNT];
    size_t stud_count = 0;
    int err_code = get_stud_all(f_in, stud_all, &stud_count);

    if (err_code)
        return err_code;

    fclose(f_in);

    FILE *f_out = fopen(file_out, "wt");

    if (f_out == NULL)
        return ERR_IO;

    err_code = put_matches(f_out, stud_all, stud_count, sub_str);

    if (err_code)
        return err_code;

    fclose(f_out);
    
    return EXIT_SUCCESS;
}
