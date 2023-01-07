#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "input.h"
#include "errors.h"

typedef struct elem
{
    size_t row_ind;
    size_t col_ind;
} element_t;

/* int restrict_matrix(int **matrix, size_t *const rows, size_t *const cols); */
/* int expand_matrix(int ***matrix, size_t *const size, const size_t new_size); */
int get_matrix(my_matrix_t *matrix);
int frestrict_matrix(my_matrix_t *matrix);
int make_sizes_equal(my_matrix_t *matrix_a, my_matrix_t *matrix_b);
int multiply_powers(my_matrix_t matrix_a, my_matrix_t matrix_b, my_matrix_t *res_matrix);

#endif
