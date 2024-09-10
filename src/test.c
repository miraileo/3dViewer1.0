#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "transformations.h"

START_TEST(pars_01) {
  int ERROR;
  Model A;
  ERROR = loadModel(&A, "models/cube.obj");
  ck_assert_int_eq(ERROR, 0);
  deleteModel(&A);
}

START_TEST(pars_02) {
  int ERROR;
  Model A;
  ERROR = loadModel(&A, "models/man.obj");
  ck_assert_int_eq(ERROR, 1);
}

START_TEST(pars_03) {
  int ERROR;
  Model A;
  ERROR = loadModel(&A, "models/cube.obj");
  ck_assert_int_eq(ERROR, 0);
  deleteModel(&A);
}

START_TEST(pars_04) {
  int ERROR;
  Model A;
  ERROR = loadModel(&A, "models/blank.obj");
  ck_assert_int_eq(ERROR, 1);
}

START_TEST(move_x) {
  Model A;
  float a = 0;
  loadModel(&A, "models/test_afinne.obj");
  ck_assert_double_eq(A.vertices[3], 1);
  a = moveX(&A, 2, a);
  ck_assert_double_eq(A.vertices[3], 3);
  deleteModel(&A);
}

START_TEST(move_y) {
  Model A;
  float a = 0;
  loadModel(&A, "models/test_afinne.obj");
  a = moveY(&A, 2, a);
  ck_assert_double_eq(A.vertices[4], 3);
  deleteModel(&A);
}

START_TEST(move_z) {
  Model A;
  float a = 0;
  loadModel(&A, "models/test_afinne.obj");
  a = moveZ(&A, 2, a);
  ck_assert_double_eq(A.vertices[5], 3);
  deleteModel(&A);
}

START_TEST(rotation_x) {
  Model A;
  float a = 0;
  loadModel(&A, "models/test_afinne.obj");
  a = rotateX(&A, 60, a);
  double angleToRad = 60 * M_PI / 180.0f;
  double temp_y = cos(-angleToRad) * 1 - sin(-angleToRad) * 1;
  double temp_z = sin(-angleToRad) * 1 + cos(-angleToRad) * 1;
  ck_assert_double_eq_tol(A.vertices[3], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[4], temp_y, 1e-6);
  ck_assert_double_eq_tol(A.vertices[5], temp_z, 1e-6);
  deleteModel(&A);
}

START_TEST(rotation_y) {
  Model A;
  float a = 0;
  loadModel(&A, "models/test_afinne.obj");
  a = rotateY(&A, 60, a);
  double angleToRad = 60 * M_PI / 180.0f;
  double temp_x = cos(-angleToRad) * 3 - sin(-angleToRad) * 3;
  double temp_z = sin(-angleToRad) * 3 + cos(-angleToRad) * 3;
  ck_assert_double_eq_tol(A.vertices[6], temp_x, 1e-6);
  ck_assert_double_eq_tol(A.vertices[7], 3, 1e-6);
  ck_assert_double_eq_tol(A.vertices[8], temp_z, 1e-6);
  deleteModel(&A);
}

START_TEST(rotation_z) {
  Model A;
  float a = 0;
  loadModel(&A, "models/test_afinne.obj");
  a = rotateZ(&A, 60, a);
  double angleToRad = 60 * M_PI / 180.0f;
  double temp_x = cos(-angleToRad) * 3 - sin(-angleToRad) * 3;
  double temp_y = sin(-angleToRad) * 3 + cos(-angleToRad) * 3;
  ck_assert_double_eq_tol(A.vertices[6], temp_x, 1e-6);
  ck_assert_double_eq_tol(A.vertices[7], temp_y, 1e-6);
  ck_assert_double_eq_tol(A.vertices[8], 3, 1e-6);
  deleteModel(&A);
}

START_TEST(scale) {
  Model A;
  float a = 1;
  loadModel(&A, "models/test_afinne.obj");
  a = scaleModel(&A, 5, a);
  ck_assert_double_eq(A.vertices[6], 18);
  ck_assert_double_eq(A.vertices[7], 18);
  ck_assert_double_eq(A.vertices[8], 18);
  deleteModel(&A);
}

