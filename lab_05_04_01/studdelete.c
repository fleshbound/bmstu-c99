#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "studdelete.h"
#include "studgetput.h"

// Получить средний балл студента
double get_avg(studinfo stud)
{
    double sum = 0.;

    for (size_t i = 0; i < MARKS_COUNT; i++)
        sum += stud.marks[i];

    return sum / MARKS_COUNT;
}

double get_avg_all(studinfo stud_all[INFO_COUNT], const size_t stud_count)
{
    double sum = 0.;

    for (size_t i = 0; i < stud_count; i++)
        sum += get_avg(stud_all[i]);

    return sum / stud_count;
}

size_t get_higher_avg(studinfo stud_all[INFO_COUNT], const size_t all_count, studinfo higher_avg[INFO_COUNT])
{
    size_t high_count = 0;
    double avg = get_avg_all(stud_all, all_count);

    for (size_t i = 0; i < all_count; i++)
        if (get_avg(stud_all[i]) >= avg)
            higher_avg[high_count++] = stud_all[i];

    return high_count;
}

int stud_delete(char *file_in)
{
    FILE *f_in = fopen(file_in, "rt");

    if (f_in == NULL)
        return ERR_IO;

    studinfo stud_all[INFO_COUNT];
    size_t stud_count = 0;
    int err_code = get_stud_all(f_in, stud_all, &stud_count);

    if (err_code)
        return err_code;

    fclose(f_in);

    studinfo higher_avg[INFO_COUNT];
    size_t high_count = get_higher_avg(stud_all, stud_count, higher_avg);

    if (high_count == 0)
        return ERR_EMPTY;

    FILE *f_out = fopen(file_in, "wt");

    if (f_out == NULL)
        return ERR_IO;

    err_code = put_stud_all(f_out, higher_avg, high_count);

    if (err_code)
        return err_code;

    fclose(f_out);

    return EXIT_SUCCESS;
}
