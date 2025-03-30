#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *restrict dst) {
  s21_conversion_result code = S21_CONVERSION_OK;
  if (unlikely(dst == NULL)) {
    return S21_CONVERSION_ERROR;
  }
    // s21_decimal temp = src;     
    // __int64_t preInt = 0;
    // //s21_truncate(&temp); добавить сюда округление
    s21_decimal tmp = src;     
    uint64_t preInt = 0;
    s21_decimal temp;
    s21_truncate(tmp, &temp);
  if (likely(temp.bits[1] == 0 && temp.bits[2] == 0)) {
    preInt = temp.bits[0];

    //*dst /= (int)pow(10, getScale(temp));
    unsigned int scale = getScale(temp);
    unsigned int divisor = 1;
    // было выбрано решение ограничить массив до 9 элементов, т.к. с точки
    // зрения прогнозирования scale для числа типа int крайне редко будет
    // превышать значение 9
    if (scale <= 9) {  // убрать if
      static const unsigned int pow10_lookup[10] = {
          1,      10,      100,      1000,      10000,
          100000, 1000000, 10000000, 100000000, 1000000000};
      divisor = pow10_lookup[scale];
    } else {
      divisor = (unsigned int)pow(10, scale);
    }
    preInt /= divisor;
    int sign = 1 - 2 * getSign(temp);
    preInt *= sign;

    // code = (preInt < MIN_INT) ? S21_CONVERSION_ERROR : code;
    // code = (preInt > MAX_INT) ? S21_CONVERSION_ERROR : code;
    *dst = (int)preInt;
  } else {
    code = S21_CONVERSION_ERROR;
  }
  return code;
}