START_TEST(incorrect_input) {
  Model A;
  int code = loadModel(&A, "models/blank.obj");
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(correct_input) {
  Model A;
  int code = loadModel(&A, "models/minicooper.obj");
  ck_assert_int_eq(code, 0);
  deleteModel(&A);
}
END_TEST

START_TEST(parser_array) {
  Model A;
  int code = loadModel(&A, "models/test.obj");
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq_tol(A.vertices[3], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[4], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[5], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[6], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[7], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[8], 1.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[9], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[10], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[11], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[12], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[13], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[14], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[15], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[16], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[17], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[18], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[19], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[20], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[21], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[22], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[23], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[24], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[25], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[26], 1, 1e-6);
  deleteModel(&A);
}
END_TEST

START_TEST(rotate_X) {
  Model A;
  loadModel(&A, "models/test.obj");
  float a = 0;
  a = rotateX(&A, 2, a);
  ck_assert_double_eq_tol(A.vertices[3], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[4], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[5], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[6], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[7], 0.034899, 1e-6);
  ck_assert_double_eq_tol(A.vertices[8], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[9], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[10], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[11], -0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[12], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[13], 1.03429, 1e-6);
  ck_assert_double_eq_tol(A.vertices[14], 0.964491, 1e-6);
  ck_assert_double_eq_tol(A.vertices[15], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[16], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[17], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[18], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[19], 0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[20], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[21], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[22], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[23], -0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[24], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[25], 1.03429, 1e-6);
  ck_assert_double_eq_tol(A.vertices[26], 0.964491, 1e-6);
  deleteModel(&A);
}
END_TEST

START_TEST(rotate_Y) {
  Model A;
  loadModel(&A, "models/test.obj");
  float a = 0;
  a = rotateY(&A, 2, a);
  ck_assert_double_eq_tol(A.vertices[3], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[4], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[5], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[6], 0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[7], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[8], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[9], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[10], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[11], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[12], 0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[13], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[14], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[15], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[16], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[17], -0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[18], 1.03429, 1e-6);
  ck_assert_double_eq_tol(A.vertices[19], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[20], 0.964491, 1e-6);
  ck_assert_double_eq_tol(A.vertices[21], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[22], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[23], -0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[24], 1.03429, 1e-6);
  ck_assert_double_eq_tol(A.vertices[25], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[26], 0.964491, 1e-6);
  deleteModel(&A);
}
END_TEST

START_TEST(rotate_Z) {
  Model A;
  loadModel(&A, "models/test.obj");
  float a = 0;
  a = rotateZ(&A, 2, a);
  ck_assert_double_eq_tol(A.vertices[3], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[4], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[5], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[6], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[7], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[8], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[9], 0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[10], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[11], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[12], 0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[13], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[14], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[15], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[16], -0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[17], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[18], 0.999391, 1e-6);
  ck_assert_double_eq_tol(A.vertices[19], -0.0348995, 1e-6);
  ck_assert_double_eq_tol(A.vertices[20], 1, 1e-6);
  ck_assert_double_eq_tol(A.vertices[21], 1.03429, 1e-6);
  ck_assert_double_eq_tol(A.vertices[22], 0.964491, 1e-6);
  ck_assert_double_eq_tol(A.vertices[23], 0, 1e-6);
  ck_assert_double_eq_tol(A.vertices[24], 1.03429, 1e-6);
  ck_assert_double_eq_tol(A.vertices[25], 0.964491, 1e-6);
  ck_assert_double_eq_tol(A.vertices[26], 1, 1e-6);
  deleteModel(&A);
}
END_TEST

Suite *s21_3d_suite(void) {
  Suite *suite;

  suite = suite_create("s21_3d");
  TCase *tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, pars_01);
  tcase_add_test(tcase_core, pars_02);
  tcase_add_test(tcase_core, pars_03);
  tcase_add_test(tcase_core, pars_04);
  tcase_add_test(tcase_core, move_x);
  tcase_add_test(tcase_core, move_y);
  tcase_add_test(tcase_core, move_z);
  tcase_add_test(tcase_core, rotation_x);
  tcase_add_test(tcase_core, rotation_y);
  tcase_add_test(tcase_core, rotation_z);
  tcase_add_test(tcase_core, scale);
  tcase_add_test(tcase_core, incorrect_input);
  tcase_add_test(tcase_core, correct_input);
  tcase_add_test(tcase_core, parser_array);
  tcase_add_test(tcase_core, rotate_X);
  tcase_add_test(tcase_core, rotate_Y);
  tcase_add_test(tcase_core, rotate_Z);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_3d_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}