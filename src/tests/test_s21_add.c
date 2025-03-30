#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_add_zero) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_add_zero_positive) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_2, 123, 0, 0, 0);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_add_zero_negative) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_2, 123, 0, 0, 0x80000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_add_large_positive) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
  s21_init_decimal(&value_2, 1, 0, 0, 0);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 1);
}
END_TEST

START_TEST(test_add_large_negative) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x80000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 2);
}
END_TEST

START_TEST(test_add_diff_scale_1) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x00050000);
  s21_init_decimal(&value_2, 123, 0, 0, 0x00020000);
  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 135345);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

START_TEST(test_add_diff_scale_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 123, 0, 0, 0x00020000);
  s21_init_decimal(&value_2, 12345, 0, 0, 0x00050000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 135345);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

START_TEST(test_add_same_scale_overflow) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x00010000);
  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
}
END_TEST

START_TEST(test_add_diff_sign_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x00030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x80020000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 55545);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_add_diff_sign_scale_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 6789, 0, 0, 0x80020000);
  s21_init_decimal(&value_2, 12345, 0, 0, 0x00030000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 55545);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_add_max_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x001C0000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x001C0000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 28);
}
END_TEST

START_TEST(test_add_min_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 123, 0, 0, 0x00000000);
  s21_init_decimal(&value_2, 456, 0, 0, 0x00000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 579);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

START_TEST(test_add_diff_sign_zero_result) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 123, 0, 0, 0x00000000);
  s21_init_decimal(&value_2, 123, 0, 0, 0x80000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_diff_sign_zero_result_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 123, 0, 0, 0x80000000);
  s21_init_decimal(&value_2, 123, 0, 0, 0x00000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_diff_sign_large_values) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_diff_sign_large_values_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&value_2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_diff_sign_large_values_3) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x80000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_diff_sign_large_values_4) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x00000000);

  int add_result = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(add_result, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_add \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_add_zero);
  tcase_add_test(tc_core, test_add_zero_positive);
  tcase_add_test(tc_core, test_add_zero_negative);
  tcase_add_test(tc_core, test_add_large_positive);
  tcase_add_test(tc_core, test_add_large_negative);
  tcase_add_test(tc_core, test_add_diff_scale_1);
  tcase_add_test(tc_core, test_add_diff_scale_2);
  tcase_add_test(tc_core, test_add_same_scale_overflow);
  tcase_add_test(tc_core, test_add_diff_sign_scale);
  tcase_add_test(tc_core, test_add_diff_sign_scale_2);
  tcase_add_test(tc_core, test_add_max_scale);
  tcase_add_test(tc_core, test_add_min_scale);
  tcase_add_test(tc_core, test_add_diff_sign_zero_result);
  tcase_add_test(tc_core, test_add_diff_sign_zero_result_2);
  tcase_add_test(tc_core, test_add_diff_sign_large_values);
  tcase_add_test(tc_core, test_add_diff_sign_large_values_2);
  tcase_add_test(tc_core, test_add_diff_sign_large_values_3);
  tcase_add_test(tc_core, test_add_diff_sign_large_values_4);

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