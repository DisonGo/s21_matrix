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
int is_eq_d(double a, double b, long double precision);
int is_eq_mat_size(matrix_t* a, matrix_t* b);
int is_null_mat(matrix_t* a);
int is_incorrect_mat(matrix_t* a);
int is_bad_size_mat(matrix_t* a);
double determinant_2x2(matrix_t* A);
#endif  // UTILITY_H
