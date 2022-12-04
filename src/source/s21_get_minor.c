#include "s21_matrix.h"
void create_sub_matrix(matrix_t* src, int row, int col, int size,
                       matrix_t* result);
// TODO Documentation
double get_minor(matrix_t* src, int row, int col) {
  if (is_incorrect_mat(src)) return 0;
  int sub_size = src->rows - 1;
  double res = 0;
  matrix_t sub_matrix = {0};
  create_sub_matrix(src, row, col, sub_size, &sub_matrix);
  if (sub_size == 2)
    res = determinant_2x2(&sub_matrix);
  else
    for (int column = 0; column < sub_size; column++) {
      int sign = (column % 2 == 0) ? 1 : -1;
      double value = sub_matrix.matrix[0][column];
      res += sign * value * get_minor(&sub_matrix, 0, column);
    }
  s21_remove_matrix(&sub_matrix);
  return res;
}
void create_sub_matrix(matrix_t* src, int row, int col, int size,
                       matrix_t* result) {
  if (s21_create_matrix(size, size, result)) return;
  for (int r = 0, res_r = 0; r <= size; r++) {
    if (r == row) continue;
    for (int c = 0, res_c = 0; c <= size; c++) {
      if (c == col) continue;
      result->matrix[res_r][res_c] = src->matrix[r][c];
      res_c++;
    }
    res_r++;
  }
}
