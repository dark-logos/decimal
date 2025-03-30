#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_is_less_1) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_s21_is_less_2) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal num1 = {{2, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0x80000000}};

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal num1 = {{1, 0, 0, 0x00010000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal num1 = {{1, 0, 0, 0x80000000}};
  s21_decimal num2 = {{1, 0, 0, 0}};

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s = suite_create("s21_is_greater \nTESTS:");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_is_less_1);
  tcase_add_test(tc_core, test_s21_is_less_2);
  tcase_add_test(tc_core, test_s21_is_less_3);
  tcase_add_test(tc_core, test_s21_is_less_4);
  tcase_add_test(tc_core, test_s21_is_less_5);
  tcase_add_test(tc_core, test_s21_is_less_6);
  tcase_add_test(tc_core, test_s21_is_less_7);
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
