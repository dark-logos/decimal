
#include "s21_decimal.h"

int s21_from_int_to_decimal(int intValue, s21_decimal *restrict decimalValue) {
  s21_conversion_result code = S21_CONVERSION_OK;
  if (unlikely(decimalValue == NULL)) {
    return S21_CONVERSION_ERROR;
  }
  setScale(decimalValue, 0);
  setSign(decimalValue, 0);

  memset(decimalValue, 0, sizeof(s21_decimal));
  setSign(decimalValue, (intValue < 0));
  intValue = abs(intValue);  // ускорил выполнение операции на одну ассемблерную
                             // инструкцию(ABS)

  decimalValue->bits[0] = intValue;

  return code;
}
