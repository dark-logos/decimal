#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_negate_positive) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_negate_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_negative_1) {
  s21_decimal value = {{123, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_negative_2) {
  s21_decimal value = {{123956, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  value.bits[3] = 29 << 16;
  ck_assert_int_eq(s21_negate(value, &result), 1);
}

END_TEST

START_TEST(test_negate_negative_3) {
  s21_decimal value = {{123956, 0, 0, 0x1000}};
  s21_decimal result = {{0}};
  value.bits[3] = 29 << 16;
  ck_assert_int_eq(s21_negate(value, &result), 1);
}
END_TEST

START_TEST(test_negate_negative_4) {
  s21_decimal value = {{123956, 0, 0, 0x7F000004}};
  s21_decimal result = {{0}};
  value.bits[3] = 29 << 16;
  ck_assert_int_eq(s21_negate(value, &result), 1);
}
END_TEST

START_TEST(test_negate_positive_1) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 123, 0, 0, 0);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 123, 0, 0, 0x80000000);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_zero_1) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 0, 0, 0, 0);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_max_value) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_negate_min_value) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_fractional) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 12345, 0, 0, 0x00030000);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 3);
}
END_TEST

START_TEST(test_negate_max_scale) {
  s21_decimal value = {{0}};
  s21_decimal result = {{0}};

  s21_init_decimal(&value, 1, 0, 0, 0x001C0000);

  int negate_result = s21_negate(value, &result);

  ck_assert_int_eq(negate_result, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 28);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_negete \nTESTS:");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_negate_positive);
  tcase_add_test(tc_core, test_negate_zero);
  tcase_add_test(tc_core, test_negate_max);
  tcase_add_test(tc_core, test_negate_min);

  tcase_add_test(tc_core, test_negate_negative_1);
  tcase_add_test(tc_core, test_negate_negative_2);
  tcase_add_test(tc_core, test_negate_negative_3);
  tcase_add_test(tc_core, test_negate_negative_4);

  tcase_add_test(tc_core, test_negate_positive_1);
  tcase_add_test(tc_core, test_negate_negative);
  tcase_add_test(tc_core, test_negate_zero_1);
  tcase_add_test(tc_core, test_negate_max_value);
  tcase_add_test(tc_core, test_negate_min_value);
  tcase_add_test(tc_core, test_negate_fractional);
  tcase_add_test(tc_core, test_negate_max_scale);

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