#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_round_positive) {
  s21_decimal value = {{345, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_negative) {
  s21_decimal value = {{345, 0, 0, 0x80020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_round_zero_scale) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_fraction_less_than_half) {
  s21_decimal value = {{349, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_fraction_greater_than_half) {
  s21_decimal value = {{351, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_exact_half_even) {
  s21_decimal value = {{350, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_exact_half_odd) {
  s21_decimal value = {{45, 0, 0, 0x00010000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_negative_fraction_greater_than_half) {
  s21_decimal value = {{351, 0, 0, 0x80020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_round_negative_fraction_less_than_half) {
  s21_decimal value = {{349, 0, 0, 0x80020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_round_negative_exact_half_even) {
  s21_decimal value = {{361, 0, 0, 0x80020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_round_negative_exact_half_odd) {
  s21_decimal value = {{450, 0, 0, 0x80020000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_round_zero) {
  s21_decimal value = {{0, 0, 0, 0x00050000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_large_scale) {
  s21_decimal value = {{123456789, 0, 0, 0x00050000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1235);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_null_result) {
  s21_decimal value = {{345, 0, 0, 0x00010000}};
  int status = s21_round(value, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_round_large_scale_bits012) {
  s21_decimal value = {{567, 0, 1000, 0x00030000}};
  s21_decimal result = {{0}};

  int status = s21_round(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 1);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_round \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_round_positive);
  tcase_add_test(tc_core, test_s21_round_negative);
  tcase_add_test(tc_core, test_s21_round_zero_scale);
  tcase_add_test(tc_core, test_s21_round_fraction_less_than_half);
  tcase_add_test(tc_core, test_s21_round_fraction_greater_than_half);
  tcase_add_test(tc_core, test_s21_round_exact_half_even);
  tcase_add_test(tc_core, test_s21_round_exact_half_odd);
  tcase_add_test(tc_core, test_s21_round_negative_fraction_greater_than_half);
  tcase_add_test(tc_core, test_s21_round_negative_fraction_less_than_half);
  tcase_add_test(tc_core, test_s21_round_negative_exact_half_even);
  tcase_add_test(tc_core, test_s21_round_negative_exact_half_odd);
  tcase_add_test(tc_core, test_s21_round_zero);
  tcase_add_test(tc_core, test_s21_round_large_scale);
  tcase_add_test(tc_core, test_s21_round_null_result);
  tcase_add_test(tc_core, test_s21_round_large_scale_bits012);

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