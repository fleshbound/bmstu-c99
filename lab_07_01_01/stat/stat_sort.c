#include "../inc/stat_sort.h"

#define SWAPMEM(a, b, size) \
    do  \
    {   \
        size_t __size = (size); \
        char *__a = (a), *__b = (b); \
        do  \
	    {	\
	        char __tmp = *__a; \
	        *__a++ = *__b; \
	        *__b++ = __tmp; \
	    } while (--__size > 0);	\
    } while (0)

int cmp_int(const void *a, const void *b)
{
    return (*((int *)a) - *((int *)b));
}

// bubble sort
void mysort(void *pbeg, size_t count, size_t t_size, cmpf_ptr_t cmp)
{
    if ((count == 0) || (pbeg == NULL) || (t_size == 0))
        return;

    char *begin = (char *) pbeg;

    for (size_t i = 0; i < count - 1; i++)
        for (size_t j = 0; j < count - 1 - i; j++)
            if (cmp(begin + j * t_size, begin + (j + 1) * t_size) > 0)
                SWAPMEM(begin + j * t_size, begin + (j + 1) * t_size, t_size);
}
