#include "s21_matrix.h"
#include <stdlib.h>
/**
 * @brief Create matrix of given size.
 * 
 * @param rows Rows count.
 * @param columns Columns count.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) { 
  if (!result) return 1;
  if (rows <= 0 || columns <= 0) return 2;
  double** matrix = calloc(rows, sizeof(double*)); 
  if (!matrix) return 1;
  for (int i = 0; i < rows; i++) {
    matrix[i] = calloc(columns, sizeof(double));
    if (!matrix[i]) return 1;
  }
  result->matrix = matrix;
  result->columns = columns;
  result->rows = rows;
  return 0;
}
