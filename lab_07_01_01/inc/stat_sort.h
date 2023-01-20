#ifndef __SORT_H__

#define __SORT_H__

#include <stdio.h>
#include <stdlib.h>

typedef int (*cmpf_ptr_t)(const void *, const void *);

int cmp_int(const void *a, const void *b);

void mysort(void *pbeg, size_t count, size_t t_size, cmpf_ptr_t cmp);

#endif // __SORT_H__
