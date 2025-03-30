#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  uint64_t transfer = 0;
  s21_big_decimal big_result;
  memset(big_result.bits, 0, sizeof(big_result.bits));
  memset(result->bits, 0, sizeof(result->bits));

  ScalesAndSigns ScalesAndSigns;
  ScalesAndSigns.sign1 = getSign(value_1);
  ScalesAndSigns.sign2 = getSign(value_2);
  ScalesAndSigns.resultScale = getResultScaleForAddAndSub(value_1, value_2);

  decimalAddCheckOverflow(value_1, value_2, &flag);
  if (ScalesAndSigns.sign1 == 1 && ScalesAndSigns.sign2 == 0) {
    value_1.bits[3] = value_1.bits[3] & ~(1 << 31);
    s21_sub(value_2, value_1, result);
    ScalesAndSigns.resultSign = result->bits[3] >> 31;
    fromDecimalToBigDecimal(&big_result, *result);
  } else if (ScalesAndSigns.sign1 == 0 && ScalesAndSigns.sign2 == 1) {
    value_2.bits[3] = value_2.bits[3] & ~(1 << 31);
    s21_sub(value_1, value_2, result);
    ScalesAndSigns.resultSign = result->bits[3] >> 31;
    fromDecimalToBigDecimal(&big_result, *result);
  } else {
    if (ScalesAndSigns.sign1 == 1 && ScalesAndSigns.sign2 == 1)
      ScalesAndSigns.resultSign = 1;
    else
      ScalesAndSigns.resultSign = 0;
    zero_scale(&value_1, &value_2, ScalesAndSigns.resultScale, &flag);
    for (int i = 0; i <= 2; i++) {
      uint64_t sum = 0;
      sum = binary_add(value_1.bits[i], value_2.bits[i], &transfer);
      big_result.bits[i] += (int32_t)(sum & 0xFFFFFFFF);
      if (i <= 6) {
        big_result.bits[i + 1] += (int32_t)(transfer);
      }
    }
  }

  set_techInfo_big(ScalesAndSigns.resultSign, ScalesAndSigns.resultScale,
                   &big_result);
  big_to_normal(result, big_result, ScalesAndSigns.resultSign, &flag);
  return flag;
}

uint64_t binary_add(uint64_t value_1, uint64_t value_2, uint64_t *transfer) {
  uint64_t sum;
  uint64_t carry = *transfer;
  int count = 0;

  while ((value_2 != 0 || carry != 0) && count <= 64) {
    sum = value_1 ^ value_2 ^ carry;
    carry = ((value_1 & value_2) | (value_1 & carry) | (value_2 & carry)) << 1;

    value_1 = sum + carry;
    if (value_1 != sum) carry = 0;
    value_2 = carry;
    count++;
  }

  *transfer = carry >> 63;
  return value_1;
}
