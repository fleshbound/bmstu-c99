#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define READ_COUNT 1

int finput_size(FILE *const f, size_t *const size);
int finput_nonneg(FILE *const f, int *const numb);
int finput_matrix(FILE *const f, my_matrix_t matrix);
int input_matrix(my_matrix_t matrix);
int input_nonneg(int *const numb);
int input_size(size_t *const size);
void foutput_matrix(FILE *const f, my_matrix_t matrix);
int input_power(int *const power);
void output_matrix(my_matrix_t matrix);

#endif
