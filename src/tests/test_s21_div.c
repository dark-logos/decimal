#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_div_by_zero) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 10, 0, 0, 0);
  s21_init_decimal(&divisor, 0, 0, 0, 0);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 3);
}
END_TEST

START_TEST(test_div_positive) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0);
  s21_init_decimal(&divisor, 5, 0, 0, 0);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 20);
}
END_TEST

START_TEST(test_div_negative) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0x80000000);
  s21_init_decimal(&divisor, 5, 0, 0, 0x80000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_div_diff_signs) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0);
  s21_init_decimal(&divisor, 5, 0, 0, 0x80000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_div_diff_scales) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0x00020000);
  s21_init_decimal(&divisor, 5, 0, 0, 0x00010000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

START_TEST(test_div_overflow) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&divisor, 1, 0, 0, 0x00010000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 1);
}
END_TEST

START_TEST(test_div_zero_by_number) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 0, 0, 0, 0);
  s21_init_decimal(&divisor, 5, 0, 0, 0);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_div_large_by_small) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&divisor, 1, 0, 0, 0x00000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_div_by_self) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 123456, 0, 0, 0x00010000);
  s21_init_decimal(&divisor, 123456, 0, 0, 0x00010000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_div_by_self_1) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 123456, 0, 0, 0x00000000);
  s21_init_decimal(&divisor, 123456, 0, 0, 0x00000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_div_diff_scales_2) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 123456, 0, 0, 0x00020000);
  s21_init_decimal(&divisor, 123456, 0, 0, 0x00030000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

START_TEST(test_div_negative_result) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0x80000000);
  s21_init_decimal(&divisor, 5, 0, 0, 0x00000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_div_by_one) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 123456, 0, 0, 0x00020000);
  s21_init_decimal(&divisor, 1, 0, 0, 0x00000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 123456);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 2);
}
END_TEST

START_TEST(test_div_small_by_large) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 1, 0, 0, 0x00010000);
  s21_init_decimal(&divisor, 100, 0, 0, 0x00000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_div_overflow_2) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&divisor, 0x00000001, 0x00000000, 0x00000000, 0x00010000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 1);
}
END_TEST

START_TEST(test_div_negative_dividend) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0x80000000);
  s21_init_decimal(&divisor, 5, 0, 0, 0x00000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_div_negative_divisor) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 100, 0, 0, 0x00000000);
  s21_init_decimal(&divisor, 5, 0, 0, 0x80000000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_div_overflow_minus) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&divisor, 1, 0, 0, 0x00010000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 2);
}
END_TEST

START_TEST(test_div_large_scale) {
  s21_decimal dividend = {{0}};
  s21_decimal divisor = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&dividend, 123456789, 0, 0, 0x00070000);
  s21_init_decimal(&divisor, 123456789, 0, 0, 0x00070000);

  int div_result = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(div_result, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_add \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_div_by_zero);
  tcase_add_test(tc_core, test_div_positive);
  tcase_add_test(tc_core, test_div_negative);
  tcase_add_test(tc_core, test_div_diff_signs);
  tcase_add_test(tc_core, test_div_diff_scales);
  tcase_add_test(tc_core, test_div_overflow);
  tcase_add_test(tc_core, test_div_zero_by_number);
  tcase_add_test(tc_core, test_div_large_by_small);
  tcase_add_test(tc_core, test_div_by_self);
  tcase_add_test(tc_core, test_div_by_self_1);
  tcase_add_test(tc_core, test_div_diff_scales_2);
  tcase_add_test(tc_core, test_div_negative_result);
  tcase_add_test(tc_core, test_div_by_one);
  tcase_add_test(tc_core, test_div_small_by_large);
  tcase_add_test(tc_core, test_div_overflow_2);
  tcase_add_test(tc_core, test_div_negative_dividend);
  tcase_add_test(tc_core, test_div_negative_divisor);
  tcase_add_test(tc_core, test_div_large_scale);
  tcase_add_test(tc_core, test_div_overflow_minus);

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