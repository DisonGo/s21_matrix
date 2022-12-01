#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_
// TODO Write documentation
// TODO Add Unit_tests
#ifndef SUCCESS
#define SUCCESS 1
#endif
#ifndef FAILURE
#define FAILURE 0
#endif
#include <stdio.h>
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#endif  // S21_MATRIX_H_