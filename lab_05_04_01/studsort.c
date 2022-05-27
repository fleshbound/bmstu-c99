#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "errors.h"
#include "studsort.h"
#include "studgetput.h"

#define TRUE 1
#define FALSE 0

void swap_stud(studinfo *const stud1, studinfo *const stud2)
{
    studinfo buf = *stud1;
    *stud1 = *stud2;
    *stud2 = buf;
}

int is_first_bigger(studinfo *const stud1, studinfo *const stud2)
{
    if (strcmp(stud1->surname, stud2->surname) > 0)
        return TRUE;

    if (strcmp(stud1->surname, stud2->surname) < 0)
        return FALSE;

    if (strcmp(stud1->name, stud2->name) > 0)
        return TRUE;

    return FALSE;
}

void sort_studinfo(studinfo *const stud_all, const size_t stud_count)
{
    for (size_t i = 0; i < stud_count - 1; i++)
        for (size_t j = 0; j < stud_count - i - 1; j++)
            if (is_first_bigger(&stud_all[j], &stud_all[j + 1]))
                swap_stud(&stud_all[j], &stud_all[j + 1]);
}

int stud_sort(char *file_in)
{
    FILE *f = fopen(file_in, "rt+");

    if (f == NULL)
        return ERR_IO;

    studinfo stud_all[INFO_COUNT];

    size_t stud_c = 0;
    int err_code = get_stud_all(f, stud_all, &stud_c);

    if (err_code)
        return err_code;

    sort_studinfo(stud_all, stud_c);

    err_code = put_stud_all(f, stud_all, stud_c);

    if (err_code)
        return err_code;

    fclose(f);
    
    return EXIT_SUCCESS;
}
