#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *restrict dst) {
  s21_conversion_result code = S21_CONVERSION_OK;
  if (unlikely(dst == NULL)) {
    return S21_CONVERSION_ERROR;
  }
  double tmp = 0.0;
  for (int i = 0; i < 3; i++) {
    tmp += ldexp((double)src.bits[i],
                 i * 32);  // Выполняет умножение на степень двойки аппаратно,
    // используя внутренние инструкции процессора (FPU) со скоростью выполнения
    // o(1), вместо o(n) при побитовом сдвиге, что особенно выделяется при
    // возведении в степень 96, o(1) vs 0(96)
  }
  unsigned int scale = getScale(src);
  unsigned int divisor = 1;
  if (scale <= 9) {  // убрать if
    static const unsigned int pow10_lookup[10] = {
        1,      10,      100,      1000,      10000,
        100000, 1000000, 10000000, 100000000, 1000000000};
    divisor = pow10_lookup[scale];
  } else {
    divisor = (unsigned int)pow(10, scale);
  }
  tmp /= divisor;

  int sign = 1 - 2 * getSign(src);
  tmp *= sign;

  *dst = (float)tmp;
  return code;
}