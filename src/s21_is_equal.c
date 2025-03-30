#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;

  s21_decimal value_copy_1 = value_1;
  s21_decimal value_copy_2 = value_2;

  int sign1 = getSign(value_copy_1);
  int sign2 = getSign(value_copy_2);
  if (sign1 != sign2) {
    result = 0;
  }
  normalize(&value_copy_1, &value_copy_2);
  int scale1 = getScale(value_copy_1);
  int scale2 = getScale(value_copy_2);

  if (scale1 != scale2) {
    result = 0;
  }

  for (int j = 0; j < 3; j++) {
    // printf("value_copy_1[%d]:", j);
    // for (int i = 31; i >= 0; i--) {
    //   printf("%d", (value_copy_1.bits[j] >> i) & 1);
    //   if (i % 4 == 0) printf(" ");
    // }
    // printf("\n");
    // printf("value_copy_2[%d]:", j);
    // for (int i = 31; i >= 0; i--) {
    //   printf("%d", (value_copy_2.bits[j] >> i) & 1);
    //   if (i % 4 == 0) printf(" ");
    // }
    // printf("\n");
    if (value_copy_1.bits[j] != value_copy_2.bits[j]) {
      result = 0;
    }
  }
  scale1 = getScale(value_copy_1);
  scale2 = getScale(value_copy_2);

  return result;
}