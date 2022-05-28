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
int put_stud(FILE *const f_in, studinfo *const stud)
{
    if (fprintf(f_in, "%s\n", stud->surname) < 0)
        return ERR_WRITE;

    if (fprintf(f_in, "%s\n", stud->name) < 0)
        return ERR_WRITE;

    for (size_t i = 0; i < MARKS_COUNT; i++)
        if (fprintf(f_in, "%u%s", stud->marks[i], (i == MARKS_COUNT - 1) ? "\n" : " ") < 0)
            return ERR_WRITE;

    return EXIT_SUCCESS;
}

// Записать данные всех студентов списка
int put_stud_all(FILE *const f_in, studinfo *const stud_all, const size_t stud_count)
{
    rewind(f_in);

    for (size_t i = 0; i < stud_count; i++)
    {
        int err_code = put_stud(f_in, &stud_all[i]);

        if (err_code)
            return err_code;
    }

    return EXIT_SUCCESS;
}

// Получить средний балл студента
double get_avg(studinfo *const stud)
{
    double sum = 0.;
    
    for (size_t i = 0; i < MARKS_COUNT; i++)
        sum += stud->marks[i];
    
    return sum / MARKS_COUNT;
}

// Записать данные студентов, чей средний балл выше, чем средний балл файла
int put_stud_delete(FILE *const f_in, studinfo *const stud_all, const size_t stud_count, const double avg)
{
    rewind(f_in);

    printf("%f\n", avg);
    
    for (size_t i = 0; i < stud_count; i++)
    {
        // printf("%f\n", get_avg(&stud_all[i]));
        
        if (get_avg(&stud_all[i]) >= avg)
        {
            
            int err_code = put_stud(f_in, &stud_all[i]);

            if (err_code)
                return err_code;
        }
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

// Получить данные об одном студенте
int get_stud_pack(FILE *const f_in, studinfo *const stud, size_t *const count)
{
    null_strings(stud);

    if (fgets(stud->surname, SURNAME_LEN, f_in) == NULL)
        return ERR_READ;
    
    // Если мы считали переход на новую строку
    // после строки с оценками
    if (stud->surname[0] == '\n') 
    {
        // Если мы не смогли считать строку и это конец файла
        if (fgets(stud->surname, SURNAME_LEN, f_in) == NULL)
        {
            if (feof(f_in))
                return EXIT_SUCCESS;
        }
        // Если мы смогли считать строку и это пустая строка
        else if (stud->surname[0] == '\n')
            return ERR_READ;
    }
    // Итог: пустая строка допускается только в конце файла

    stud->surname[strlen(stud->surname) - 1] = '\0';

    if (fgets(stud->name, NAME_LEN, f_in) == NULL)
        return ERR_READ;

    stud->name[strlen(stud->name) - 1] = '\0';

    for (size_t i = 0; i < MARKS_COUNT; i++)
        if (fscanf(f_in, "%u", &stud->marks[i]) != READ_COUNT)
            return ERR_READ;

    *count = *count + 1;

    return EXIT_SUCCESS;
}

// Получить данные о студенте, игнорируя пустые строки
int get_stud(FILE *const f_in, studinfo *const stud, size_t *const count)
{
    null_strings(stud);

    if (fgets(stud->surname, SURNAME_LEN, f_in) == NULL)
        return ERR_READ;
    
    while (stud->surname[0] == '\n') 
        if (fgets(stud->surname, SURNAME_LEN, f_in) == NULL)
        {
            if (feof(f_in))
                return EXIT_SUCCESS;
        }

    stud->surname[strlen(stud->surname) - 1] = '\0';

    if (fgets(stud->name, NAME_LEN, f_in) == NULL)
        return ERR_READ;

    while (stud->name[0] == '\n') 
        if (fgets(stud->name, NAME_LEN, f_in) == NULL)
            return ERR_READ;

    stud->name[strlen(stud->name) - 1] = '\0';

    for (size_t i = 0; i < MARKS_COUNT; i++)
        if (fscanf(f_in, "%u", &stud->marks[i]) != READ_COUNT)
            return ERR_READ;

    *count = *count + 1;

    return EXIT_SUCCESS;
}



// Считать данные о всех студентах
int get_stud_all(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count)
{
    rewind(f_in);

    int err_code = EXIT_SUCCESS;
    size_t i = 0;

    while (!feof(f_in))
    {
        err_code = get_stud(f_in, &stud_all[i], &i);

        if (err_code)
            return err_code;
    }

    *count = i;

    return err_code;
}

// Считать данные о студентах, чьи фамилии начинаются с substr
int get_stud_fprint(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count, char *const substr)
{
    rewind(f_in);

    int err_code = EXIT_SUCCESS;
    size_t i = 0;

    while (!feof(f_in))
    {
        studinfo buf;
        err_code = get_stud(f_in, &buf, &i);
        
        if (buf.surname == strstr(buf.surname, substr))
            stud_all[i - 1] = buf;
        else if (!feof(f_in))
            i--;
        
        if (err_code)
            return err_code;
    }

    *count = i;

    return err_code;
}

// Считать данные о студентах с расчетом среднего
int get_stud_delete(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count, double *const avg)
{
    rewind(f_in);

    int err_code = EXIT_SUCCESS;
    size_t i = 0;
    double curr_sum = 0.;

    while (!feof(f_in))
    {
        err_code = get_stud(f_in, &stud_all[i], &i);

        if ((!feof(f_in)) && (!err_code))
            for (size_t j = 0; j < MARKS_COUNT; j++)
                curr_sum += stud_all[i - 1].marks[j];

        if (err_code)
            return err_code;
    }

    *count = i;
    
    if (i != 0)
        *avg = curr_sum / (i * MARKS_COUNT);

    return err_code;
}
