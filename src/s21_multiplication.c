#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_big_decimal big_result;
  s21_decimal zero = {{0, 0, 0, 0}};
  memset(big_result.bits, 0, sizeof(big_result.bits));
  memset(result->bits, 0, sizeof(result->bits));

  ScalesAndSigns ScalesAndSigns;
  ScalesAndSigns.resultScale = getScale(value_1) + getScale(value_2);
  ScalesAndSigns.resultSign = getSign(value_1) ^ getSign(value_2);
  if (s21_is_equal(value_1, zero) || s21_is_equal(value_2, zero)) {
    *result = zero;
    return 0;
  }
  // Алгоритм умножения
  for (int i = 2; i >= 0; i--) {
    for (int j = 2; j >= 0; j--) {
      uint64_t product = binary_multiply(value_1.bits[i], value_2.bits[j]);
      big_result.bits[i + j] += (int32_t)(product & 0xFFFFFFFF);

      // Проверка переполнения
      if ((big_result.bits[i + j]) < (uint32_t)(product & 0xFFFFFFFF)) {
        if (i + j + 1 < 6) {
          big_result.bits[i + j + 1]++;
        }
      }

      // Добавление старших битов
      if (i + j + 1 < 5) {
        big_result.bits[i + j + 1] += (int32_t)(product >> 32);
      }
    }
  }
  set_techInfo_big(ScalesAndSigns.resultSign, ScalesAndSigns.resultScale,
                   &big_result);
  big_to_normal(result, big_result, ScalesAndSigns.resultSign, &flag);
  return flag;
}

uint64_t binary_multiply(uint64_t value_1, uint64_t value_2) {
  uint64_t result = 0;
  while (value_2 > 0) {
    if (value_2 & 1) {
      result += value_1;
    }
    value_1 <<= 1;
    value_2 >>= 1;
  }
  return result;
}
