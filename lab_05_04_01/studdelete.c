#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "studdelete.h"
#include "studgetput.h"

// Получить средний балл студента
double get_avg(student_info_t stud)
{
    double sum = 0;

    for (size_t i = 0; i < MARKS_COUNT; i++)
        sum += stud.marks[i];

    return sum / MARKS_COUNT;
}

double get_avg_all(student_info_t students[INFO_COUNT], const size_t stud_count)
{
    double sum = 0;

    for (size_t i = 0; i < stud_count; i++)
        sum += get_avg(students[i]);

    return sum / stud_count;
}

int put_higher_avg(FILE *const f, student_info_t students[INFO_COUNT], size_t const stud_count)
{
    double avg = get_avg_all(students, stud_count);
    size_t count = 0;

    for (size_t i = 0; i < stud_count; i++)
        if (get_avg(students[i]) >= avg)
        {
            put_stud(f, students[i]);
            count++;
        }

    if (count == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}

int delete_students(char *file_in)
{
    FILE *f_in = fopen(file_in, "rt");

    if (f_in == NULL)
        return ERR_IO;

    student_info_t students[INFO_COUNT];
    size_t stud_count = 0;
    int err_code = get_students(f_in, students, &stud_count);

    if (err_code)
        return err_code;

    fclose(f_in);

    FILE *f_out = fopen(file_in, "wt");

    if (f_out == NULL)
        return ERR_IO;

    err_code = put_higher_avg(f_out, students, stud_count);

    if (err_code)
        return err_code;

    fclose(f_out);

    return EXIT_SUCCESS;
}
