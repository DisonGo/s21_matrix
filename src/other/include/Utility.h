#ifndef UTILITY_H
#define UTILITY_H
#include <math.h>
#include "s21_matrix.h"
int max_i(int a, int b);
int min_i(int a, int b);
double max_d(double a, double b);
double min_d(double a, double b);
long double max_ld(long double a, long double b);
long double min_ld(long double a, long double b);
int is_eq_ld(long double a, long double b, long double precision);
int is_eq_mat_size(matrix_t *a, matrix_t *b);
#endif  // UTILITY_H
