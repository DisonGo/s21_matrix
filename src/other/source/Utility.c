#include "Utility.h"

int max_i(int a, int b) {return a > b ? a : b;}
int min_i(int a, int b) {return a < b ? a : b;}

double max_d(double a, double b) {return a > b ? a : b;}
double min_d(double a, double b) {return a < b ? a : b;}

long double max_ld(long double a, long double b) {return a > b ? a : b;}
long double min_ld(long double a, long double b) {return a < b ? a : b;}

int is_eq_ld(long double a, long double b, long double precision) {
    a = (long double)(float) a;
    b = (long double)(float) b;
    long double diff = fabs(fabs(a) - fabs(b));
    return (diff <= precision);
}

int is_eq_mat_size(matrix_t *a, matrix_t *b) {
    return (a->columns == b->columns && a->rows == b->rows);
}
int is_null_mat(matrix_t *a) {
    return (!a || !a->matrix);
}
double determinant_2x2(matrix_t* A) {
  double first = A->matrix[0][0] * A->matrix[1][1];
  double second = A->matrix[0][1] * A->matrix[1][0];
  return first - second;
}