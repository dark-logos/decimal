#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_sub_positive) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 5, 0, 0, 0);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_sub_negative) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0x80000000);
  s21_init_decimal(&value_2, 5, 0, 0, 0x80000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_diff_signs) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 5, 0, 0, 0x80000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(test_sub_diff_scales) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 100, 0, 0, 0x00020000);
  s21_init_decimal(&value_2, 5, 0, 0, 0x00010000);
  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 1);
}
END_TEST

START_TEST(test_sub_zero) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 0, 0, 0, 0);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_sub_from_zero) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0, 0, 0, 0);
  s21_init_decimal(&value_2, 5, 0, 0, 0);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_overflow) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x80000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 1);
}
END_TEST

START_TEST(test_sub_overflow_minus) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x00000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 2);
}
END_TEST

START_TEST(test_sub_loss_of_precision) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x00010000);
  s21_init_decimal(&value_2, 3, 0, 0, 0x00020000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 7);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 2);
}
END_TEST

START_TEST(test_sub_diff_signs_and_scales_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x80030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x00020000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 80235);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_sub_diff_signs_and_scales_3) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x00030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x80020000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 80235);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 0);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_sub_diff_signs_and_scales_4) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x80030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x80020000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 55545);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 0);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_sub_max_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x001C0000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x001C0000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

START_TEST(test_sub_min_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 123, 0, 0, 0x00000000);
  s21_init_decimal(&value_2, 456, 0, 0, 0x00000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 333);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_loss_of_precision_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x00010000);
  s21_init_decimal(&value_2, 3, 0, 0, 0x00020000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], 7);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 2);
}
END_TEST

START_TEST(test_sub_diff_signs_large_values) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 1);
}
END_TEST

START_TEST(test_sub_diff_signs_large_values_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&value_2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 2);
}
END_TEST

START_TEST(test_sub_diff_signs_large_values_3) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x80000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 1);
}
END_TEST

START_TEST(test_sub_diff_signs_large_values_4) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x00000000);

  int sub_result = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(sub_result, 2);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sub \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sub_positive);
  tcase_add_test(tc_core, test_sub_negative);
  tcase_add_test(tc_core, test_sub_diff_signs);
  tcase_add_test(tc_core, test_sub_diff_scales);
  tcase_add_test(tc_core, test_sub_zero);
  tcase_add_test(tc_core, test_sub_from_zero);
  tcase_add_test(tc_core, test_sub_overflow);
  tcase_add_test(tc_core, test_sub_overflow_minus);
  tcase_add_test(tc_core, test_sub_loss_of_precision);
  tcase_add_test(tc_core, test_sub_diff_signs_and_scales_2);
  tcase_add_test(tc_core, test_sub_diff_signs_and_scales_3);
  tcase_add_test(tc_core, test_sub_diff_signs_and_scales_4);
  tcase_add_test(tc_core, test_sub_max_scale);
  tcase_add_test(tc_core, test_sub_min_scale);
  tcase_add_test(tc_core, test_sub_loss_of_precision_2);
  tcase_add_test(tc_core, test_sub_diff_signs_large_values);
  tcase_add_test(tc_core, test_sub_diff_signs_large_values_2);
  tcase_add_test(tc_core, test_sub_diff_signs_large_values_3);
  tcase_add_test(tc_core, test_sub_diff_signs_large_values_4);

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