#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"

START_TEST(test_from_int_to_decimal_1) {
  int num1 = 12;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_2) {
  int num1 = -2147483646;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_3) {
  int num1 = 2147483647;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_4) {
  int num1 = -2147483648;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_5) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_6) {
  int num1 = 123;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_7) {
  int num1 = 999999;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_8) {
  int num1 = -999999;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_9) {
  int num1 = 1111111111;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST
START_TEST(test_from_int_to_decimal_10) {
  int num1 = 222222222;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_11) {
  int num1 = -222222222;
  int num2 = 0;
  s21_decimal value1 = {0};
  s21_from_int_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num1);
}
END_TEST

START_TEST(test_from_int_to_decimal_12) {
  int num1 = 52;
  int num2 = 0;
  num2 = s21_from_int_to_decimal(num1, NULL);
  ck_assert_int_eq(num2, 1);
}
END_TEST
START_TEST(test_from_int_to_decimal_13) {
  int num1 = 52;
  int num2 = 0;
  s21_decimal value1 = {0};
  num2 = s21_from_int_to_decimal(num1, &value1);
  ck_assert_int_eq(num2, 0);
}
END_TEST
START_TEST(test_from_int_to_decimal_14) {
  //    int num1 = -222222222;
  int num2 = 0;
  s21_decimal value1 = {0};
  // s21_from_int_to_decimal(num1, &value1);
  num2 = s21_from_decimal_to_int(value1, NULL);
  ck_assert_int_eq(num2, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_15) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal value1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  num2 = s21_from_decimal_to_int(value1, &num1);
  ck_assert_int_eq(num2, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_16) {
  s21_decimal num1 = {{0x1, 0x0, 0x0, 0xA0000}};
  int num2 = 0;
  int result = 0;
  num2 = s21_from_decimal_to_int(num1, &result);
  ck_assert_int_eq(num2, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_17) {
  float num1 = 123.123;
  int num2 = 0;
  s21_decimal value1 = {0};
  int num3 = 123;
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num3);
}
END_TEST

START_TEST(test_from_int_to_decimal_18) {
  float num1 = 1.9821374;
  int num2 = 0;
  s21_decimal value1 = {0};
  int num3 = 1;
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num3);
}
END_TEST

START_TEST(test_from_int_to_decimal_19) {
  float num1 = 12.9821374;
  int num2 = 0;
  s21_decimal value1 = {0};
  int num3 = 12;
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num3);
}
END_TEST

START_TEST(test_from_int_to_decimal_20) {
  float num1 = 21474836.9821374;
  int test = num1;
  printf("\n\n\n%d\n\n\n", test);
  int num2 = 0;
  s21_decimal value1 = {0};
  int num3 = 21474836;
  s21_from_float_to_decimal(num1, &value1);
  s21_from_decimal_to_int(value1, &num2);
  ck_assert_int_eq(num2, num3);
}
END_TEST

Suite *from_to_int_suite(void) {
  Suite *s = suite_create("s21_from_to_int \nTESTS:");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_from_int_to_decimal_1);
  tcase_add_test(tc_core, test_from_int_to_decimal_2);
  tcase_add_test(tc_core, test_from_int_to_decimal_3);
  tcase_add_test(tc_core, test_from_int_to_decimal_4);
  tcase_add_test(tc_core, test_from_int_to_decimal_5);
  tcase_add_test(tc_core, test_from_int_to_decimal_6);
  tcase_add_test(tc_core, test_from_int_to_decimal_7);
  tcase_add_test(tc_core, test_from_int_to_decimal_8);
  tcase_add_test(tc_core, test_from_int_to_decimal_9);
  tcase_add_test(tc_core, test_from_int_to_decimal_10);
  tcase_add_test(tc_core, test_from_int_to_decimal_11);
  tcase_add_test(tc_core, test_from_int_to_decimal_12);
  tcase_add_test(tc_core, test_from_int_to_decimal_13);
  tcase_add_test(tc_core, test_from_int_to_decimal_14);
  tcase_add_test(tc_core, test_from_int_to_decimal_15);
  tcase_add_test(tc_core, test_from_decimal_to_int_16);
  tcase_add_test(tc_core, test_from_int_to_decimal_17);
  tcase_add_test(tc_core, test_from_int_to_decimal_18);
  tcase_add_test(tc_core, test_from_int_to_decimal_19);
  tcase_add_test(tc_core, test_from_int_to_decimal_20);
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
