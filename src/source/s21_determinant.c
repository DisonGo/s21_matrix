#include "s21_matrix.h"
/**
 * @brief Calculate determinant of matrix.
 * 
 * @param A Input matrix.
 * @param result Output value.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_determinant(matrix_t *A, double *result) {
  if (is_null_mat(A)) return 1;
  if (A->columns != A->rows) return 2;
  int size = A->rows;
  if (size == 2) *result = determinant_2x2(A);
  if (size != 2) {
    for (int col = 0; col < size; col++) {
      long double cur_number = A->matrix[0][col];
      int sign = (col % 2 == 0) ? 1 : -1;
      *result += cur_number ? sign * cur_number * get_minor(A, 0, col) : 0;
    }
  }
  return 0;
}
