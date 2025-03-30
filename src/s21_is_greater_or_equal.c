#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value_2) {
  return (s21_is_equal(value1, value_2) || s21_is_greater(value1, value_2)) ? 1
                                                                            : 0;
}