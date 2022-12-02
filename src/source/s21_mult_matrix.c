#include "s21_matrix.h"
//TODO Implement mult_matrix
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) { 
  if (is_null_mat(A) || is_null_mat(B)) return 1;
  if (!((A->rows == B->columns) || (A->columns == B->rows))) return 2;
  int rows = A->rows;
  int cols = B->columns;
  int k_max = A->columns;
  if (s21_create_matrix(rows, cols, result)) return 1;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++) {
      long double value = 0;
      for (int k = 0; k < k_max; k++)
        value += A->matrix[row][k] * B->matrix[k][col];
      result->matrix[row][col] = value;
    }
  return 0;
}
