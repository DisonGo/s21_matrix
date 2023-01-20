#include "s21_matrix.h"
/**
 * @brief Multiply matrix by number.
 *
 * @param A Matrix.
 * @param number Multiplication number.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_incorrect_mat(A)) return 1;
  int rows = A->rows, cols = A->columns;
  int error = 0;
  if (s21_create_matrix(rows, cols, result)) return 1;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      double mult = A->matrix[row][col] * number;
      if (isinf(fabs(mult)) || isnan(fabs(mult))) error = 2;
      if (!error) result->matrix[row][col] = mult;
    }
  return error;
}
