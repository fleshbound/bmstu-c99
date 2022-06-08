#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "studmatch.h"
#include "studgetput.h"

int put_matches(FILE *const f, student_info_t students[INFO_COUNT], const size_t stud_count, char *const substr)
{
    size_t count = 0;

    for (size_t i = 0; i < stud_count; i++)
        if (strstr(students[i].surname, substr) == students[i].surname)
        {
            put_stud(f, students[i]);
            count++;
        }

    if (count == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}

int show_students(char *const file_in, char *const file_out, char *const substr)
{
    if (strlen(substr) > NAME_LEN - 1)
        return ERR_ARGS;

    FILE *f_in = fopen(file_in, "rt");

    if (f_in == NULL)
        return ERR_IO;

    student_info_t students[INFO_COUNT];
    size_t stud_count = 0;
    int err_code = get_students(f_in, students, &stud_count);

    if (err_code)
        return err_code;

    fclose(f_in);

    FILE *f_out = fopen(file_out, "wt");

    if (f_out == NULL)
        return ERR_IO;

    err_code = put_matches(f_out, students, stud_count, substr);

    if (err_code)
        return err_code;

    fclose(f_out);
    
    return EXIT_SUCCESS;
}
