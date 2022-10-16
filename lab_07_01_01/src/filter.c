#include "../inc/filter.h"
#include "../inc/errors.h"

#define SWAP(t, a, b) do{ t _c = a; a = b; b = _c; }while(0)

// find pointer to min or max element
int *get_special_ptr(const int *pbeg, const int *pend, const int code)
{
    if ((pbeg == NULL) || (pend == NULL) || (pbeg >= pend))
        return NULL;

    int *pi = (int *) pbeg, *pspec = (int *) pbeg;

    while (pi < pend)
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
        || (pb_src >= pe_src))
        return ERR_DATA;

    // get ptrs of min and max
    int *new_beg = get_special_ptr(pb_src, pe_src, MIN);
    int *new_end = get_special_ptr(pb_src, pe_src, MAX);

    if ((new_beg == NULL) || (new_end == NULL) || (new_beg == new_end))
        return ERR_MEM;

    // if max appears earlier than min
    if (new_beg > new_end)
        SWAP(int *, new_beg, new_end);

    // limits are not included
    new_beg++;

    if (new_beg == new_end)
        return ERR_DATA;

    int *pi = new_beg;
    size_t count = 0;

    // get count of special elements
    while (pi <= new_end)
    {
        count++;
        pi++;
    }

    if (count <= 0)
        return ERR_EMPTY;

    // allocate new array
    //printf("%lu", count * sizeof(int));
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
