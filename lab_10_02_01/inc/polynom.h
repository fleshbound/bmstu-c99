#ifndef _POLYNOM_H_
#define _POLYNOM_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

#define END_CODE 100

typedef struct polynom_data
{
    int coef;
    int power;
} poly_data_t;

int input_arg_polynom(list_t *polynom, int *const arg);
void print_poly_data(void *data);
void print_polynom(list_t polynom);
void free_polynom(list_t *polynom);
int calc_polynom(list_t polynom, const int arg);
int input_polynom(list_t *polynom);
list_t get_ddx_polynom(list_t polynom);
void free_poly_data(void *data);
list_t sum_polynoms(list_t *polynom_a, list_t *polynom_b);
void get_odd_even_poly(list_t polynom, list_t *even, list_t *odd);

#endif
