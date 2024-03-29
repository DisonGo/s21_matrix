#include "s21_matrix.h"
/**
 * @brief Substruct matrices.
 *
 * @param A First matrix.
 * @param B Second matrix.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_incorrect_mat(A) || is_incorrect_mat(B)) return 1;
  if (!is_eq_mat_size(A, B)) return 2;
  int rows = A->rows, cols = A->columns;
  int error = 0;
  if (s21_create_matrix(rows, cols, result)) return 1;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      double sub = A->matrix[row][col] - B->matrix[row][col];
      if (isinf(fabs(sub)) || isnan(fabs(sub))) error = 2;
      if (!error) result->matrix[row][col] = sub;
    }
  return error;
}
