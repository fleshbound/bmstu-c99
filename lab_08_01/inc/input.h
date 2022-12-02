#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

#define READ_COUNT 1
#define MAX_SIZE 1000000

int finput_size(FILE *const f, size_t *const size);
int finput_nonneg(FILE *const f, size_t *const numb);
int finput_matrix(FILE *const f, int **matrix, const size_t rows, const size_t cols);
int input_matrix(int **matrix, const size_t rows, const size_t cols);
int input_nonneg(size_t *const numb);
int input_size(size_t *const size);
void foutput_matrix(FILE *const f, int **matrix, const size_t rows, const size_t cols);
void output_matrix(int **matrix, const size_t rows, const size_t cols);

#endif
