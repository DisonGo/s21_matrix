#include <stdio.h>

#include "s21_matrix.h"
/**
 * @brief Copy matrix to new empty matrix.
 *
 * @param source Source matrix.
 * @param copy Output matrix.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 */
int s21_copy_matrix(matrix_t* source, matrix_t* copy) {
  if (is_incorrect_mat(source) || !is_incorrect_mat(copy)) return 1;
  if (s21_create_matrix(source->rows, source->columns, copy)) return 1;
  for (int row = 0; row < source->rows; row++)
    for (int col = 0; col < source->columns; col++)
      copy->matrix[row][col] = source->matrix[row][col];
  return 0;
}
