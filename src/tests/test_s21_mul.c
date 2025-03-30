#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_mul_positive) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 5, 0, 0, 0);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_int_eq(result.bits[0], 50);
}
END_TEST

START_TEST(test_mul_negative) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0x80000000);
  s21_init_decimal(&value_2, 5, 0, 0, 0x80000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_mul_diff_signs) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 5, 0, 0, 0x80000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_mul_diff_scales) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 100, 0, 0, 0x00020000);
  s21_init_decimal(&value_2, 5, 0, 0, 0x00010000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_int_eq(result.bits[0], 500);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_mul_by_zero) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 10, 0, 0, 0);
  s21_init_decimal(&value_2, 0, 0, 0, 0);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_mul_overflow) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 2, 0, 0, 0x00000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 1);
}
END_TEST

START_TEST(test_mul_loss_of_precision) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x00010000);
  s21_init_decimal(&value_2, 3, 0, 0, 0x00010000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 2);
}
END_TEST

START_TEST(test_mul_large_numbers) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x00000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_mul_max_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x001C0000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x0000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 28);
}
END_TEST

START_TEST(test_mul_min_scale) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 123, 0, 0, 0x00000000);
  s21_init_decimal(&value_2, 456, 0, 0, 0x00000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 56088);
  ck_assert_uint_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_mul_loss_of_precision_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 1, 0, 0, 0x00010000);
  s21_init_decimal(&value_2, 3, 0, 0, 0x00020000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 3);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_mul_overflow_negative) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 2, 0, 0, 0x80000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 2);
}
END_TEST

START_TEST(test_mul_diff_signs_and_scales) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x00030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x80020000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 83810205);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

START_TEST(test_mul_near_limits) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 2, 0, 0, 0x00000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 1);
}
END_TEST

START_TEST(test_mul_near_limits_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 2, 0, 0, 0x80000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 2);
}
END_TEST

START_TEST(test_mul_diff_signs_large_values) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 2);
}
END_TEST

START_TEST(test_mul_min_scale_large_values) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
  s21_init_decimal(&value_2, 1, 0, 0, 0x80000000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_mul_diff_signs_and_scales_2) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x80030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x00020000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 83810205);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

START_TEST(test_mul_diff_signs_and_scales_3) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x00030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x80020000);
  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 83810205);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

START_TEST(test_mul_diff_signs_and_scales_4) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value_1, 12345, 0, 0, 0x80030000);
  s21_init_decimal(&value_2, 6789, 0, 0, 0x80020000);

  int mul_result = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(mul_result, 0);
  ck_assert_uint_eq(result.bits[0], 83810205);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 0);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_mul \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_mul_positive);
  tcase_add_test(tc_core, test_mul_negative);
  tcase_add_test(tc_core, test_mul_diff_signs);
  tcase_add_test(tc_core, test_mul_diff_scales);
  tcase_add_test(tc_core, test_mul_by_zero);
  tcase_add_test(tc_core, test_mul_overflow);
  tcase_add_test(tc_core, test_mul_loss_of_precision);
  tcase_add_test(tc_core, test_mul_large_numbers);
  tcase_add_test(tc_core, test_mul_max_scale);
  tcase_add_test(tc_core, test_mul_min_scale);
  tcase_add_test(tc_core, test_mul_loss_of_precision_2);
  tcase_add_test(tc_core, test_mul_overflow_negative);
  tcase_add_test(tc_core, test_mul_diff_signs_and_scales);
  tcase_add_test(tc_core, test_mul_near_limits);
  tcase_add_test(tc_core, test_mul_near_limits_2);
  tcase_add_test(tc_core, test_mul_diff_signs_large_values);
  tcase_add_test(tc_core, test_mul_min_scale_large_values);
  tcase_add_test(tc_core, test_mul_diff_signs_and_scales_2);
  tcase_add_test(tc_core, test_mul_diff_signs_and_scales_3);
  tcase_add_test(tc_core, test_mul_diff_signs_and_scales_4);

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