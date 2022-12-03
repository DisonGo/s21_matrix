#include "s21_matrix.h"
/**
 * @brief Determine if matrices are equal.
 * 
 * @param A First matrix.
 * @param B Second matrix.
 * @return Bool - Are matrices equal.
 * @retval int
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) { 
  if (!A || !B) return 0;
  if (!is_eq_mat_size(A, B)) return 0;
  int x = A->columns, y = A->rows;
  int res = SUCCESS;
  for (int i = 0; i < y; i++)
    for (int j = 0; j < x; j++)
      if (!is_eq_ld(A->matrix[i][j], B->matrix[i][j], 1E-7)) res = FAILURE;
  return res;
}
