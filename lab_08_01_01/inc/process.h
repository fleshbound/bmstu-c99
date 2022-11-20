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
int get_matrix(int ***matrix, size_t *const rows, size_t *const cols);
int multiply_powers(const size_t size, int **matrix_A, int **matrix_B, int ***res_matrix);
int make_sizes_equal(int ***matrix_A, int ***matrix_B, size_t *const size_A, size_t *const size_B);
int frestrict_matrix(int **matrix, size_t *const rows, size_t *const cols);

#endif
