#include "s21_decimal.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  return s21_is_less_or_equal(value1, value2) ? 0 : 1;
}