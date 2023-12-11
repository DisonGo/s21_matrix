#include <math.h>

#include "s21_matrix.h"

/**
 * @brief Calculate matrix cofactor matrix.
 *
 * @param A Source matrix.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_incorrect_mat(A) || !is_incorrect_mat(result)) return 1;
  if (A->rows != A->columns) return 2;
  if (s21_create_matrix(A->rows, A->columns, result)) return 1;
  if (A->rows == 2) {
    result->matrix[0][0] = A->matrix[1][1];
    result->matrix[0][1] = -A->matrix[1][0];
    result->matrix[1][0] = -A->matrix[0][1];
    result->matrix[1][1] = A->matrix[0][0];
  } else {
    int stop = 0;
    for (int i = 0; i < result->rows && !stop; i++) {
      for (int j = 0; j < result->columns && !stop; j++) {
        double temp = s21_get_minor(A, i, j);
        if (!isinf(fabs(temp)) && !isnan(fabs(temp))) {
          result->matrix[i][j] = temp * pow(-1, i + j);
        }
      }
    }
  }
  return 0;
}
