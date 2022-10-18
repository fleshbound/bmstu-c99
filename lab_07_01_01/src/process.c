#include <stdlib.h>
#include <stdio.h>

#include "../inc/errors.h"
#include "../inc/process.h"
#include "../inc/argch.h"
#include "../inc/filter.h"
#include "../inc/sort.h"

/* Get count of integers in file */
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

    if (*size == 0)
        return ERR_EMPTY;

    return EXIT_SUCCESS;
}

/* Fill array with integers from file */
int fill_array(FILE *const f, const int *pbeg, const int *pend)
{
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

/* Get filtered array with key func */
int get_filtered_array(const int *pb_src, const int *pe_src, int **pb_dest, int **pe_dest)
{
    return key(pb_src, pe_src, pb_dest, pe_dest);
}

/* Print array to file */
void fprint_array(FILE *const f, const int *pbeg, const int *pend)
{
    int *pi = (int *) pbeg;

    while (pi < pend)
    {
        fprintf(f, "%d%s", *pi, (pend - pi > 1) ? " " : "\n");
        pi++;
    }
}

/* Sort old array or make and sort new filtered array */
int fsort_array(int *pb_src, int *pe_src, int **pb_dest, int **pe_dest, const int code)
{
    int err_code = EXIT_SUCCESS;

    if (code == F_CODE)
    {
        err_code = get_filtered_array(pb_src, pe_src, pb_dest, pe_dest);

        if (err_code)
            return err_code;

        mysort(*pb_dest, *pe_dest - *pb_dest, sizeof(int), cmp_int);
    }
    else
        mysort(pb_src, pe_src - pb_src, sizeof(int), cmp_int);

    return err_code;
}

void free_all_data(int *data1, int *data2)
{
    if (data1 != NULL)
        free(data1);

    if (data2 != NULL)
        free(data2);
}

// output sorted name_in-file to name_out-file
int fsort_file(char *const name_in, char *const name_out, const int fcode)
{
    FILE *f_in = fopen(name_in, "rt");

    if (f_in == NULL)
        return ERR_PATH;

    /* Size */
    size_t size = 0;
    int err_code = get_fsize(f_in, &size);

    if (err_code)
    {
        fclose(f_in);
        return err_code;
    }

    /* Main array */
    int *pb_src = malloc(size * sizeof(int));

    if (pb_src == NULL)
    {
        fclose(f_in);
        return ERR_MEM;
    }

    int *pe_src = pb_src + size, *pb_dest = NULL, *pe_dest = NULL;
    err_code = fill_array(f_in, pb_src, pe_src);

    if (err_code)
    {
        fclose(f_in);
        free_all_data(pb_src, NULL);
        return err_code;
    }

    if (fclose(f_in) == EOF)
    {
        free_all_data(pb_src, NULL);
        return ERR_IO;
    }

    /* Array sorting according to fcode */    
    err_code = fsort_array(pb_src, pe_src, &pb_dest, &pe_dest, fcode);

    if (err_code)
    {
        free_all_data(pb_src, pe_src);
        return err_code;
    }

    /* Writing result array to file */
    FILE *f_out = fopen(name_out, "wt");   

    if (f_out == NULL)
    {
        free_all_data(pb_src, pb_dest);
        return ERR_IO;
    }
    
    if (fcode == F_CODE)
        fprint_array(f_out, pb_dest, pe_dest);
    else
        fprint_array(f_out, pb_src, pe_src);

    free_all_data(pb_src, pb_dest);

    if (fclose(f_out) == EOF)
        return ERR_IO;

    return EXIT_SUCCESS;
}
