#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "studfprint.h"
#include "studgetput.h"

size_t get_matches(studinfo stud_all[INFO_COUNT], const size_t all_count, studinfo matches[INFO_COUNT], char *const substr)
{
    size_t match_count = 0;

    for (size_t i = 0; i < all_count; i++)
        if (strstr(stud_all[i].surname, substr) == stud_all[i].surname)
            matches[match_count++] = stud_all[i];

    return match_count;
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

    studinfo matches[INFO_COUNT];
    size_t match_count = get_matches(stud_all, stud_count, matches, sub_str);

    if (match_count == 0)
        return ERR_EMPTY;

    FILE *f_out = fopen(file_out, "wt");

    if (f_out == NULL)
        return ERR_IO;

    err_code = put_stud_all(f_out, matches, match_count);

    if (err_code)
        return err_code;

    fclose(f_out);
    
    return EXIT_SUCCESS;
}
