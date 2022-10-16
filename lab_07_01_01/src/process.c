#include <stdlib.h>
#include <stdio.h>

#include "../inc/errors.h"
#include "../inc/process.h"
#include "../inc/argch.h"
#include "../inc/filter.h"
#include "../inc/sort.h"

// file elements' count
int get_fsize(FILE *const f, size_t *const size)
{
    fseek(f, 0, SEEK_SET);

    int elem = 0;
    size_t count = 0;

    while (fscanf(f, "%d ", &elem) == READ_INT)
        count++;

    fgetc(f);

    if (!feof(f))
        return ERR_DATA;

    *size = count;
    
    return EXIT_SUCCESS;
}

// fill array with ints from file f
int fill_array(FILE *const f, const int *pbeg, const int *pend)
{
    if ((pbeg == NULL) || (pend == NULL) || (pbeg >= pend))
        return ERR_DATA;

    fseek(f, 0, SEEK_SET);

    int elem = 0, *pi = (int *) pbeg;

    while (pi < pend)
    {
        if (fscanf(f, "%d ", &elem) == READ_INT)
            *pi = elem;
        else
            return ERR_IO;

        pi++;
    }

    return EXIT_SUCCESS;
}

// print array to file f
int fprint_array(FILE *const f, const int *pbeg, const int *pend)
{
    if ((pbeg == NULL) || (pend == NULL) || (pbeg == pend))
        return ERR_DATA;

    int *pi = (int *) pbeg;

    while (pi < pend)
    {
        if (fprintf(f, "%d%s", *pi, (pend - pi > 1) ? " " : "\n") < 0)
            return ERR_IO;

        pi++;
    }

    return EXIT_SUCCESS;
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
    {
        fclose(f_in);
        return err_code;
    }

    if (size == 0)
    {
        fclose(f_in);
        return ERR_EMPTY;
    }

    int *tmp = malloc(size * sizeof(int)); // main array

    if (tmp == NULL)
    {
        fclose(f_in);
        return ERR_MEM;
    }

    int *pb_src = tmp, *pe_src = pb_src + size;

    err_code = fill_array(f_in, pb_src, pe_src); // filling
    
    if (err_code)
    {
        fclose(f_in);
        return err_code;
    }

    if (fclose(f_in) == EOF)
        return ERR_IO;

    int *pb_dest = NULL, *pe_dest = NULL;

    if (fcode == F_CODE)
    {
        int err_code = key(pb_src, pe_src, &pb_dest, &pe_dest);

        if (err_code)
            return err_code;

        mysort(pb_dest, pe_dest - pb_dest, sizeof(int), cmp_int);
    }
    else
        mysort(pb_src, pe_src - pb_src, sizeof(int), cmp_int);

    FILE *f_out = fopen(name_out, "wt");

    if (f_out == NULL)
        return ERR_PATH;

    if ((pb_dest != NULL) && (pe_dest != NULL))
    {
        err_code = fprint_array(f_out, pb_dest, pe_dest);
        
        if (err_code)
        {
            fclose(f_out);
            return err_code;
        }

        free(pb_dest);
    }
    else if ((pb_dest == NULL) && (pe_dest == NULL))
    {
        err_code = fprint_array(f_out, pb_src, pe_src);

        if (err_code)
        {
            fclose(f_out);
            return err_code;
        }
    }
    else
    {
        fclose(f_out);
        return ERR_MEM;
    }

    if (fclose(f_out) == EOF)
        return ERR_IO;

    free(pb_src);

    return EXIT_SUCCESS;
}
