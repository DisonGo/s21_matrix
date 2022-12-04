//
// Created by maslynem on 25.11.22.
//

#include <check.h>
#include <stdlib.h>
#include "s21_matrix.h"

void print_matrix_in_str(matrix_t *A, char *str, int return_result) {
  sprintf(str, "return=%d row=%d, column=%d, values: ", return_result, A->rows,
          A->columns);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      char value[64] = {'\0'};
      if (i + 1 == A->rows && j + 1 == A->columns)
        sprintf(value, "%.7lf", A->matrix[i][j]);
      else
        sprintf(value, "%.7lf ", A->matrix[i][j]);
      strcat(str, value);
    }
  }
}

void set_matrix(matrix_t *A) {
  double count = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = count++;
    }
  }
}

START_TEST(s21_create_matrix_test) {
  int data[3] = {1, 2, 3};
  FILE *fp = fopen("tests/data/s21_create_matrix_data.txt", "r");
  if (fp) {
    for (int k = 0; k < 3; k++) {
      for (int l = 0; l < 3; l++) {
        char matrix_str[1024] = {'\0'};
        char str_original[1024] = {'\0'};
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';
        matrix_t A = {0};
        int return_result = s21_create_matrix(data[k], data[l], &A);
        for (int i = 0; i < A.rows; i++) {
          for (int j = 0; j < A.columns; j++) {
            A.matrix[i][j] = i + j;
          }
        }
        print_matrix_in_str(&A, matrix_str, return_result);
        ck_assert_str_eq(matrix_str, str_original);
        s21_remove_matrix(&A);
      }
    }
  } else {
    fprintf(stderr, "no file\n");
  }
}
END_TEST

Suite *test_suite_s21_create_matrix() {
  Suite *s = suite_create("test_suite_s21_create_matrix");
  TCase *tc = tcase_create("test_suite_s21_create_matrix");
  tcase_add_test(tc, s21_create_matrix_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_create_matrix_test_error) {
  int data[3] = {0, -1, 1};
  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < 3; l++) {
      matrix_t A = {0};
      int return_result = s21_create_matrix(data[k], data[l], &A);
      ck_assert_int_eq(return_result, 2);
    }
  }
}
END_TEST

