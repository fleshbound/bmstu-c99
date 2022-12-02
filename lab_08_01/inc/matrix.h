#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int **allocate_matrix(const size_t rows, const size_t cols);
void free_matrix(int **matrix, const size_t rows);

void multiply_matrices(const size_t size, int **matrix1, int **matrix2, int **res_matrix);
int power_matrix(const size_t size, int **matrix, int **res_matrix, const int power);

int add_col_to_matrix(int **matrix, int *new_col, const size_t rows, size_t *const cols);
int add_row_to_matrix(int ***matrix, int *new_row, size_t *const rows, const size_t cols);

int delete_matrix_col(int **matrix, const size_t rows, size_t *const cols, const size_t col_ind);
void delete_matrix_row(int **matrix, size_t *const rows, const size_t row_ind);

void null_matrix(int **matrix, const size_t rows, const size_t cols);
void copy_matrix(int **dest, int **src, const size_t rows, const size_t cols);

#endif
