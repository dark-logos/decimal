#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal* result) {
  int errorFlag = 0;
  if (result == NULL) {
    errorFlag = 1;
  } else {
    s21_decimal trunc_val;
    int truncate_status = s21_truncate(value, &trunc_val);
    if (truncate_status != 0) {
      errorFlag = 1;
    } else if (s21_is_equal(value, trunc_val)) {
      *result = trunc_val;
    } else {
      s21_decimal zeroFive = {{5, 0, 0, 1 << 16}};
      getSign(value) ? s21_sub(value, zeroFive, &value)
                     : s21_add(value, zeroFive, &value);
      s21_truncate(value, result);
    }
  }
  return errorFlag;
}