#include "s21_matrix.h"
/**
 * @brief Multiplicate matrices.
 *
 * @param A First matrix.
 * @param B Second matrix.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_incorrect_mat(A) || is_incorrect_mat(B)) return 1;
  if (!((A->rows == B->columns) && (A->columns == B->rows))) return 2;
  int rows = A->rows;
  int cols = B->columns;
  int k_max = A->columns;
  int error = 0;
  if (s21_create_matrix(rows, cols, result)) return 1;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      double value = 0;
      for (int k = 0; k < k_max; k++)
        value += A->matrix[row][k] * B->matrix[k][col];
      if (isinf(fabs(value)) || isnan(fabs(value))) error = 2;
      if (!error) result->matrix[row][col] = value;
    }
  return error;
}
