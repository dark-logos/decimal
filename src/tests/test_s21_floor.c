#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_floor_1) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_floor_2) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 124);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_floor_3) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  value.bits[3] = 29 << 16;
  ck_assert_int_eq(s21_floor(value, &result), 1);
}
END_TEST

START_TEST(test_floor_4) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_floor_5) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_add \nTESTS:");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_floor_1);
  tcase_add_test(tc_core, test_floor_2);
  tcase_add_test(tc_core, test_floor_3);
  tcase_add_test(tc_core, test_floor_4);
  tcase_add_test(tc_core, test_floor_5);

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