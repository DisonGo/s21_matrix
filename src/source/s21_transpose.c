#include "s21_matrix.h"
/**
 * @brief Switch around rows and columns of matrix into new one.
 * 
 * @param A Source matrix.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 */
int s21_transpose(matrix_t *A, matrix_t *result) { 
  if (is_null_mat(A) || !is_null_mat(result)) return 1;
  if (s21_create_matrix(A->columns, A->rows, result)) return 1;
  for (int col = 0; col < A->columns; col++)
    for (int row = 0; row < A->rows; row++)
      result->matrix[col][row] = A->matrix[row][col];
  return 0;
}
