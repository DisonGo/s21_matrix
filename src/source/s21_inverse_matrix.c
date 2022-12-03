#include "s21_matrix.h"
/**
 * @brief Calculate inverse matrix.
 * 
 * @param A Source matrix.
 * @param result Output matrix.
 * @return Success of function.
 * @retval 0 - OK.
 * @retval 1 - Memory, incorrect matrix errors.
 * @retval 2 - Wrong size.
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_null_mat(A) || !is_null_mat(result)) return 1;
  if (A->rows != A->columns) return 2;
  matrix_t M = {0};
  matrix_t MT = {0};
  double deter = 0;
  int error = 0;
  s21_determinant(A, &deter);
  if (deter) {
    error = s21_calc_complements(A, &M);
    if (!error) {
      error = s21_transpose(&M, &MT);
      if (!error) {
        error = s21_mult_number(&MT, (1.0 / deter), result);
        s21_remove_matrix(&MT);
      }
      s21_remove_matrix(&M);
    }
  }
  return error;
}
