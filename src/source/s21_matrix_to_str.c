#include <stdlib.h>

#include "s21_matrix.h"
#include "string.h"

/**
 * @brief Creates table of matrix in str with given precision.
 *
 * @param A Source matrix.
 * @param precision Presicion of values. (0 = no mantissa).
 * @return New str with parsed matrix.
 * @retval char* - New str.
 * @retval NULL - Memory error.
 */
char *s21_matrix_to_str(matrix_t *A, int precision) {
  int row_size = 1024;
  int width = precision + 3;
  int length = precision;
  int dot = 1;
  char *str = calloc(A->rows * row_size + 1, sizeof(char));
  if (!str) return NULL;
  for (int y = 0; y < A->rows; y++) {
    char tmp[1024] = {0};
    for (int x = 0; x < A->columns; x++) {
      int next_not_end = (x + 1 < A->columns);
      sprintf(tmp, "% *.*lf", width, length, A->matrix[y][x]);
      if (next_not_end) strncat(tmp, " ", 1);
      strncat(str, tmp, width + dot + next_not_end);
    }
    if (y + 1 < A->rows) strncat(str, "\n", 1);
  }
  return str;
}