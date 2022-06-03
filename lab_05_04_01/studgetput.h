#ifndef __STUDGETPUT_H__
  
#define __STUDGETPUT_H__

#define INFO_COUNT 50
#define SURNAME_LEN 26
#define NAME_LEN 11
#define MARKS_COUNT 4

#ifndef __TRUEFALSE__
#define TRUE 1
#define FALSE 0
#endif

typedef struct stud
{
    char surname[SURNAME_LEN];
    char name[NAME_LEN];
    uint32_t marks[MARKS_COUNT];
} studinfo;

int get_stud_all(FILE *const f, studinfo stud_all[INFO_COUNT], size_t *const count);

int put_stud_all(FILE *const f, studinfo *const stud_all, const size_t stud_count);

int put_stud(FILE *const f, studinfo stud);

#endif // #ifndef __STUDGETPUT_H__
