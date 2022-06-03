#ifndef __STUDGETPUT_H__
  
#define __STUDGETPUT_H__

#define INFO_COUNT 50
#define SURNAME_LEN 26
#define NAME_LEN 11
#define MARKS_COUNT 4
#define READ_COUNT 1

#define TRUE 1
#define FALSE 0

typedef struct stud
{
    char surname[SURNAME_LEN];
    char name[NAME_LEN];
    uint32_t marks[MARKS_COUNT];
} studinfo;

int get_students(FILE *const f, studinfo students[INFO_COUNT], size_t *const count);

int put_students(FILE *const f, studinfo *const students, const size_t stud_count);

int put_stud(FILE *const f, studinfo stud);

#endif // #ifndef __STUDGETPUT_H__
