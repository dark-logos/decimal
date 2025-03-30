#include "s21_decimal.h"

#define S21_POSITIVE 0
#define S21_NEGATIVE 1
#define MINUSE 0x80000000

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = S21_POSITIVE;
  if (!result || !s21_checking_decimal_for_correct(value)) {
    flag = S21_NEGATIVE;
  } else {
    int scale = getScale(value);
    int sign = getSign(value);

    if (scale == 0) {
      *result = value;
    } else if (sign == 0) {
      s21_truncate(value, result);
    } else if (sign == 1) {
      s21_decimal minus_one = {{1, 0, 0, MINUSE}};
      s21_truncate(value, result);
      s21_add(*result, minus_one, result);
    }
  }
  return flag;
}

int s21_checking_decimal_for_correct(s21_decimal num) {
  int flag = 1;

  if ((num.bits[3] & 0x0000FFFF) != 0) {
    flag = 0;
  }
  int exponent = (num.bits[3] >> 16) & 0xFF;
  ;
  if (exponent > 28) {
    flag = 0;
  }
  if ((num.bits[3] & 0x7F000000) != 0) {
    flag = 0;
  }

  return flag;
}
