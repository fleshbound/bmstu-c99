#ifndef __PROCESS_H__

#define __PROCESS_H__

#define MIN 0
#define MAX 1
#define READ_INT 1

typedef int (*cmpf_ptr_t) (const void *, const void *);

int fsort_file(char *const name_in, char *const name_out, const int fcode);

int cmp_int(const void *a, const void *b);

void mysort(void *pbeg, size_t count, size_t t_size, cmpf_ptr_t cmp);

int key(const int *pb_src, const int *pe_src, int **pb_dest, int **pe_dest);

#endif // #define __PROCESS_H__
