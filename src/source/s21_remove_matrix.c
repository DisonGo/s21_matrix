#include "s21_matrix.h"
#include <stdlib.h>
/**
 * @brief Free matrix.
 * 
 * @param A Matrix to free.
 */
void s21_remove_matrix(matrix_t *A) { 
  if (!A) return;
  if (A->matrix) {
    for(int i = 0; i < A->rows; i++)
      free(A->matrix[i]);
    free(A->matrix);
  }
}
