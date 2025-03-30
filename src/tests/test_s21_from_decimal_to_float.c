#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_from_decimal_to_float_1) {
  float num1 = 10.5;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_2) {
  float num1 = 0.0;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_3) {
  float num1 = -123.45;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_4) {
  float num1 = 789.123;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_5) {
  float num1 = 1.0;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_6) {
  float num1 = -0.001;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST
START_TEST(test_from_decimal_to_float_7) {
  float num1 = 3.141592;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_8) {
  float num1 = -0.000001;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_9) {
  float num1 = 999999.999;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_10) {
  float num1 = -999999.999;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_11) {
  float num1 = 0.000001;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_12) {
  float num1 = -0.000001;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_13) {
  float num1 = 1000000.0;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_14) {
  float num1 = -1000000.0;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_15) {
  float num1 = 0.1234567;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_16) {
  float num1 = -0.1234567;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_17) {
  float num1 = 0.0001;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_18) {
  float num1 = -0.0001;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_19) {
  float num1 = 12.2e5;
  float num2 = 0;
  s21_decimal value1 = {0};
  int res = s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_int_eq(res, 0);
  ck_assert_float_eq(num2, num1);
}
END_TEST

START_TEST(test_from_decimal_to_float_20) {
  float num1 = -1234.1;
  float num2 = 0;
  s21_decimal value1 = {0};
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_float_eq(num2, num1);
}
END_TEST
START_TEST(test_from_decimal_to_float_21) {
  float num1 = 1.23e5;
  float num2 = 0;
  s21_decimal value1 = {0};
  int res = s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_int_eq(res, 0);
  ck_assert_float_eq(num2, num1);
  ck_assert_float_eq_tol(num1, num2, 1e-6);
}
END_TEST

START_TEST(test_from_decimal_to_float_22) {
  float num1 = 0;
  float num2 = 0;
  s21_decimal value1 = {0};
  num1 = s21_from_float_to_decimal(num1, NULL);
  num2 = s21_from_decimal_to_float(value1, NULL);
  ck_assert_int_eq(num1, 1);
  ck_assert_int_eq(num2, 1);
}
END_TEST
START_TEST(test_from_decimal_to_float_23) {
  float num1 = 4.56e7;
  float num2 = 0;
  s21_decimal value1 = {0};
  int result = s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_float(value1, &num2);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq_tol(num1, num2, 1e-6);
}
END_TEST
START_TEST(test_from_decimal_to_float_24) {
  float num1 = INFINITY;
  s21_decimal value1 = {0};
  int result = s21_from_float_to_decimal(num1, &value1);
  ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_from_decimal_to_float_25) {
  s21_decimal num1 = {{0x1, 0x0, 0x0, 0xA0000}};
  int num2 = 0;
  float result = 0;
  num2 = s21_from_decimal_to_float(num1, &result);
  ck_assert_int_eq(num2, 0);
  ck_assert_float_eq(result, 7.09187e-10);
}
END_TEST

Suite *from_to_int_suite(void) {
  Suite *s = suite_create("s21_from_decimal_to_float \nTESTS:");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_from_decimal_to_float_1);
  tcase_add_test(tc_core, test_from_decimal_to_float_2);
  tcase_add_test(tc_core, test_from_decimal_to_float_3);
  tcase_add_test(tc_core, test_from_decimal_to_float_4);
  tcase_add_test(tc_core, test_from_decimal_to_float_5);
  tcase_add_test(tc_core, test_from_decimal_to_float_6);
  tcase_add_test(tc_core, test_from_decimal_to_float_7);
  tcase_add_test(tc_core, test_from_decimal_to_float_8);
  tcase_add_test(tc_core, test_from_decimal_to_float_9);
  tcase_add_test(tc_core, test_from_decimal_to_float_10);
  tcase_add_test(tc_core, test_from_decimal_to_float_11);
  tcase_add_test(tc_core, test_from_decimal_to_float_12);
  tcase_add_test(tc_core, test_from_decimal_to_float_13);
  tcase_add_test(tc_core, test_from_decimal_to_float_14);
  tcase_add_test(tc_core, test_from_decimal_to_float_15);
  tcase_add_test(tc_core, test_from_decimal_to_float_16);
  tcase_add_test(tc_core, test_from_decimal_to_float_17);
  tcase_add_test(tc_core, test_from_decimal_to_float_18);
  tcase_add_test(tc_core, test_from_decimal_to_float_19);
  tcase_add_test(tc_core, test_from_decimal_to_float_20);
  tcase_add_test(tc_core, test_from_decimal_to_float_21);
  tcase_add_test(tc_core, test_from_decimal_to_float_22);
  tcase_add_test(tc_core, test_from_decimal_to_float_23);
  tcase_add_test(tc_core, test_from_decimal_to_float_24);
  tcase_add_test(tc_core, test_from_decimal_to_float_25);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s = from_to_int_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
