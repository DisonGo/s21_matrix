#include "s21_matrix.h"
// TODO Add Infinity / nan checks for value.
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
  if (is_null_mat(A)) return 1;
  int rows = A->rows, cols = A->columns;
  if (s21_create_matrix(rows, cols, result)) return 1;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      long double mult = A->matrix[row][col] * number;
      result->matrix[row][col] = mult;
    }
  return 0;
}
