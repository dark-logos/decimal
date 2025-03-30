#include "s21_decimal.h"
int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (getScale(value) > 28) flag = 1;
  s21_decimal negative_one = {{1, 0, 0, 1 << 31}};
  int mul_flag = s21_mul(value, negative_one, result);
  if (mul_flag != 0) flag = 1;
  return flag;
}