#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_add_positive) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 20, 0, 0, 0);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 30);
}
END_TEST

START_TEST(test_add_negative) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0x80000000);
  s21_init_decimal(&value_2, 20, 0, 0, 0x80000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 30);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_add_different_signs) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 30, 0, 0, 0);
  s21_init_decimal(&value_2, 20, 0, 0, 1 << 31);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_same_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1111, 0, 0, 0x00030000);
  s21_init_decimal(&value_2, 2222, 0, 0, 0x00030000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 3333);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_add_diff_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1111, 0, 0, 0x00030000);
  s21_init_decimal(&value_2, 2222, 0, 0, 0x00020000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 23331);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_add_overflow) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
  s21_init_decimal(&value_2, 1, 0, 0, 0);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 1);
}
END_TEST

START_TEST(test_add_overflow_minus) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 31);
  s21_init_decimal(&value_2, 1, 0, 0, 1 << 31);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 2);
}
END_TEST

START_TEST(test_add_diff_sign) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};
  s21_decimal expected_result = {{0}};

  s21_init_decimal(&value_1, 123456, 0, 0, 1 << 31);
  s21_init_decimal(&value_2, 654321, 0, 0, 0);

  s21_init_decimal(&expected_result, 654321 - 123456, 0, 0, 0);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);

  ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
  ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
  ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
  ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

START_TEST(test_add_diff_sign_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};
  s21_decimal expected_result = {{0}};

  s21_init_decimal(&value_1, 654321, 0, 0, 1 << 31);
  s21_init_decimal(&value_2, 123456, 0, 0, 0);

  s21_init_decimal(&expected_result, 654321 - 123456, 0, 0, 1 << 31);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);

  ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
  ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
  ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
  ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_add_plus \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_add_positive);
  tcase_add_test(tc_core, test_add_negative);
  tcase_add_test(tc_core, test_add_different_signs);
  tcase_add_test(tc_core, test_add_same_scale);
  tcase_add_test(tc_core, test_add_diff_scale);
  tcase_add_test(tc_core, test_add_overflow);
  tcase_add_test(tc_core, test_add_overflow_minus);
  tcase_add_test(tc_core, test_add_diff_sign);
  tcase_add_test(tc_core, test_add_diff_sign_2);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_decimal_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}