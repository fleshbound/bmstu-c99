#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "errors.h"
#include "studsort.h"
#include "studgetput.h"
#include "studdelete.h"

#define READ_COUNT 1

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
int put_stud_all(FILE *const f, studinfo *const stud_all, const size_t stud_size)
{
    rewind(f);

    for (size_t i = 0; i < stud_size; i++)
    {
        int err_code = put_stud(f, stud_all[i]);

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

// Считать данные о всех студентах
int get_stud_all(FILE *const f, studinfo stud_all[INFO_COUNT], size_t *const size)
{
    int is_end = FALSE;
    size_t q = 0;
    
    while (!is_end)
    {
        //printf("sur %lu: %s\n", q, stud_all[q].surname);
        null_strings(&stud_all[q]);

        if ((!is_end) && (fgets(stud_all[q].surname, SURNAME_LEN, f) == NULL))
            return ERR_DATA;

        while ((!is_end) && (stud_all[q].surname[0] == '\n'))
        {
            if ((fgets(stud_all[q].surname, SURNAME_LEN, f) == NULL) && (!feof(f)))
                return ERR_DATA;
            else if (feof(f))
                is_end = TRUE;
        }

        if ((!is_end) && (fgets(stud_all[q].name, NAME_LEN, f) == NULL))
            return ERR_DATA;

        while ((!is_end) && (stud_all[q].name[0] == '\n'))
        {
            if ((fgets(stud_all[q].name, NAME_LEN, f) == NULL) && (!feof(f)))
                return ERR_DATA;
            else if (feof(f))
                is_end = TRUE;
        }

        //printf("name %lu: %s\n", q, stud_all[q].name);

        for (size_t i = 0; (!is_end) && (i < MARKS_COUNT); i++)
            if (fscanf(f, "%u", &stud_all[q].marks[i]) < 0)
                return ERR_DATA; 

        if (!is_end)
            q++;
    }

    if (!is_end)
        return ERR_DATA;

    *size = q;

    if (*size == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}
