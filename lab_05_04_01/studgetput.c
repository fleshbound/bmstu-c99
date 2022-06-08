#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "errors.h"
#include "studgetput.h"

// Записать данные студента
void put_stud(FILE *const f, student_info_t stud)
{
    fprintf(f, "%s", stud.surname);
    fprintf(f, "%s", stud.name);

    for (size_t i = 0; i < MARKS_COUNT; i++)
        fprintf(f, "%u%s", stud.marks[i], (i == MARKS_COUNT - 1) ? "\n" : " ");
}

// Записать данные всех студентов списка
int put_students(FILE *const f, student_info_t *const students, const size_t stud_count)
{
    rewind(f);

    for (size_t i = 0; i < stud_count; i++)
        put_stud(f, students[i]);

    return EXIT_SUCCESS;
}

// Обнуление фамилии и имени
void null_strings(student_info_t *const stud)
{
    memset(stud->surname, '\0', SURNAME_LEN);
    memset(stud->name, '\0', NAME_LEN);
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
int get_students(FILE *const f, student_info_t students[INFO_COUNT], size_t *const stud_count)
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