Suite *test_suite_s21_create_matrix_error() {
  Suite *s = suite_create("test_suite_s21_create_matrix_error");
  TCase *tc = tcase_create("test_suite_s21_create_matrix_error");
  tcase_add_test(tc, s21_create_matrix_test_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_eq_matrix_test) {
  matrix_t matrix[5];
  s21_create_matrix(3, 4, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(3, 2, &matrix[1]);
  matrix[1].matrix[0][0] = 1.123456789;
  matrix[1].matrix[0][1] = 1.123456789;
  matrix[1].matrix[1][0] = 1.123456789;
  matrix[1].matrix[1][1] = 1.123456789;
  matrix[1].matrix[2][0] = 1.123456789;
  matrix[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[2]);
  matrix[2].matrix[0][0] = 1.123456789;
  matrix[2].matrix[0][1] = 1.123456789;
  matrix[2].matrix[1][0] = 1.123456789;
  matrix[2].matrix[1][1] = 1.123456789;
  matrix[2].matrix[2][0] = 1.123456789;
  matrix[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[3]);
  matrix[3].matrix[0][0] = 123456789.123456789;
  matrix[3].matrix[0][1] = 123456789.123456789;
  matrix[3].matrix[1][0] = 123456789.123456789;
  matrix[3].matrix[1][1] = 123456789.123456789;
  matrix[3].matrix[2][0] = 123456789.123456789;
  matrix[3].matrix[2][1] = 123456789.123456789;

  s21_create_matrix(3, 2, &matrix[4]);
  matrix[4].matrix[0][0] = 123456789.123456789;
  matrix[4].matrix[0][1] = 123456789.123456789;
  matrix[4].matrix[1][0] = 123456789.123456789;
  matrix[4].matrix[1][1] = 123456789.123456789;
  matrix[4].matrix[2][0] = 123456789.123456789;
  matrix[4].matrix[2][1] = 123456789.123456789;

  matrix_t matrix_dif[5];
  s21_create_matrix(3, 4, &matrix_dif[0]);
  set_matrix(&matrix_dif[0]);

  s21_create_matrix(3, 2, &matrix_dif[1]);
  matrix_dif[1].matrix[0][0] = 1.123456789;
  matrix_dif[1].matrix[0][1] = 1.123456789;
  matrix_dif[1].matrix[1][0] = 1.123456689;
  matrix_dif[1].matrix[1][1] = 1.123456789;
  matrix_dif[1].matrix[2][0] = 1.123456789;
  matrix_dif[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix_dif[2]);
  matrix_dif[2].matrix[0][0] = 1.123456766;
  matrix_dif[2].matrix[0][1] = 1.123456789;
  matrix_dif[2].matrix[1][0] = 1.123456723;
  matrix_dif[2].matrix[1][1] = 1.123456789;
  matrix_dif[2].matrix[2][0] = 1.123456789;
  matrix_dif[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix_dif[3]);
  matrix_dif[3].matrix[0][0] = 123456789.123456789;
  matrix_dif[3].matrix[0][1] = 123456789.123456789;
  matrix_dif[3].matrix[1][0] = 123456789.123456789;
  matrix_dif[3].matrix[1][1] = 123456789.123456789;
  matrix_dif[3].matrix[2][0] = 123456789.123456789;
  matrix_dif[3].matrix[2][1] = 123456781.123456789;

  s21_create_matrix(3, 2, &matrix_dif[4]);
  matrix_dif[4].matrix[0][0] = 123456789.123456789;
  matrix_dif[4].matrix[0][1] = 123456789.123456789;
  matrix_dif[4].matrix[1][0] = 123456789.123456789;
  matrix_dif[4].matrix[1][1] = 123456789.123456789;
  matrix_dif[4].matrix[2][0] = 123456789.123456789;
  matrix_dif[4].matrix[2][1] = 123456789.123456789;

  for (int k = 0; k < 5; k++) {
    int return_result = s21_eq_matrix(&matrix[k], &matrix_dif[k]);
    if (k % 2 == 0)
      ck_assert_int_eq(return_result, 1);
    else
      ck_assert_int_eq(return_result, 0);
    s21_remove_matrix(&matrix[k]);
    s21_remove_matrix(&matrix_dif[k]);
  }
}
END_TEST

Suite *test_suite_s21_eq_matrix() {
  Suite *s = suite_create("test_suite_s21_eq_matrix");
  TCase *tc = tcase_create("test_suite_s21_eq_matrix");
  tcase_add_test(tc, s21_eq_matrix_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_sum_matrix_test) {
  matrix_t matrix[5];
  s21_create_matrix(3, 4, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(3, 2, &matrix[1]);
  matrix[1].matrix[0][0] = 1.123456789;
  matrix[1].matrix[0][1] = 1.123456789;
  matrix[1].matrix[1][0] = 1.123456789;
  matrix[1].matrix[1][1] = 1.123456789;
  matrix[1].matrix[2][0] = 1.123456789;
  matrix[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[2]);
  matrix[2].matrix[0][0] = 1.123456789;
  matrix[2].matrix[0][1] = 1.123456789;
  matrix[2].matrix[1][0] = 1.123456789;
  matrix[2].matrix[1][1] = 1.123456789;
  matrix[2].matrix[2][0] = 1.123456789;
  matrix[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[3]);
  matrix[3].matrix[0][0] = 123456789.123456789;
  matrix[3].matrix[0][1] = 123456789.123456789;
  matrix[3].matrix[1][0] = 123456789.123456789;
  matrix[3].matrix[1][1] = 123456789.123456789;
  matrix[3].matrix[2][0] = 123456789.123456789;
  matrix[3].matrix[2][1] = 123456789.123456789;

  s21_create_matrix(3, 2, &matrix[4]);
  matrix[4].matrix[0][0] = 123456789.123456789;
  matrix[4].matrix[0][1] = 123456789.123456789;
  matrix[4].matrix[1][0] = 123456789.123456789;
  matrix[4].matrix[1][1] = 123456789.123456789;
  matrix[4].matrix[2][0] = 123456789.123456789;
  matrix[4].matrix[2][1] = 123456789.123456789;

  matrix_t matrix_dif[5];
  s21_create_matrix(3, 4, &matrix_dif[0]);
  set_matrix(&matrix_dif[0]);

  s21_create_matrix(3, 2, &matrix_dif[1]);
  matrix_dif[1].matrix[0][0] = 1.123456789;
  matrix_dif[1].matrix[0][1] = 1.123456789;
  matrix_dif[1].matrix[1][0] = 1.123456689;
  matrix_dif[1].matrix[1][1] = 1.123456789;
  matrix_dif[1].matrix[2][0] = 1.123456789;
  matrix_dif[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix_dif[2]);
  matrix_dif[2].matrix[0][0] = 1.123456746;
  matrix_dif[2].matrix[0][1] = 1.123456789;
  matrix_dif[2].matrix[1][0] = 1.123456723;
  matrix_dif[2].matrix[1][1] = 1.123456789;
  matrix_dif[2].matrix[2][0] = 1.123456789;
  matrix_dif[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix_dif[3]);
  matrix_dif[3].matrix[0][0] = 123456789.123456789;
  matrix_dif[3].matrix[0][1] = 123456789.123456789;
  matrix_dif[3].matrix[1][0] = 123456789.123456789;
  matrix_dif[3].matrix[1][1] = 123456789.123456789;
  matrix_dif[3].matrix[2][0] = 123456789.123456789;
  matrix_dif[3].matrix[2][1] = 123456781.123456789;

  s21_create_matrix(3, 2, &matrix_dif[4]);
  matrix_dif[4].matrix[0][0] = 123456789.123456789;
  matrix_dif[4].matrix[0][1] = 123456789.123456789;
  matrix_dif[4].matrix[1][0] = 123456789.123456789;
  matrix_dif[4].matrix[1][1] = 123456789.123456789;
  matrix_dif[4].matrix[2][0] = 123456789.123456789;
  matrix_dif[4].matrix[2][1] = 123456789.123456789;

  FILE *fp = fopen("tests/data/s21_sum_matrix_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    for (int i = 0; i < 5; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      matrix_t res = {0};
      int return_result = s21_sum_matrix(&matrix[i], &matrix_dif[i], &res);
      print_matrix_in_str(&res, matrix_str, return_result);
      ck_assert_str_eq(matrix_str, str_original);
      s21_remove_matrix(&matrix[i]);
      s21_remove_matrix(&matrix_dif[i]);
      s21_remove_matrix(&res);
    }
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_sum_matrix() {
  Suite *s = suite_create("test_suite_s21_sum_matrix");
  TCase *tc = tcase_create("test_suite_s21_sum_matrix");
  tcase_add_test(tc, s21_sum_matrix_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_sum_matrix_test_error) {
  matrix_t matrix[5];
  s21_create_matrix(3, 3, &matrix[0]);
  for (int i = 0; i < matrix[0].rows; i++) {
    free(matrix->matrix[i]);
  }
  matrix[0].rows = 0;

  s21_create_matrix(3, 3, &matrix[1]);
  matrix[1].columns = 0;

  matrix[2].rows = 2;
  matrix[2].columns = 2;
  matrix[2].matrix = NULL;

  s21_create_matrix(3, 3, &matrix[3]);
  s21_create_matrix(3, 4, &matrix[4]);

  matrix_t no_way_error;
  no_way_error.rows = 3;
  no_way_error.columns = 3;
  no_way_error.matrix = calloc(3, sizeof(double *));
  no_way_error.matrix[0] = NULL;

  matrix_t MAX_DBL;
  s21_create_matrix(2, 2, &MAX_DBL);
  MAX_DBL.matrix[0][0] = DBL_MAX;
  MAX_DBL.matrix[0][1] = 1;
  MAX_DBL.matrix[1][0] = 1;
  MAX_DBL.matrix[1][1] = 1;

  matrix_t res = {0};
  for (int i = 0; i < 3; i++) {
    int return_result = s21_sum_matrix(&matrix[i], &matrix[3], &res);
    ck_assert_int_eq(return_result, 1);
  }
  int return_result = s21_sum_matrix(&matrix[3], &matrix[4], &res);
  ck_assert_int_eq(return_result, 2);

  int return_result_1 = s21_sum_matrix(&no_way_error, &matrix[3], &res);
  ck_assert_int_eq(return_result_1, 1);

  int return_result_2 = s21_sum_matrix(&MAX_DBL, &MAX_DBL, &res);
  ck_assert_int_eq(return_result_2, 2);
  s21_remove_matrix(&res);

  s21_remove_matrix(&matrix[0]);
  s21_remove_matrix(&matrix[1]);
  s21_remove_matrix(&matrix[3]);
  s21_remove_matrix(&matrix[4]);
  s21_remove_matrix(&MAX_DBL);
  free(no_way_error.matrix);
}
END_TEST

Suite *test_suite_s21_sum_matrix_error() {
  Suite *s = suite_create("test_suite_s21_sum_matrix_error");
  TCase *tc = tcase_create("test_suite_s21_sum_matrix_error");
  tcase_add_test(tc, s21_sum_matrix_test_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_sub_matrix_test) {
  matrix_t matrix[5];
  s21_create_matrix(3, 4, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(3, 2, &matrix[1]);
  matrix[1].matrix[0][0] = 1.123456789;
  matrix[1].matrix[0][1] = 1.123456789;
  matrix[1].matrix[1][0] = 1.123456789;
  matrix[1].matrix[1][1] = 1.123456789;
  matrix[1].matrix[2][0] = 1.123456789;
  matrix[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[2]);
  matrix[2].matrix[0][0] = 1.123456789;
  matrix[2].matrix[0][1] = 1.123456789;
  matrix[2].matrix[1][0] = 1.123456789;
  matrix[2].matrix[1][1] = 1.123456789;
  matrix[2].matrix[2][0] = 1.123456789;
  matrix[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[3]);
  matrix[3].matrix[0][0] = 123456789.123456789;
  matrix[3].matrix[0][1] = 123456789.123456789;
  matrix[3].matrix[1][0] = 123456789.123456789;
  matrix[3].matrix[1][1] = 123456789.123456789;
  matrix[3].matrix[2][0] = 123456789.123456789;
  matrix[3].matrix[2][1] = 123456789.123456789;

  s21_create_matrix(3, 2, &matrix[4]);
  matrix[4].matrix[0][0] = 123456789.123456789;
  matrix[4].matrix[0][1] = 123456789.123456789;
  matrix[4].matrix[1][0] = 123456789.123456789;
  matrix[4].matrix[1][1] = 123456789.123456789;
  matrix[4].matrix[2][0] = 123456789.123456789;
  matrix[4].matrix[2][1] = 123456789.123456789;

  matrix_t matrix_dif[5];
  s21_create_matrix(3, 4, &matrix_dif[0]);
  set_matrix(&matrix_dif[0]);

  s21_create_matrix(3, 2, &matrix_dif[1]);
  matrix_dif[1].matrix[0][0] = 1.123456789;
  matrix_dif[1].matrix[0][1] = 1.123456789;
  matrix_dif[1].matrix[1][0] = 1.123456689;
  matrix_dif[1].matrix[1][1] = 1.123456789;
  matrix_dif[1].matrix[2][0] = 1.123456789;
  matrix_dif[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix_dif[2]);
  matrix_dif[2].matrix[0][0] = 1.123456746;
  matrix_dif[2].matrix[0][1] = 1.123456789;
  matrix_dif[2].matrix[1][0] = 1.123456723;
  matrix_dif[2].matrix[1][1] = 1.123456789;
  matrix_dif[2].matrix[2][0] = 1.123456789;
  matrix_dif[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix_dif[3]);
  matrix_dif[3].matrix[0][0] = 123456789.123456789;
  matrix_dif[3].matrix[0][1] = 123456789.123456789;
  matrix_dif[3].matrix[1][0] = 123456789.123456789;
  matrix_dif[3].matrix[1][1] = 123456789.123456789;
  matrix_dif[3].matrix[2][0] = 123458789.123456789;
  matrix_dif[3].matrix[2][1] = 123456781.123456789;

  s21_create_matrix(3, 2, &matrix_dif[4]);
  matrix_dif[4].matrix[0][0] = 123456789.123456789;
  matrix_dif[4].matrix[0][1] = 123456789.123456789;
  matrix_dif[4].matrix[1][0] = 123456789.123456789;
  matrix_dif[4].matrix[1][1] = 123456789.123456789;
  matrix_dif[4].matrix[2][0] = 123456789.123456789;
  matrix_dif[4].matrix[2][1] = 123456789.123456789;

  FILE *fp = fopen("tests/data/s21_sub_matrix_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    for (int i = 0; i < 5; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      matrix_t res = {0};
      int return_result = s21_sub_matrix(&matrix[i], &matrix_dif[i], &res);
      print_matrix_in_str(&res, matrix_str, return_result);
      ck_assert_str_eq(matrix_str, str_original);
      s21_remove_matrix(&matrix[i]);
      s21_remove_matrix(&matrix_dif[i]);
      s21_remove_matrix(&res);
    }
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_sub_matrix() {
  Suite *s = suite_create("test_suite_s21_sub_matrix");
  TCase *tc = tcase_create("test_suite_s21_sub_matrix");
  tcase_add_test(tc, s21_sub_matrix_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_sub_matrix_test_error) {
  matrix_t matrix[5];
  s21_create_matrix(3, 3, &matrix[0]);
  for (int i = 0; i < matrix[0].rows; i++) {
    free(matrix->matrix[i]);
  }
  matrix[0].rows = 0;

  s21_create_matrix(3, 3, &matrix[1]);
  matrix[1].columns = 0;

  matrix[2].rows = 2;
  matrix[2].columns = 2;
  matrix[2].matrix = NULL;

  s21_create_matrix(3, 3, &matrix[3]);
  s21_create_matrix(3, 4, &matrix[4]);

  matrix_t no_way_error;
  no_way_error.rows = 3;
  no_way_error.columns = 3;
  no_way_error.matrix = calloc(3, sizeof(double *));
  no_way_error.matrix[0] = NULL;

  matrix_t neg_MAX_DBL;
  s21_create_matrix(2, 2, &neg_MAX_DBL);
  neg_MAX_DBL.matrix[0][0] = -DBL_MAX;
  neg_MAX_DBL.matrix[0][1] = 1;
  neg_MAX_DBL.matrix[1][0] = 1;
  neg_MAX_DBL.matrix[1][1] = 1;

  matrix_t MAX_DBL;
  s21_create_matrix(2, 2, &MAX_DBL);
  MAX_DBL.matrix[0][0] = DBL_MAX;
  MAX_DBL.matrix[0][1] = 1;
  MAX_DBL.matrix[1][0] = 1;
  MAX_DBL.matrix[1][1] = 1;

  matrix_t res = {0};
  for (int i = 0; i < 3; i++) {
    int return_result = s21_sub_matrix(&matrix[i], &matrix[3], &res);
    ck_assert_int_eq(return_result, 1);
  }
  int return_result = s21_sub_matrix(&matrix[3], &matrix[4], &res);
  ck_assert_int_eq(return_result, 2);

  int return_result_1 = s21_sub_matrix(&no_way_error, &matrix[3], &res);
  ck_assert_int_eq(return_result_1, 1);

  int return_result_2 = s21_sub_matrix(&neg_MAX_DBL, &MAX_DBL, &res);
  ck_assert_int_eq(return_result_2, 2);
  s21_remove_matrix(&res);

  s21_remove_matrix(&matrix[0]);
  s21_remove_matrix(&matrix[1]);
  s21_remove_matrix(&matrix[3]);
  s21_remove_matrix(&matrix[4]);
  s21_remove_matrix(&MAX_DBL);
  s21_remove_matrix(&neg_MAX_DBL);
  free(no_way_error.matrix);
}
END_TEST

Suite *test_suite_s21_sub_matrix_error() {
  Suite *s = suite_create("test_suite_s21_sub_matrix_error");
  TCase *tc = tcase_create("test_suite_s21_sub_matrix_error");
  tcase_add_test(tc, s21_sub_matrix_test_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_mult_number_test) {
  matrix_t matrix[5];
  s21_create_matrix(3, 4, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(3, 2, &matrix[1]);
  matrix[1].matrix[0][0] = 1.123456789;
  matrix[1].matrix[0][1] = 1.123456789;
  matrix[1].matrix[1][0] = 1.123456789;
  matrix[1].matrix[1][1] = 1.123456789;
  matrix[1].matrix[2][0] = 1.123456789;
  matrix[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[2]);
  matrix[2].matrix[0][0] = 1.123456789;
  matrix[2].matrix[0][1] = 1.123456789;
  matrix[2].matrix[1][0] = 1.123456789;
  matrix[2].matrix[1][1] = 1.123456789;
  matrix[2].matrix[2][0] = 1.123456789;
  matrix[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(3, 2, &matrix[3]);
  matrix[3].matrix[0][0] = 123456789.123456789;
  matrix[3].matrix[0][1] = 123456789.123456789;
  matrix[3].matrix[1][0] = 123456789.123456789;
  matrix[3].matrix[1][1] = 123456789.123456789;
  matrix[3].matrix[2][0] = 123456789.123456789;
  matrix[3].matrix[2][1] = 123456789.123456789;

  s21_create_matrix(3, 2, &matrix[4]);
  matrix[4].matrix[0][0] = 123456789.123456789;
  matrix[4].matrix[0][1] = 123456789.123456789;
  matrix[4].matrix[1][0] = 123456789.123456789;
  matrix[4].matrix[1][1] = 123456789.123456789;
  matrix[4].matrix[2][0] = 123456789.123456789;
  matrix[4].matrix[2][1] = 123456789.123456789;

  FILE *fp = fopen("tests/data/s21_mult_number_matrix_data.txt", "r");
  double number[5] = {-1.0, 0, 1.0, 2.0, 3.43};
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    for (int i = 0; i < 5; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      matrix_t res = {0};
      int return_result = s21_mult_number(&matrix[i], number[i], &res);
      print_matrix_in_str(&res, matrix_str, return_result);
      ck_assert_str_eq(matrix_str, str_original);
      s21_remove_matrix(&matrix[i]);
      s21_remove_matrix(&res);
    }
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_ss21_mult_number() {
  Suite *s = suite_create("test_suite_ss21_mult_number");
  TCase *tc = tcase_create("test_suite_ss21_mult_number");
  tcase_add_test(tc, s21_mult_number_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_mult_number_test_error) {
  matrix_t matrix[5];
  s21_create_matrix(3, 4, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(3, 3, &matrix[1]);
  matrix[1].columns = 0;

  matrix[2].rows = 2;
  matrix[2].columns = 2;
  matrix[2].matrix = NULL;

  s21_create_matrix(3, 3, &matrix[3]);
  s21_create_matrix(3, 4, &matrix[4]);

  matrix_t no_way_error;
  no_way_error.rows = 3;
  no_way_error.columns = 3;
  no_way_error.matrix = calloc(3, sizeof(double *));
  no_way_error.matrix[0] = NULL;

  matrix_t MAX_DBL;
  s21_create_matrix(2, 2, &MAX_DBL);
  MAX_DBL.matrix[0][0] = DBL_MAX;
  MAX_DBL.matrix[0][1] = 1;
  MAX_DBL.matrix[1][0] = 1;
  MAX_DBL.matrix[1][1] = 1;

  double number[6] = {NAN, -NAN, INFINITY, -INFINITY, DBL_MAX, -DBL_MAX};
  for (int i = 0; i < 6; i++) {
    matrix_t res = {0};
    int return_result = s21_mult_number(&matrix[0], number[i], &res);
    ck_assert_int_eq(return_result, 2);
    if (i == 4 || i == 5) {
      s21_remove_matrix(&res);
    }
  }

  matrix_t res = {0};
  for (int i = 1; i < 3; i++) {
    int return_result = s21_mult_number(&matrix[i], 1, &res);
    ck_assert_int_eq(return_result, 1);
  }

  int return_result_1 = s21_mult_number(&no_way_error, 1, &res);
  ck_assert_int_eq(return_result_1, 1);

  int return_result_2 = s21_mult_number(&MAX_DBL, DBL_MAX, &res);
  ck_assert_int_eq(return_result_2, 2);
  s21_remove_matrix(&res);

  s21_remove_matrix(&matrix[0]);
  s21_remove_matrix(&matrix[1]);
  s21_remove_matrix(&matrix[3]);
  s21_remove_matrix(&matrix[4]);
  s21_remove_matrix(&MAX_DBL);
  free(no_way_error.matrix);
}
END_TEST

Suite *test_suite_ss21_mult_number_error() {
  Suite *s = suite_create("test_suite_ss21_mult_number_error");
  TCase *tc = tcase_create("test_suite_ss21_mult_number_error");
  tcase_add_test(tc, s21_mult_number_test_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_mult_matrix_test) {
  matrix_t matrix[5];
  matrix_t matrix_dif[5];

  s21_create_matrix(3, 4, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(4, 3, &matrix_dif[0]);
  set_matrix(&matrix_dif[0]);

  s21_create_matrix(3, 2, &matrix[1]);
  matrix[1].matrix[0][0] = 1.123456789;
  matrix[1].matrix[0][1] = 1.123456789;
  matrix[1].matrix[1][0] = 1.123456789;
  matrix[1].matrix[1][1] = 1.123456789;
  matrix[1].matrix[2][0] = 1.123456789;
  matrix[1].matrix[2][1] = 1.123456789;

  s21_create_matrix(2, 3, &matrix_dif[1]);
  matrix_dif[1].matrix[0][0] = 1.123456789;
  matrix_dif[1].matrix[0][1] = 1.123456789;
  matrix_dif[1].matrix[0][2] = 1.123456689;
  matrix_dif[1].matrix[1][0] = 1.123456789;
  matrix_dif[1].matrix[1][1] = 1.123456789;
  matrix_dif[1].matrix[1][2] = 1.123456789;

  ///

  s21_create_matrix(3, 2, &matrix[2]);
  matrix[2].matrix[0][0] = -2151.123456789;
  matrix[2].matrix[0][1] = -1.123456789;
  matrix[2].matrix[1][0] = 0;
  matrix[2].matrix[1][1] = 1.123456789;
  matrix[2].matrix[2][0] = 1.123456789;
  matrix[2].matrix[2][1] = 1.123456789;

  s21_create_matrix(2, 3, &matrix_dif[2]);
  matrix_dif[2].matrix[0][0] = 1.123456746;
  matrix_dif[2].matrix[0][1] = 1.123456789;
  matrix_dif[2].matrix[0][2] = 1.123456723;
  matrix_dif[2].matrix[1][0] = 1.123456789;
  matrix_dif[2].matrix[1][1] = 1.123456789;
  matrix_dif[2].matrix[1][2] = 1.123456789;

  ///

  s21_create_matrix(3, 2, &matrix[3]);
  matrix[3].matrix[0][0] = 0;
  matrix[3].matrix[0][1] = 0;
  matrix[3].matrix[1][0] = 0;
  matrix[3].matrix[1][1] = 0;
  matrix[3].matrix[2][0] = 0;
  matrix[3].matrix[2][1] = 0;

  s21_create_matrix(2, 3, &matrix_dif[3]);
  matrix_dif[3].matrix[0][0] = 123456789.123456789;
  matrix_dif[3].matrix[0][1] = 123456789.123456789;
  matrix_dif[3].matrix[0][2] = 123456789.123456789;
  matrix_dif[3].matrix[1][0] = 123456789.123456789;
  matrix_dif[3].matrix[1][1] = 123456789.123456789;
  matrix_dif[3].matrix[1][2] = 123456781.123456789;

  ///

  s21_create_matrix(4, 5, &matrix[4]);
  s21_create_matrix(5, 4, &matrix_dif[4]);
  set_matrix(&matrix[4]);
  set_matrix(&matrix_dif[4]);

  FILE *fp = fopen("tests/data/s21_mult_matrix_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    for (int i = 0; i < 5; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      matrix_t res = {0};
      int return_result = s21_mult_matrix(&matrix[i], &matrix_dif[i], &res);
      print_matrix_in_str(&res, matrix_str, return_result);
      ck_assert_str_eq(matrix_str, str_original);
      s21_remove_matrix(&matrix[i]);
      s21_remove_matrix(&matrix_dif[i]);
      s21_remove_matrix(&res);
    }
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_mult_matrix() {
  Suite *s = suite_create("test_suite_s21_mult_matrix");
  TCase *tc = tcase_create("test_suite_s21_mult_matrix");
  tcase_add_test(tc, s21_mult_matrix_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_mult_matrix_test_error) {
  matrix_t matrix[5];
  s21_create_matrix(3, 3, &matrix[0]);
  for (int i = 0; i < matrix[0].rows; i++) {
    free(matrix->matrix[i]);
  }
  matrix[0].rows = 0;

  s21_create_matrix(3, 3, &matrix[1]);
  matrix[1].columns = 0;

  matrix[2].rows = 2;
  matrix[2].columns = 2;
  matrix[2].matrix = NULL;

  s21_create_matrix(3, 3, &matrix[3]);
  s21_create_matrix(3, 4, &matrix[4]);

  matrix_t no_way_error;
  no_way_error.rows = 3;
  no_way_error.columns = 3;
  no_way_error.matrix = calloc(3, sizeof(double *));
  no_way_error.matrix[0] = NULL;

  matrix_t neg_MAX_DBL;
  s21_create_matrix(2, 2, &neg_MAX_DBL);
  neg_MAX_DBL.matrix[0][0] = DBL_MAX;
  neg_MAX_DBL.matrix[0][1] = 1;
  neg_MAX_DBL.matrix[1][0] = 1;
  neg_MAX_DBL.matrix[1][1] = 1;

  matrix_t MAX_DBL;
  s21_create_matrix(2, 2, &MAX_DBL);
  MAX_DBL.matrix[0][0] = DBL_MAX;
  MAX_DBL.matrix[0][1] = 1;
  MAX_DBL.matrix[1][0] = 1;
  MAX_DBL.matrix[1][1] = 1;

  matrix_t res = {0};
  for (int i = 0; i < 3; i++) {
    int return_result = s21_mult_matrix(&matrix[i], &matrix[3], &res);
    ck_assert_int_eq(return_result, 1);
  }
  int return_result = s21_mult_matrix(&matrix[3], &matrix[4], &res);
  ck_assert_int_eq(return_result, 2);

  int return_result_1 = s21_mult_matrix(&no_way_error, &matrix[3], &res);
  ck_assert_int_eq(return_result_1, 1);

  int return_result_2 = s21_mult_matrix(&neg_MAX_DBL, &MAX_DBL, &res);
  ck_assert_int_eq(return_result_2, 2);
  s21_remove_matrix(&res);

  s21_remove_matrix(&matrix[0]);
  s21_remove_matrix(&matrix[1]);
  s21_remove_matrix(&matrix[3]);
  s21_remove_matrix(&matrix[4]);
  s21_remove_matrix(&MAX_DBL);
  s21_remove_matrix(&neg_MAX_DBL);
  free(no_way_error.matrix);
}
END_TEST

Suite *test_suite_s21_mult_matrix_error() {
  Suite *s = suite_create("test_suite_s21_mult_matrix_error");
  TCase *tc = tcase_create("test_suite_s21_mult_matrix_error");
  tcase_add_test(tc, s21_mult_matrix_test_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_transpose_matrix_test) {
  matrix_t matrix[3];
  s21_create_matrix(3, 3, &matrix[0]);
  set_matrix(&matrix[0]);

  s21_create_matrix(2, 3, &matrix[1]);
  matrix[1].matrix[0][0] = 123456789.123456789;
  matrix[1].matrix[0][1] = 123456789.123456789;
  matrix[1].matrix[0][2] = 123456789.123456789;
  matrix[1].matrix[1][0] = 123456789.123456789;
  matrix[1].matrix[1][1] = 123456789.123456789;
  matrix[1].matrix[1][2] = 123456781.123456789;

  s21_create_matrix(4, 2, &matrix[2]);
  matrix[2].matrix[0][0] = -1;
  matrix[2].matrix[0][1] = -2;
  matrix[2].matrix[1][0] = -3;
  matrix[2].matrix[1][1] = -4;
  matrix[2].matrix[2][0] = -5;
  matrix[2].matrix[2][1] = -6;
  matrix[2].matrix[3][0] = -7;
  matrix[2].matrix[3][1] = -8;

  FILE *fp = fopen("tests/data/s21_transpose_matrix_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    for (int i = 0; i < 3; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      matrix_t res = {0};
      int return_result = s21_transpose(&matrix[i], &res);
      print_matrix_in_str(&res, matrix_str, return_result);
      ck_assert_str_eq(matrix_str, str_original);
      s21_remove_matrix(&matrix[i]);
      s21_remove_matrix(&res);
    }
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_transpose_matrix() {
  Suite *s = suite_create("test_suite_s21_transpose_matrix");
  TCase *tc = tcase_create("test_suite_s21_transpose_matrix");
  tcase_add_test(tc, s21_transpose_matrix_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_transpose_matrix_test_error) {
  matrix_t matrix[5];
  s21_create_matrix(3, 3, &matrix[0]);
  for (int i = 0; i < matrix[0].rows; i++) {
    free(matrix->matrix[i]);
  }
  matrix[0].rows = 0;

  s21_create_matrix(3, 3, &matrix[1]);
  matrix[1].columns = 0;

  matrix[2].rows = 2;
  matrix[2].columns = 2;
  matrix[2].matrix = NULL;

  matrix_t no_way_error;
  no_way_error.rows = 3;
  no_way_error.columns = 3;
  no_way_error.matrix = calloc(3, sizeof(double *));
  no_way_error.matrix[0] = NULL;

  matrix_t res = {0};
  for (int i = 0; i < 3; i++) {
    int return_result = s21_transpose(&matrix[i], &res);
    ck_assert_int_eq(return_result, 1);
  }

  int return_result_1 = s21_transpose(&no_way_error, &res);
  ck_assert_int_eq(return_result_1, 1);

  s21_remove_matrix(&matrix[0]);
  s21_remove_matrix(&matrix[1]);
  free(no_way_error.matrix);
}
END_TEST

Suite *test_suite_s21_transpose_matrix_error() {
  Suite *s = suite_create("test_suite_s21_transpose_matrix_error");
  TCase *tc = tcase_create("test_suite_s21_transpose_matrix_error");
  tcase_add_test(tc, s21_transpose_matrix_test_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_calc_complements_error) {
  matrix_t matrix[5];
  s21_create_matrix(3, 3, &matrix[0]);
  for (int i = 0; i < matrix[0].rows; i++) {
    free(matrix->matrix[i]);
  }
  matrix[0].rows = 0;

  s21_create_matrix(3, 3, &matrix[1]);
  matrix[1].columns = 0;

  matrix[2].rows = 2;
  matrix[2].columns = 2;
  matrix[2].matrix = NULL;

  matrix_t no_way_error;
  no_way_error.rows = 3;
  no_way_error.columns = 3;
  no_way_error.matrix = calloc(3, sizeof(double *));
  no_way_error.matrix[0] = NULL;

  matrix_t res = {0};
  for (int i = 0; i < 3; i++) {
    int return_result = s21_calc_complements(&matrix[i], &res);
    ck_assert_int_eq(return_result, 1);
  }

  int return_result_1 = s21_calc_complements(&no_way_error, &res);
  ck_assert_int_eq(return_result_1, 1);

  s21_remove_matrix(&matrix[0]);
  s21_remove_matrix(&matrix[1]);
  free(no_way_error.matrix);
}
END_TEST

Suite *test_suite_s21_calc_complements_error() {
  Suite *s = suite_create("test_suite_s21_calc_complements_error");
  TCase *tc = tcase_create("test_suite_s21_calc_complements_error");
  tcase_add_test(tc, s21_calc_complements_error);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_calc_complements_test) {
  matrix_t matrix = {0};
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  FILE *fp = fopen("tests/data/s21_calc_complements_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    fgets(str_original, sizeof(str_original), fp);
    str_original[strlen(str_original) - 1] = '\0';
    matrix_t res = {0};
    int return_result = s21_calc_complements(&matrix, &res);
    print_matrix_in_str(&res, matrix_str, return_result);
    ck_assert_str_eq(matrix_str, str_original);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&res);
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_calc_complements() {
  Suite *s = suite_create("test_suite_s21_calc_complements");
  TCase *tc = tcase_create("test_suite_s21_calc_complements");
  tcase_add_test(tc, s21_calc_complements_test);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_determinant_test_2x2) {
  matrix_t matrix = {0};
  double value = 10759902.756;

  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 14234;
  matrix.matrix[0][1] = -2234;
  matrix.matrix[1][0] = 3324;
  matrix.matrix[1][1] = 234.234;

  double res;
  s21_determinant(&matrix, &res);
  ck_assert_double_eq_tol(res, value, 1e-7);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite *test_suite_s21_determinant_2x2() {
  Suite *s = suite_create("test_suite_s21_determinant_2x2");
  TCase *tc = tcase_create("test_suite_s21_determinant_2x2");
  tcase_add_test(tc, s21_determinant_test_2x2);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_determinant_test_3x3) {
  matrix_t matrix = {0};
  double value = -14351145.1125;
  double res;

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1234.25;
  matrix.matrix[0][1] = -234.4;
  matrix.matrix[0][2] = 624;
  matrix.matrix[1][0] = 43;
  matrix.matrix[1][1] = 45;
  matrix.matrix[1][2] = 1;
  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = -560;
  matrix.matrix[2][2] = -0.25;

  s21_determinant(&matrix, &res);
  ck_assert_double_eq_tol(res, value, 1e-7);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite *test_suite_s21_determinant_3x3() {
  Suite *s = suite_create("test_suite_s21_determinant_3x3");
  TCase *tc = tcase_create("test_suite_s21_determinant_3x3");
  tcase_add_test(tc, s21_determinant_test_3x3);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_determinant_test_4x4) {
  matrix_t matrix = {0};
  double value = 1563370.85615;
  double res;

  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 1234.25;
  matrix.matrix[0][1] = -234.4;
  matrix.matrix[0][2] = 624;
  matrix.matrix[0][3] = 624;

  matrix.matrix[1][0] = 43;
  matrix.matrix[1][1] = 45;
  matrix.matrix[1][2] = 1;
  matrix.matrix[1][3] = 1;

  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -0.25;
  matrix.matrix[2][3] = -0.45;

  matrix.matrix[3][0] = 30;
  matrix.matrix[3][1] = 2.303;
  matrix.matrix[3][2] = 23;
  matrix.matrix[3][3] = 2;

  s21_determinant(&matrix, &res);
  ck_assert_double_eq_tol(res, value, 1e-7);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite *test_suite_s21_determinant_4x4() {
  Suite *s = suite_create("test_suite_s21_determinant_4x4");
  TCase *tc = tcase_create("test_suite_s21_determinant_4x4");
  tcase_add_test(tc, s21_determinant_test_4x4);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_determinant_test_5x5) {
  matrix_t matrix = {0};
  double value = -82677054.89092243;
  double res;

  s21_create_matrix(5, 5, &matrix);
  matrix.matrix[0][0] = 1234.25;
  matrix.matrix[0][1] = -234.4;
  matrix.matrix[0][2] = 624;
  matrix.matrix[0][3] = 624;
  matrix.matrix[0][4] = 23;

  matrix.matrix[1][0] = 43;
  matrix.matrix[1][1] = 45;
  matrix.matrix[1][2] = 1;
  matrix.matrix[1][3] = 1;
  matrix.matrix[1][4] = 14.3;

  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -0.25;
  matrix.matrix[2][3] = -0.45;
  matrix.matrix[2][4] = 3.15;

  matrix.matrix[3][0] = 30;
  matrix.matrix[3][1] = 2.303;
  matrix.matrix[3][2] = 23;
  matrix.matrix[3][3] = 2;
  matrix.matrix[3][4] = 25.5;

  matrix.matrix[4][0] = 14.04;
  matrix.matrix[4][1] = 42.07;
  matrix.matrix[4][2] = -9.3;
  matrix.matrix[4][3] = -25;
  matrix.matrix[4][4] = -2.5;

  s21_determinant(&matrix, &res);
  ck_assert_double_eq_tol(res, value, 1e-7);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite *test_suite_s21_determinant_5x5() {
  Suite *s = suite_create("test_suite_s21_determinant_5x5");
  TCase *tc = tcase_create("test_suite_s21_determinant_5x5");
  tcase_add_test(tc, s21_determinant_test_5x5);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_determinant_test_6x6) {
  matrix_t matrix = {0};
  double value = 53342143.1860735;
  double res;

  s21_create_matrix(6, 6, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 0.1;
  matrix.matrix[0][3] = 0.55;
  matrix.matrix[0][4] = 0.66;
  matrix.matrix[0][5] = 0.4;

  matrix.matrix[1][0] = 34;
  matrix.matrix[1][1] = 35;
  matrix.matrix[1][2] = 89;
  matrix.matrix[1][3] = 5;
  matrix.matrix[1][4] = 78;
  matrix.matrix[1][5] = 13;

  matrix.matrix[2][0] = 12;
  matrix.matrix[2][1] = 35;
  matrix.matrix[2][2] = 0.48;
  matrix.matrix[2][3] = 0.56;
  matrix.matrix[2][4] = 0.12;
  matrix.matrix[2][5] = 42;

  matrix.matrix[3][0] = 32;
  matrix.matrix[3][1] = 13;
  matrix.matrix[3][2] = 12;
  matrix.matrix[3][3] = 12;
  matrix.matrix[3][4] = 11;
  matrix.matrix[3][5] = 0.112;

  matrix.matrix[4][0] = 2.01;
  matrix.matrix[4][1] = 2.9;
  matrix.matrix[4][2] = 5;
  matrix.matrix[4][3] = 45;
  matrix.matrix[4][4] = 62.5;
  matrix.matrix[4][5] = 52.2;

  matrix.matrix[5][0] = 5.4;
  matrix.matrix[5][1] = 56.5;
  matrix.matrix[5][2] = 0.1;
  matrix.matrix[5][3] = 3.5;
  matrix.matrix[5][4] = 7;
  matrix.matrix[5][5] = 8;

  s21_determinant(&matrix, &res);
  ck_assert_double_eq_tol(res, value, 1e-7);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite *test_suite_s21_determinant_6x6() {
  Suite *s = suite_create("test_suite_s21_determinant_6x6");
  TCase *tc = tcase_create("test_suite_s21_determinant_6x6");
  tcase_add_test(tc, s21_determinant_test_6x6);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_inverse_matrix_test_2x2) {
  matrix_t matrix = {0};

  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 14234;
  matrix.matrix[0][1] = -2234;
  matrix.matrix[1][0] = 3324;
  matrix.matrix[1][1] = 234.234;

  FILE *fp = fopen("tests/data/s21_inverse_matrix_2x2_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    fgets(str_original, 1024, fp);
    str_original[strlen(str_original) - 1] = '\0';
    matrix_t res = {0};
    int return_result = s21_inverse_matrix(&matrix, &res);
    print_matrix_in_str(&res, matrix_str, return_result);
    ck_assert_str_eq(matrix_str, str_original);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&res);
    fclose(fp);
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_inverse_matrix_2x2() {
  Suite *s = suite_create("test_suite_s21_inverse_matrix_2x2");
  TCase *tc = tcase_create("test_suite_s21_inverse_matrix_2x2");
  tcase_add_test(tc, s21_inverse_matrix_test_2x2);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_inverse_matrix_test_3x3) {
  matrix_t matrix = {0};

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1234.25;
  matrix.matrix[0][1] = -234.4;
  matrix.matrix[0][2] = 624;
  matrix.matrix[1][0] = 43;
  matrix.matrix[1][1] = 45;
  matrix.matrix[1][2] = 1;
  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = -560;
  matrix.matrix[2][2] = -0.25;

  FILE *fp = fopen("tests/data/s21_inverse_matrix_3x3_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    fgets(str_original, sizeof(str_original), fp);
    str_original[strlen(str_original) - 1] = '\0';
    matrix_t res = {0};
    int return_result = s21_inverse_matrix(&matrix, &res);
    print_matrix_in_str(&res, matrix_str, return_result);
    ck_assert_str_eq(matrix_str, str_original);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&res);
    fclose(fp);
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_inverse_matrix_3x3() {
  Suite *s = suite_create("test_suite_s21_inverse_matrix_3x3");
  TCase *tc = tcase_create("test_suite_s21_inverse_matrix_3x3");
  tcase_add_test(tc, s21_inverse_matrix_test_3x3);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_inverse_matrix_test_4x4) {
  matrix_t matrix = {0};

  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 1234.25;
  matrix.matrix[0][1] = -234.4;
  matrix.matrix[0][2] = 624;
  matrix.matrix[0][3] = 624;

  matrix.matrix[1][0] = 43;
  matrix.matrix[1][1] = 45;
  matrix.matrix[1][2] = 1;
  matrix.matrix[1][3] = 1;

  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -0.25;
  matrix.matrix[2][3] = -0.45;

  matrix.matrix[3][0] = 30;
  matrix.matrix[3][1] = 2.303;
  matrix.matrix[3][2] = 23;
  matrix.matrix[3][3] = 2;

  FILE *fp = fopen("tests/data/s21_inverse_matrix_4x4_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    fgets(str_original, sizeof(str_original), fp);
    str_original[strlen(str_original) - 1] = '\0';
    matrix_t res = {0};
    int return_result = s21_inverse_matrix(&matrix, &res);
    print_matrix_in_str(&res, matrix_str, return_result);
    ck_assert_str_eq(matrix_str, str_original);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&res);
    fclose(fp);
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_inverse_matrix_4x4() {
  Suite *s = suite_create("test_suite_s21_inverse_matrix_4x4");
  TCase *tc = tcase_create("test_suite_s21_inverse_matrix_4x4");
  tcase_add_test(tc, s21_inverse_matrix_test_4x4);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_inverse_matrix_test_5x5) {
  matrix_t matrix = {0};

  s21_create_matrix(5, 5, &matrix);
  matrix.matrix[0][0] = 1234.25;
  matrix.matrix[0][1] = -234.4;
  matrix.matrix[0][2] = 624;
  matrix.matrix[0][3] = 624;
  matrix.matrix[0][4] = 23;

  matrix.matrix[1][0] = 43;
  matrix.matrix[1][1] = 45;
  matrix.matrix[1][2] = 1;
  matrix.matrix[1][3] = 1;
  matrix.matrix[1][4] = 14.3;

  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -0.25;
  matrix.matrix[2][3] = -0.45;
  matrix.matrix[2][4] = 3.15;

  matrix.matrix[3][0] = 30;
  matrix.matrix[3][1] = 2.303;
  matrix.matrix[3][2] = 23;
  matrix.matrix[3][3] = 2;
  matrix.matrix[3][4] = 25.5;

  matrix.matrix[4][0] = 14.04;
  matrix.matrix[4][1] = 42.07;
  matrix.matrix[4][2] = -9.3;
  matrix.matrix[4][3] = -25;
  matrix.matrix[4][4] = -2.5;

  FILE *fp = fopen("tests/data/s21_inverse_matrix_5x5_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    fgets(str_original, sizeof(str_original), fp);
    str_original[strlen(str_original) - 1] = '\0';
    matrix_t res = {0};
    int return_result = s21_inverse_matrix(&matrix, &res);
    print_matrix_in_str(&res, matrix_str, return_result);
    ck_assert_str_eq(matrix_str, str_original);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&res);
    fclose(fp);
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_inverse_matrix_5x5() {
  Suite *s = suite_create("test_suite_s21_inverse_matrix_5x5");
  TCase *tc = tcase_create("test_suite_s21_inverse_matrix_5x5");
  tcase_add_test(tc, s21_inverse_matrix_test_5x5);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_inverse_matrix_test_6x6) {
  matrix_t matrix = {0};

  s21_create_matrix(6, 6, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 0.1;
  matrix.matrix[0][3] = 0.55;
  matrix.matrix[0][4] = 0.66;
  matrix.matrix[0][5] = 0.4;

  matrix.matrix[1][0] = 34;
  matrix.matrix[1][1] = 35;
  matrix.matrix[1][2] = 89;
  matrix.matrix[1][3] = 5;
  matrix.matrix[1][4] = 78;
  matrix.matrix[1][5] = 13;

  matrix.matrix[2][0] = 12;
  matrix.matrix[2][1] = 35;
  matrix.matrix[2][2] = 0.48;
  matrix.matrix[2][3] = 0.56;
  matrix.matrix[2][4] = 0.12;
  matrix.matrix[2][5] = 42;

  matrix.matrix[3][0] = 32;
  matrix.matrix[3][1] = 13;
  matrix.matrix[3][2] = 12;
  matrix.matrix[3][3] = 12;
  matrix.matrix[3][4] = 11;
  matrix.matrix[3][5] = 0.112;

  matrix.matrix[4][0] = 2.01;
  matrix.matrix[4][1] = 2.9;
  matrix.matrix[4][2] = 5;
  matrix.matrix[4][3] = 45;
  matrix.matrix[4][4] = 62.5;
  matrix.matrix[4][5] = 52.2;

  matrix.matrix[5][0] = 5.4;
  matrix.matrix[5][1] = 56.5;
  matrix.matrix[5][2] = 0.1;
  matrix.matrix[5][3] = 3.5;
  matrix.matrix[5][4] = 7;
  matrix.matrix[5][5] = 8;

  FILE *fp = fopen("tests/data/s21_inverse_matrix_6x6_data.txt", "r");
  if (fp) {
    char matrix_str[1024] = {'\0'};
    char str_original[1024] = {'\0'};
    fgets(str_original, sizeof(str_original), fp);
    str_original[strlen(str_original) - 1] = '\0';
    matrix_t res = {0};
    int return_result = s21_inverse_matrix(&matrix, &res);
    print_matrix_in_str(&res, matrix_str, return_result);
    ck_assert_str_eq(matrix_str, str_original);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&res);
    fclose(fp);
  } else
    fprintf(stderr, "no file");
}
END_TEST

Suite *test_suite_s21_inverse_matrix_6x6() {
  Suite *s = suite_create("test_suite_s21_inverse_matrix_6x6");
  TCase *tc = tcase_create("test_suite_s21_inverse_matrix_6x6");
  tcase_add_test(tc, s21_inverse_matrix_test_6x6);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int no_failed = 0;
  Suite *test_suites[] = {test_suite_s21_create_matrix(),
                          test_suite_s21_create_matrix_error(),
                          test_suite_s21_eq_matrix(),
                          test_suite_s21_sum_matrix(),
                          test_suite_s21_sum_matrix_error(),
                          test_suite_s21_sub_matrix(),
                          test_suite_s21_sub_matrix_error(),
                          test_suite_ss21_mult_number(),
                          test_suite_ss21_mult_number_error(),
                          test_suite_s21_mult_matrix(),
                          test_suite_s21_mult_matrix_error(),
                          test_suite_s21_transpose_matrix(),
                          test_suite_s21_transpose_matrix_error(),
                          test_suite_s21_calc_complements(),
                          test_suite_s21_calc_complements_error(),
                          test_suite_s21_determinant_2x2(),
                          test_suite_s21_determinant_3x3(),
                          test_suite_s21_determinant_4x4(),
                          test_suite_s21_determinant_5x5(),
                          test_suite_s21_determinant_6x6(),
                          test_suite_s21_inverse_matrix_2x2(),
                          test_suite_s21_inverse_matrix_3x3(),
                          test_suite_s21_inverse_matrix_4x4(),
                          test_suite_s21_inverse_matrix_5x5(),
                          test_suite_s21_inverse_matrix_6x6(),
                          NULL};
  for (Suite **suite = test_suites; *suite != NULL; suite++) {
    SRunner *runner = srunner_create(*suite);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return no_failed;
}
