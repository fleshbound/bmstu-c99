#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "errors.h"
#include "studsort.h"
#include "studgetput.h"

void swap_stud(studinfo *const stud1, studinfo *const stud2)
{
    studinfo buf = *stud1;
    *stud1 = *stud2;
    *stud2 = buf;
}

int is_first_bigger(studinfo stud1, studinfo stud2)
{
    if (strcmp(stud1.surname, stud2.surname) > 0)
        return TRUE;

    if (strcmp(stud1.surname, stud2.surname) < 0)
        return FALSE;

    if ((strcmp(stud1.name, stud2.name) >= 0) && (strcmp(stud1.surname, stud2.surname) == 0))
        return TRUE;

    return FALSE;
}

void sort_studinfo(studinfo students[INFO_COUNT], const size_t stud_count)
{
    for (size_t i = 0; i < stud_count - 1; i++)
        for (size_t j = 0; j < stud_count - i - 1; j++)
            if (is_first_bigger(students[j], students[j + 1]))
                swap_stud(&students[j], &students[j + 1]);
}

void print_studinfo(studinfo students[INFO_COUNT], const size_t stud_count)
{
    for (size_t i = 0; i < stud_count; i++)
    {
        printf("%s%s", students[i].surname, students[i].name);

        for (size_t j = 0; j < MARKS_COUNT; j++)
            printf("%u%s", students[i].marks[j], (j == MARKS_COUNT - 1) ? "\n" : " ");
    }
}

int stud_sort(char *const file_in)
{
    FILE *f_in = fopen(file_in, "rt");

    if (f_in == NULL)
        return ERR_IO;

    studinfo students[INFO_COUNT];
    size_t stud_count = 0;
    int err_code = get_students(f_in, students, &stud_count);

    if (err_code)
        return err_code;

    fclose(f_in);

    sort_studinfo(students, stud_count);
    print_studinfo(students, stud_count);
   
    return EXIT_SUCCESS;
}
