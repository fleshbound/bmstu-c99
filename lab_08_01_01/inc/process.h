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

int restrict_matrix(int **matrix, size_t *const rows, size_t *const cols);
int expand_matrix(int ***matrix, size_t *const size, const size_t new_size);
int get_matrix(int ***matrix, size_t *const rows, size_t *const cols);

#endif
