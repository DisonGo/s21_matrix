#include "s21_matrix.h"
/**
 * @brief Summarize matrices.
 * 
 * @param A First matrix.
 * @param B Second matrix.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) { 
  if (is_null_mat(A) || is_null_mat(B)) return 1;
  if (!is_eq_mat_size(A, B)) return 2;
  int rows = A->rows, cols = A->columns;
  if (s21_create_matrix(rows, cols, result)) return 1;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      long double sum = A->matrix[row][col] + B->matrix[row][col];
      result->matrix[row][col] = sum;
    }
  return 0;
}
