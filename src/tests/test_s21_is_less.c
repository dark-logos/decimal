#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_is_less_1) {
  s21_decimal num1 = {{12345, 0, 0, 0x00020000}};
  s21_decimal num2 = {{67890, 0, 0, 0x00050000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_s21_is_less_2) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal num1 = {{2, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0x80000000}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal num1 = {{1, 0, 0, 0x00010000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_s21_is_less_8) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_9) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_s21_is_less_10) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_11) {
  s21_decimal num1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_s21_is_less_12) {
  s21_decimal num1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_13) {
  s21_decimal num1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  s21_decimal num2 = {{0x12C4B1, 0x0, 0x0, 0x60000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_14) {
  s21_decimal num1 = {{0xA, 0x0, 0x0, 0x10000}};
  s21_decimal num2 = {{0x1, 0x0, 0x0, 0x80000000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_15) {
  s21_decimal num1 = {{0xA, 0x0, 0x0, 0x10000}};
  s21_decimal num2 = {{0x12C4B1, 0x0, 0x0, 0x60000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_16) {
  s21_decimal num1 = {{0xA, 0x0, 0x0, 0x10000}};
  s21_decimal num2 = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_17) {
  s21_decimal num1 = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x120000}};
  s21_decimal num2 = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x120000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_18) {
  s21_decimal num1 = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_decimal num2 = {
      {0xA, 0x0, 0x0, 0x0010000}};  // 0.0000000000000000000000000001
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_19) {
  s21_decimal num1 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal num2 = {{0x0, 0x0, 0x0, 0x8000000}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_20) {
  s21_decimal num1 = {{0x0, 0x0, 0x0, 0x0012000}};
  s21_decimal num2 = {{0x0, 0x0, 0x0, 0x0}};
  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s = suite_create("s21_is_less \nTESTS:");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_is_less_1);
  tcase_add_test(tc_core, test_s21_is_less_2);
  tcase_add_test(tc_core, test_s21_is_less_3);
  tcase_add_test(tc_core, test_s21_is_less_4);
  tcase_add_test(tc_core, test_s21_is_less_5);
  tcase_add_test(tc_core, test_s21_is_less_6);
  tcase_add_test(tc_core, test_s21_is_less_7);
  tcase_add_test(tc_core, test_s21_is_less_8);
  tcase_add_test(tc_core, test_s21_is_less_9);
  tcase_add_test(tc_core, test_s21_is_less_10);
  tcase_add_test(tc_core, test_s21_is_less_11);
  tcase_add_test(tc_core, test_s21_is_less_12);
  tcase_add_test(tc_core, test_s21_is_less_13);
  tcase_add_test(tc_core, test_s21_is_less_14);
  tcase_add_test(tc_core, test_s21_is_less_15);
  tcase_add_test(tc_core, test_s21_is_less_16);
  tcase_add_test(tc_core, test_s21_is_less_17);
  tcase_add_test(tc_core, test_s21_is_less_18);
  tcase_add_test(tc_core, test_s21_is_less_19);
  tcase_add_test(tc_core, test_s21_is_less_20);

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