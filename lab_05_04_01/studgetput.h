#ifndef __STUDGETPUT_H__
  
#define __STUDGETPUT_H__

#define INFO_COUNT 50
#define SURNAME_LEN 26
#define NAME_LEN 11
#define MARKS_COUNT 4

typedef struct stud
{
    char surname[SURNAME_LEN];
    char name[NAME_LEN];
    uint32_t marks[MARKS_COUNT];
} studinfo;

int put_stud_all(FILE *const f_in, studinfo *const stud_all, const size_t stud_count);

int get_stud_all(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count);

int get_stud_fprint(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count, char *const substr);

int put_stud_delete(FILE *const f_in, studinfo *const stud_all, const size_t stud_count, const double avg);

int get_stud_delete(FILE *const f_in, studinfo stud_all[INFO_COUNT], size_t *const count, double *const avg);

#endif // #ifndef __STUDGETPUT_H__
