#include "Utility.h"

// int max_i(int a, int b) { return a > b ? a : b; }
// int min_i(int a, int b) { return a < b ? a : b; }

// double max_d(double a, double b) { return a > b ? a : b; }
// double min_d(double a, double b) { return a < b ? a : b; }

// long double max_ld(long double a, long double b) { return a > b ? a : b; }
// long double min_ld(long double a, long double b) { return a < b ? a : b; }

int is_eq_ld(long double a, long double b, long double precision) {
  // a = (long double)(float) a;
  // b = (long double)(float) b;
  long double diff = fabs(a - b);
  return (diff <= precision);
}

int is_eq_mat_size(matrix_t* a, matrix_t* b) {
  return (a->columns == b->columns && a->rows == b->rows);
}
int is_null_mat(matrix_t* a) {
  if (!a || !a->matrix) return 1;
  for (int i = 0; i < a->rows; i++)
    if (!a->matrix[i]) return 1;
  return 0;
}
int is_incorrect_mat(matrix_t* a) {
  if (is_null_mat(a)) return 1;
  if (is_bad_size_mat(a)) return 1;
  return 0;
}
int is_bad_size_mat(matrix_t* a) {
  return (a->rows <= 0 || a->columns <= 0 || (a->rows * a->columns == 1));
}
double determinant_2x2(matrix_t* A) {
  double first = A->matrix[0][0] * A->matrix[1][1];
  double second = A->matrix[0][1] * A->matrix[1][0];
  return first - second;
}