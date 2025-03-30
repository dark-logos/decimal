#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_truncate_1) {
  float num1 = 1.5;
  s21_decimal num2 = {0};
  s21_decimal result1 = {0};
  int num3 = 1;
  s21_decimal result2 = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result1);
  s21_from_int_to_decimal(num3, &result2);

  ck_assert_int_eq(result1.bits[0], result2.bits[0]);
  ck_assert_int_eq(result1.bits[1], result2.bits[1]);
  ck_assert_int_eq(result1.bits[2], result2.bits[2]);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  float num1 = -1.5;
  s21_decimal num2 = {0};
  s21_decimal result1 = {0};
  int num3 = -1;
  s21_decimal result2 = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result1);
  s21_from_int_to_decimal(num3, &result2);

  ck_assert_int_eq(result1.bits[0], result2.bits[0]);
  ck_assert_int_eq(result1.bits[1], result2.bits[1]);
  ck_assert_int_eq(result1.bits[2], result2.bits[2]);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  float num1 = 0.0;
  s21_decimal num2 = {0};
  s21_decimal result1 = {0};
  int num3 = 0;
  s21_decimal result2 = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result1);
  s21_from_int_to_decimal(num3, &result2);

  ck_assert_int_eq(result1.bits[0], result2.bits[0]);
  ck_assert_int_eq(result1.bits[1], result2.bits[1]);
  ck_assert_int_eq(result1.bits[2], result2.bits[2]);
}
END_TEST

START_TEST(test_s21_truncate_6) {
  float num1 = 0.000001;
  s21_decimal num2 = {0};
  s21_decimal result1 = {0};
  int num3 = 0;
  s21_decimal result2 = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result1);
  s21_from_int_to_decimal(num3, &result2);

  ck_assert_int_eq(result1.bits[0], result2.bits[0]);
  ck_assert_int_eq(result1.bits[1], result2.bits[1]);
  ck_assert_int_eq(result1.bits[2], result2.bits[2]);
}
END_TEST

START_TEST(test_s21_truncate_7) {
  float num1 = 0.999999;
  s21_decimal num2 = {0};
  s21_decimal result1 = {0};
  int num3 = 0;
  s21_decimal result2 = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result1);
  s21_from_int_to_decimal(num3, &result2);

  ck_assert_int_eq(result1.bits[0], result2.bits[0]);
  ck_assert_int_eq(result1.bits[1], result2.bits[1]);
  ck_assert_int_eq(result1.bits[2], result2.bits[2]);
}
END_TEST

START_TEST(test_s21_truncate_9) {
  float num1 = 42.0;
  s21_decimal num2 = {0};
  s21_decimal result1 = {0};
  int num3 = 42;
  s21_decimal result2 = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result1);
  s21_from_int_to_decimal(num3, &result2);

  ck_assert_int_eq(result1.bits[0], result2.bits[0]);
  ck_assert_int_eq(result1.bits[1], result2.bits[1]);
  ck_assert_int_eq(result1.bits[2], result2.bits[2]);
}
END_TEST

START_TEST(test_s21_truncate_12) {
  float num1 = 123.456;
  s21_decimal num2 = {0};
  s21_decimal result = {0};

  s21_from_float_to_decimal(num1, &num2);
  s21_truncate(num2, &result);

  ck_assert_int_eq(getScale(result), 0);
}
END_TEST

START_TEST(test_truncate_positive_1) {
  s21_decimal value = {{123456, 0, 0, 3 << 16}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_truncate_positive_2) {
  s21_decimal value = {{0, 1, 0, 0x00030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 4294967);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_truncate_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_truncate_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_truncate_negative_1) {
  s21_decimal value = {{323476, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 323);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_truncate_negative_2) {
  s21_decimal value = {{4135, 0, 0, 1}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 1);
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s = suite_create("s21_truncate  \nTESTS:");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_truncate_1);
  tcase_add_test(tc_core, test_s21_truncate_2);
  tcase_add_test(tc_core, test_s21_truncate_3);
  tcase_add_test(tc_core, test_s21_truncate_6);
  tcase_add_test(tc_core, test_s21_truncate_7);
  tcase_add_test(tc_core, test_s21_truncate_9);
  tcase_add_test(tc_core, test_s21_truncate_12);
  tcase_add_test(tc_core, test_truncate_positive_1);
  tcase_add_test(tc_core, test_truncate_positive_2);
  tcase_add_test(tc_core, test_truncate_max);
  tcase_add_test(tc_core, test_truncate_min);
  tcase_add_test(tc_core, test_truncate_negative_2);
  tcase_add_test(tc_core, test_truncate_negative_1);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int res_num;
  Suite *s = decimal_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  res_num = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (res_num == 0) ? 0 : 1;
}