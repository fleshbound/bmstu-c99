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
        if (fprintf(f, "%u\n", stud.marks[i]) < 0)
            return ERR_WRITE;

    return EXIT_SUCCESS;
}

// Записать данные всех студентов списка
int put_stud_all(FILE *const f, studinfo *const stud_all, const size_t stud_count)
{
    rewind(f);

    for (size_t i = 0; i < stud_count; i++)
    {
        int err_code = put_stud(f, stud_all[i]);

        if (err_code)
            return err_code;
    }

    return EXIT_SUCCESS;
}

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

// Записать данные студентов, чей средний балл выше, чем средний балл файла
int put_stud_delete(FILE *const f, studinfo stud_all[INFO_COUNT], const size_t stud_count)
{
    if (f == NULL)
        return ERR_IO;

    rewind(f);
    
    double avg = get_avg_all(stud_all, stud_count);
    
    for (size_t i = 0; i < stud_count; i++)
    {
<<<<<<< HEAD
        //printf("(%lu) avg: %f, curr avg: %f", i, avg, get_avg(stud_all[i]));

        if (get_avg(stud_all[i]) >= avg)
=======
        // printf("%f\n", get_avg(&stud_all[i]));
        
        if (get_avg(&stud_all[i]) >= avg)
>>>>>>> 9a8149f9a740b2a6d4c514c60eab0118f95306cb
        {
            
            int err_code = put_stud(f, stud_all[i]);

            if (err_code)
                return err_code;
        }
    }

    return EXIT_SUCCESS;
}

// Записать данные, начинающиеся с substr
int put_stud_fprint(FILE *const f, studinfo *const stud_all, const size_t stud_count, char *const substr)
{
    if (f == NULL)
        return ERR_IO;

    rewind(f);

    for (size_t i = 0; i < stud_count; i++)
         if (strstr(stud_all[i].surname, substr) == stud_all[i].surname)
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

<<<<<<< HEAD
// Считать данные о всех студентах
int get_stud_all(FILE *const f, studinfo stud_all[INFO_COUNT], size_t *const count)
=======
// Получить данные об одном студенте
int get_stud_pack(FILE *const f_in, studinfo *const stud, size_t *const count)
>>>>>>> 9a8149f9a740b2a6d4c514c60eab0118f95306cb
{
    if (f == NULL)
       return ERR_IO;

    rewind(f);
    int readc, is_end = FALSE;
    size_t q = 0;
    null_strings(&stud_all[q]);
    
    while ((!is_end) && (fgets(stud_all[q].surname, SURNAME_LEN, f) != NULL))
    {
        //printf("sur %lu: %s\n", q, stud_all[q].surname);

        while ((!is_end) && (stud_all[q].surname[0] == '\n'))
        {
            if ((fgets(stud_all[q].surname, SURNAME_LEN, f) == NULL) && (!feof(f)))
                return ERR_DATA;
            else if (feof(f))
                is_end = TRUE;
        }
<<<<<<< HEAD
=======
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
>>>>>>> 9a8149f9a740b2a6d4c514c60eab0118f95306cb

        //printf("sur %lu: %s\n", q, stud_all[q].surname);

<<<<<<< HEAD
        if ((!is_end) && (fgets(stud_all[q].name, NAME_LEN, f) == NULL))
            return ERR_DATA;
=======
    while (stud->name[0] == '\n') 
        if (fgets(stud->name, NAME_LEN, f_in) == NULL)
            return ERR_READ;

    stud->name[strlen(stud->name) - 1] = '\0';
>>>>>>> 9a8149f9a740b2a6d4c514c60eab0118f95306cb

        while ((!is_end) && (stud_all[q].name[0] == '\n'))
        {
            if ((fgets(stud_all[q].name, NAME_LEN, f) == NULL) && (!feof(f)))
                return ERR_DATA;
            else if (feof(f))
                is_end = TRUE;
        }

        //printf("name %lu: %s\n", q, stud_all[q].name);

<<<<<<< HEAD
        for (size_t i = 0; (!is_end) && (i < MARKS_COUNT); i++)
        {
            readc = fscanf(f, "%u", &stud_all[q].marks[i]);
            //printf("mark %lu [%lu]: %u\n", q, i, stud_all[q].marks[i]);
=======
    return EXIT_SUCCESS;
}



// Считать данные о всех студентах
int get_stud_all(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count)
{
    rewind(f_in);

    int err_code = EXIT_SUCCESS;
    size_t i = 0;
>>>>>>> 9a8149f9a740b2a6d4c514c60eab0118f95306cb

            if (readc != READ_COUNT)
                return ERR_DATA;
        }

        if (!is_end)
            q++;
    }

    if (!is_end)
        return ERR_DATA;

    *count = q;

    if (*count == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}

