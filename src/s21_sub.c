#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  uint64_t transfer = 0;
  s21_big_decimal big_result;
  memset(big_result.bits, 0, sizeof(big_result.bits));
  memset(result->bits, 0, sizeof(result->bits));
  RemoveInsignificantZeros(&value_1);
  RemoveInsignificantZeros(&value_2);
  ScalesAndSigns ScalesAndSigns;
  ScalesAndSigns.sign1 = getSign(value_1);
  ScalesAndSigns.sign2 = getSign(value_2);
  ScalesAndSigns.resultScale = getResultScaleForAddAndSub(value_1, value_2);

  decimalSubCheckOverflow(value_1, value_2, &flag);

  if (ScalesAndSigns.sign1 == 0 && ScalesAndSigns.sign2 == 1) {
    setSign(&value_2, 0);
    flag = s21_add(value_2, value_1, result);
    fromDecimalToBigDecimal(&big_result, *result);
    ScalesAndSigns.resultSign = 0;
  } else if (ScalesAndSigns.sign1 == 1 && ScalesAndSigns.sign2 == 0) {
    value_2.bits[3] = value_2.bits[3] | (1 << 31);
    flag = s21_add(value_1, value_2, result);
    fromDecimalToBigDecimal(&big_result, *result);
    ScalesAndSigns.resultSign = 1;
  } else {
    if (s21_is_less(value_1, value_2))
      ScalesAndSigns.resultSign = 1;
    else if (s21_is_less(value_2, value_1))
      ScalesAndSigns.resultSign = 0;
    if (s21_is_equal(value_1, value_2)) ScalesAndSigns.resultSign = 0;
    set_techInfo(0, 0, &value_1);
    set_techInfo(0, 0, &value_2);
    zero_scale(&value_1, &value_2, ScalesAndSigns.resultScale, &flag);
    set_techInfo(0, 0, &value_1);
    set_techInfo(0, 0, &value_2);
    for (int i = 0; i < 3; i++) {
      uint64_t sum = 0;
      uint8_t minus = 0;
      if (s21_is_less(value_1, value_2))
        sum = binary_sub(value_2.bits[i], value_1.bits[i], &transfer, &minus);
      else
        sum = binary_sub(value_1.bits[i], value_2.bits[i], &transfer, &minus);
      big_result.bits[i] += (int32_t)(sum & 0xFFFFFFFF);
      big_result.bits[i + 1] -= minus;
    }
  }
  set_techInfo_big(ScalesAndSigns.resultSign, ScalesAndSigns.resultScale,
                   &big_result);
  big_to_normal(result, big_result, ScalesAndSigns.resultSign, &flag);
  RemoveInsignificantZeros(result);
  return flag;
}

uint64_t binary_sub(uint64_t value_1, uint64_t value_2, uint64_t *transfer,
                    uint8_t *minus) {
  // заимствование у старшего бита, если уменьшаемое меньше вычитаемого
  if (value_1 < value_2) {
    value_1 = (value_1 | 0b100000000000000000000000000000000);
    *minus = 1;
  }
  // алгоритм бинарного вычитания, как алгоритм бинарного сложения делимого и
  // дополнения до двух от делителя
  value_2 = (~value_2) + 1;
  uint64_t sum;

  // обычный алгоритм бинарного сложения
  while (value_2 != 0 || *transfer != 0) {
    sum = value_1 ^ value_2;
    *transfer = (value_1 & value_2);
    value_1 = sum;
    value_2 = *transfer << 1;
  }
  return value_1;
}
