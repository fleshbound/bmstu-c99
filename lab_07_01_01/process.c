#include <stdlib.h>
#include <stdio.h>

#include "errors.h"
#include "process.h"
#include "argch.h"

#define SWAP(t, a, b) do{ t _c = a; a = b; b = _c; }while(0)

int cmp_int(const void *a, const void *b)
{
    return (*((int *)a) - *((int *)b));
}

// file elements' count
int get_fsize(FILE *const f, size_t *const size)
{
    fseek(f, 0, SEEK_SET);

    int elem = 0;
    size_t count = 1;

    if (fscanf(f, "%d", &elem) != READ_INT)
        return ERR_DATA;

    while (fscanf(f, "%d", &elem) == READ_INT)
        count++;

    *size = count;
    
    return EXIT_SUCCESS;;
}

// fill array with ints from file f
void fill_array(FILE *const f, const int *pbeg, const int *pend)
{
    fseek(f, 0, SEEK_SET);

    int elem = 0, *pi = (int *) pbeg;

    while (pi != pend)
    {
        if (fscanf(f, "%d", &elem) == READ_INT)
            *pi = elem;

        pi++;
    }
}

// bubble sort
void mysort(void *pbeg, size_t count, size_t t_size, cmpf_ptr_t cmp)
{
    int *pj = pbeg;
    
    for (size_t i = 0; (t_size != 0) && (i < count - 1); i++)
    {
        pj = pbeg;

        for (size_t j = 0; j < count - i - 1; j++)
        {
            if ((*cmp) (pj, pj + 1) > 0)
                SWAP(int, *pj, *(pj + 1));

            pj++;
        }
    }
}

// find pointer to min or max element
int *get_special_ptr(const int *pbeg, const int *pend, const int code)
{
    int *pi = (int *) pbeg, *pspec = (int *) pbeg;

    while (pi != pend)
    {
        if ((code == MIN) && (*pi < *pspec))
            pspec = pi;

        if ((code == MAX) && (*pi > *pspec))
            pspec = pi;

        pi++;
    }

    return pspec;
}

// filter func
int key(const int *pb_src, const int *pe_src, int **pb_dest, int **pe_dest)
{
    // if no source found or destination has already filled up
    if ((pb_src == NULL) || (pe_src == NULL) 
        || (*pb_dest != NULL) || (*pe_dest != NULL)
        || (pb_src == pe_src))
        return ERR_DATA;

    // get ptrs of min and max
    int *new_beg = get_special_ptr(pb_src, pe_src, MIN);
    int *new_end = get_special_ptr(pb_src, pe_src, MAX);

    // if max appears earlier than min
    if (new_beg > new_end)
        SWAP(int *, new_beg, new_end);

    // limits are not included
    new_beg++;

    int *pi = new_beg;
    size_t count = 0;

    // get count of special elements
    while (pi != new_end)
    {
        count++;
        pi++;
    }

    if (count == 0)
        return ERR_EMPTY;

    // allocate new array
    int *tmp = malloc(count * sizeof(int));

    if (tmp == NULL)
        return ERR_MEM;

    *pb_dest = tmp;
    pi = new_beg;
    int *pj = *pb_dest;

    // special elements to new array
    while (pi != new_end)
    {
        *pj = *pi;
        pj++;
        pi++;
    }

    *pe_dest = pj;

    return EXIT_SUCCESS;
}

// print array to file f
void fprint_array(FILE *const f, const int *pbeg, const int *pend)
{
    int *pi = (int *) pbeg;

    while (pi != pend)
    {
        fprintf(f, "%d%s", *pi, (pend - pi > 1) ? " " : "\n");
        pi++;
    }
}

// output sorted name_in-file to name_out-file
int fsort_file(char *const name_in, char *const name_out, const int fcode)
{
    FILE *f_in = fopen(name_in, "rt");

    if (f_in == NULL)
        return ERR_PATH;

    size_t size = 0;
    int err_code = get_fsize(f_in, &size); // size
    
    if (err_code)
        return err_code;

    if (size == 0)
        return ERR_EMPTY;

    int *tmp = malloc(size * sizeof(int)); // main array

    if (tmp == NULL)
        return ERR_MEM;

    int *pb_src = tmp, *pe_src = pb_src + size;

    fill_array(f_in, pb_src, pe_src); // filling

    if (fclose(f_in) == EOF)
        return ERR_IO;

    int *pb_dest = NULL, *pe_dest = NULL;

    if (fcode == F_CODE)
    {
        int err_code = key(pb_src, pe_src, &pb_dest, &pe_dest);

        if (err_code)
            return err_code;

        // ???
        mysort(pb_dest, pe_dest - pb_dest, sizeof(int), cmp_int);
    }
    else
        mysort(pb_src, pe_src - pb_src, sizeof(int), cmp_int);

    FILE *f_out = fopen(name_out, "wt");

    if (f_out == NULL)
        return ERR_PATH;

    if (pb_dest != NULL)
    {
        fprint_array(f_out, pb_dest, pe_dest);
        free(pb_dest);
    }
    else
        fprint_array(f_out, pb_src, pe_src);

    if (fclose(f_out) == EOF)
        return ERR_IO;

    free(pb_src);

    return EXIT_SUCCESS;
}
