#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_matrix
{
    size_t rows;
    size_t cols;
    int **data;
} my_matrix_t;

my_matrix_t allocate_matrix(const size_t rows, const size_t cols);
void free_matrix(my_matrix_t matrix);

void multiply_matrices(my_matrix_t matrix1, my_matrix_t matrix2, my_matrix_t res_matrix);
int power_matrix(my_matrix_t matrix, my_matrix_t res_matrix, const int power);

int add_row_to_matrix(my_matrix_t *matrix, int *new_row);
int add_col_to_matrix(my_matrix_t *matrix, int *new_col);

void delete_matrix_row(my_matrix_t *matrix, const size_t row_ind);
int delete_matrix_col(my_matrix_t *matrix, const size_t col_ind);

void null_matrix(my_matrix_t matrix);
void copy_matrix(my_matrix_t dest, my_matrix_t src);
my_matrix_t init_matrix(void);

#endif
