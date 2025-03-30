#include "s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int result = 0;

  if (s21_check_zero(value1) && s21_check_zero(value2)) {
    result = 0;
  } else {
    int sign1 = getSign(value1);
    int sign2 = getSign(value2);

    if (sign1 != sign2) {
      result = sign1 && !sign2;
    } else {
      int scale1 = getScale(value1);
      int scale2 = getScale(value2);
      s21_decimal *small_scale = (scale1 < scale2) ? &value1 : &value2;
      int scale_diff = abs(scale1 - scale2);

      while (scale_diff-- > 0 && !multiply_by_10(small_scale)) {
        (scale1 < scale2) ? scale1++ : scale2++;
      }

      if (scale1 != scale2) {
        if (scale1 > scale2) {
          value1 = scaleDown(value1, scale1 - scale2);
        } else {
          value2 = scaleDown(value2, scale2 - scale1);
        }
      }
      result =
          sign1 ? compareBits(value2, value1) : compareBits(value1, value2);
    }
  }

  return result;
}