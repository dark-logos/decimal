#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = getScale(value), sign = getSign(value), flag;
  if (scale > 28 || scale < 0) return 1;
  if (!result || !s21_checking_decimal_for_correct(value)) {
    return 1;
  }
  if (scale == 0) {
    *result = value;
    //return 0;
  } else {
    s21_decimal one = {{1, 0, 0, 0}}, remainder = {{0, 0, 0, 0}};
    s21_big_decimal quotient = {{0, 0, 0, 0, 0, 0, 0, 0}};

    zero_scale(&value, &one, scale, &flag);
    s21_div_int(value, one, &quotient, &remainder);

    big_to_normal(result, quotient, sign, &flag);
    set_techInfo(sign, 0, result);
  }
  return 0;
}