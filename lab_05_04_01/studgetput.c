#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "errors.h"
#include "studgetput.h"

// Записать данные студента
int put_stud(FILE *const f, studinfo stud)
{
    if (fprintf(f, "%s", stud.surname) < 0)
        return ERR_WRITE;

    if (fprintf(f, "%s", stud.name) < 0)
        return ERR_WRITE;

    for (size_t i = 0; i < MARKS_COUNT; i++)
        if (fprintf(f, "%u%s", stud.marks[i], (i == MARKS_COUNT - 1) ? "\n" : " ") < 0)
            return ERR_WRITE;

    return EXIT_SUCCESS;
}

// Записать данные всех студентов списка
int put_students(FILE *const f, studinfo *const students, const size_t stud_count)
{
    rewind(f);

    for (size_t i = 0; i < stud_count; i++)
    {
        int err_code = put_stud(f, students[i]);

        if (err_code)
            return err_code;
    }

    return EXIT_SUCCESS;
}

// Обнуление фамилии и имени
void null_strings(studinfo *const stud)
{
    for (size_t i = 0; i < SURNAME_LEN; i++)
        stud->surname[i] = '\0';

    for (size_t i = 0; i < NAME_LEN; i++)
        stud->name[i] = '\0';
}

int get_studstr(FILE *const f, int *const is_end, char *str, const size_t max_len)
{
    if ((!*is_end) && (fgets(str, max_len, f) == NULL))
        return ERR_DATA;

    while ((!*is_end) && (str[0] == '\n'))
    {
        if ((fgets(str, max_len, f) == NULL) && (!feof(f)))
            return ERR_DATA;
        else if (feof(f))
            *is_end = TRUE;
    }

    return EXIT_SUCCESS;
}

// Считать данные о всех студентах
// Пока считываются пустые строчки, считывать фамилию и имя
// Если не получилось, конец файла или ошибка
// Если получилось и не конец файла, читаем следующее
// Если закончили читать и не конец файла, ошибка...
int get_students(FILE *const f, studinfo students[INFO_COUNT], size_t *const stud_count)
{
    int is_end = FALSE;
    size_t q = 0;
    
    while (!is_end)
    {
        null_strings(&students[q]);

        int err_code = get_studstr(f, &is_end, students[q].surname, SURNAME_LEN);

        if (err_code)
            return err_code;

        err_code = get_studstr(f, &is_end, students[q].name, NAME_LEN);

        if (err_code)
            return err_code;

        // Оценки
        for (size_t i = 0; (!is_end) && (i < MARKS_COUNT); i++)
            if (fscanf(f, "%u", &students[q].marks[i]) < 0)
                return ERR_DATA; 

        if (!is_end)
            q++;
    }

    if (!is_end)
        return ERR_DATA;

    *stud_count = q;

    if (*stud_count == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}
