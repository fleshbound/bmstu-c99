#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "../inc/stat_sort.h"

#ifndef N_MAX
#define N_MAX 1
#error No N_MAX was defined
#endif

#ifndef CODE
#define CODE 1
#error No CODE was defined
#endif

#ifndef MYSORT_CODE
#define MYSORT_CODE 1
#error No MYSORT_CODE was defined
#endif

#define SORTED 1
#define REVERSED -1
#define RANDOM 0
#define TRUE 1
#define FALSE 0

int array[N_MAX];

void fill_array(const int code)
{
    if (code == SORTED)
        for (size_t i = 0; i < N_MAX; i++)
            array[i] = i;

    if (code == REVERSED)
        for (size_t i = 0; i < N_MAX; i++)
            array[i] = N_MAX - i;

    if (code == RANDOM)
        for (size_t i = 0; i < N_MAX; i++)
            array[i] = rand();
}

void print_sort_time(const int is_last)
{
    clock_t begin, end;
    
    if (MYSORT_CODE == TRUE)
    {
        begin = clock();
        mysort(array, N_MAX, sizeof(int), cmp_int);
        end = clock();
    }
    else
    {
        begin = clock();
        qsort(array, N_MAX, sizeof(int), cmp_int);
        end = clock();
    }

    if (N_MAX > 1)
    {
        array[0] = array[1];
        array[1] = 123;
    }
    
    printf("%f%s", (double) (end - begin) / CLOCKS_PER_SEC, (is_last) ? "\n" : " ");
}

int main(void)
{
    srand(time(NULL));

    fill_array(CODE);
    print_sort_time(TRUE);

    return EXIT_SUCCESS;
}
