#include "s21_decimal.h"

int s21_div(s21_decimal dividend, s21_decimal divisor, s21_decimal *result) {
  int flag = 0;
  s21_decimal one = {{1, 0, 0, 0}}, zero = {{0, 0, 0, 0}};
  s21_big_decimal big_result;
  memset(big_result.bits, 0, sizeof(big_result.bits));
  memset(result->bits, 0, sizeof(result->bits));
  if (s21_is_equal(divisor, zero)) return 3;
  ScalesAndSigns ScalesAndSigns;
  ScalesAndSigns.resultSign = getSign(dividend) ^ getSign(divisor);
  ScalesAndSigns.resultScale = 0;
  int maxScale = findMaxScale(dividend, divisor);
  if (!s21_is_equal(divisor, one))
    zero_scale(&dividend, &divisor, maxScale, &flag);
  if (s21_is_equal(dividend, divisor)) {
    big_result.bits[0]++;
  } else {
    dividend.bits[3] = 0;
    divisor.bits[3] = 0;
    s21_div_float(dividend, divisor, &big_result, &ScalesAndSigns.resultScale);
  }
  if (s21_is_equal(divisor, one)) {
    ScalesAndSigns.resultScale = maxScale;
  }
  set_techInfo_big(ScalesAndSigns.resultSign, ScalesAndSigns.resultScale,
                   &big_result);
  big_to_normal(result, big_result, ScalesAndSigns.resultSign, &flag);
  return flag;
}

void s21_div_float(s21_decimal dividend, s21_decimal divisor,
                   s21_big_decimal *result, int *scale) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  int flag = 0;
  s21_decimal temporary = zero;
  s21_decimal small_result, help_quotient;
  s21_decimal remainder = dividend;  // Начальный остаток равен делимому
  *scale = 0;

  s21_div_int(remainder, divisor, result, &remainder);
  while (!s21_is_equal(remainder, zero) && *scale < 28) {
    s21_big_decimal big_temporary = {{0, 0, 0, 0, 0, 0, 0, 0}};

    // Умножаем остаток на 10 перед следующей попыткой деления
    temporary = zero;
    s21_mul(remainder, ten, &temporary);
    remainder = temporary;
    (*scale)++;

    // Выполняем целочисленное деление только остатка
    s21_div_int(remainder, divisor, &big_temporary, &remainder);
    big_to_normal(&small_result, *result, 0, &flag);
    temporary = small_result;
    s21_mul(small_result, ten, &temporary);
    small_result = temporary;
    temporary = zero;
    big_to_normal(&help_quotient, big_temporary, 0, &flag);
    s21_add(small_result, help_quotient, &temporary);
    small_result = temporary;
    fromDecimalToBigDecimal(result, small_result);
  }
}

void s21_div_int(s21_decimal dividend, s21_decimal divisor,
                 s21_big_decimal *quotient, s21_decimal *remainder) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal temporary;
  *remainder = zero;

  for (int i = 95; i >= 0; i--) {
    temporary = zero;
    // Сдвигаем остаток влево и добавляем текущий бит делимого
    s21_shift_left(remainder, 1);
    ;
    remainder->bits[0] |= (dividend.bits[i / 32] >> (i % 32)) & 1;

    if (s21_is_less(divisor, *remainder) || s21_is_equal(*remainder, divisor)) {
      s21_sub(*remainder, divisor, &temporary);
      *remainder = temporary;
      quotient->bits[i / 32] |= (1 << (i % 32));  // Устанавливаем 1 в частном
    }
  }
}
