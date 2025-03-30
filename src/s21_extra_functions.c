#include "s21_decimal.h"

void print_binary32(unsigned long int num) {
  for (int i = 31; i >= 0; i--) {
    if (i == 7 || i == 15 || i == 23) printf(" ");
    unsigned int bit = (num >> i) & 1;
    printf("%u", bit);
  }
}

void print_binary64(unsigned long int num) {
  for (int i = 63; i >= 0; i--) {
    if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39 || i == 47 ||
        i == 55 || i == 63)
      printf(" ");
    unsigned int bit = (num >> i) & 1;
    printf("%u", bit);
  }
}

void set_techInfo_big(int result_sign, int result_scale,
                      s21_big_decimal *result) {
  // Очистка битов перед установкой
  result->bits[7] &= ~(0xFF << 16);  // Очищаем биты 16-23 для scale
  // Установка знака
  if (result_sign)
    result->bits[7] |= (1 << 31);
  else
    result->bits[7] &= ~(1 << 31);
  // Установка scale
  if (result_scale >= 0 && result_scale <= 28)
    result->bits[7] |= (result_scale << 16);
}

void set_techInfo(int result_sign, int result_scale, s21_decimal *result) {
  // установка значения знака
  if (result_sign)
    result->bits[3] = result->bits[3] | (1 << 31);
  else if (!result_sign)
    result->bits[3] = result->bits[3] & ~(1 << 31);

  // установка значения коэффициента масштабирования
  if (result_scale >= 0 && result_scale <= 28)
    result->bits[3] |= (result_scale << 16);
}

void get_techInfo(int *scale1, int *scale2, int *sign1, int *sign2,
                  s21_decimal value1, s21_decimal value2) {
  *scale1 = getScale(value1);
  *scale2 = getScale(value2);
  *sign1 = getSign(value1);
  *sign2 = getSign(value2);
}

void normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int scale1 = getScale(*value_1);
  int scale2 = getScale(*value_2);

  while (scale1 > 0 && div_by_10(*value_1)) {
    remove_zero(value_1);
    scale1--;
  }

  while (scale2 > 0 && div_by_10(*value_2)) {
    remove_zero(value_2);
    scale2--;
  }

  setScale(value_1, scale1);
  setScale(value_2, scale2);
}

void setScale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    value->bits[3] = (value->bits[3] & ~(0xFF << 16)) | ((scale & 0xFF) << 16);
  }
}

void remove_zero(s21_decimal *value) {
  unsigned int low = value->bits[0];
  unsigned int mid = value->bits[1];
  unsigned int high = value->bits[2];

  unsigned long long remainder = 0;
  unsigned long long current;

  current = ((unsigned long long)low + (remainder << 32));
  value->bits[0] = (unsigned int)(current / 10);
  remainder = current % 10;

  current = ((unsigned long long)mid + (remainder << 32));
  value->bits[1] = (unsigned int)(current / 10);
  remainder = current % 10;

  current = ((unsigned long long)high + (remainder << 32));
  value->bits[2] = (unsigned int)(current / 10);
}

void s21_shift_left(s21_decimal *number, int times) {
  number->bits[2] = (number->bits[2] << times) | (number->bits[1] >> 31);
  number->bits[1] = (number->bits[1] << times) | (number->bits[0] >> 31);
  number->bits[0] = (number->bits[0] << times);
}

void s21_shift_left_big(s21_big_decimal *number, int times) {
  number->bits[7] = (number->bits[2] << times) | (number->bits[1] >> 31);
  number->bits[6] = (number->bits[2] << times) | (number->bits[1] >> 31);
  number->bits[5] = (number->bits[1] << times) | (number->bits[0] >> 31);
  number->bits[4] = (number->bits[2] << times) | (number->bits[1] >> 31);
  number->bits[3] = (number->bits[1] << times) | (number->bits[0] >> 31);
  number->bits[2] = (number->bits[2] << times) | (number->bits[1] >> 31);
  number->bits[1] = (number->bits[1] << times) | (number->bits[0] >> 31);
  number->bits[0] = (number->bits[0] << times);
}

void s21_shift_right(s21_decimal *number, int times) {
  number->bits[0] = (number->bits[0] >> times);
  number->bits[1] = (number->bits[1] >> times) | (number->bits[0] << 31);
  number->bits[2] = (number->bits[2] >> times) | (number->bits[1] << 31);
}

void BankRound(s21_decimal *value, uint32_t remainder, int sign) {
  if (remainder > 5 || (remainder == 5 && (value->bits[0] & 1))) {
    if (sign) {
      value->bits[0] |= (1);
    } else {
      value->bits[0] = (value->bits[0] & ~(1 << 0)) | (1 << 1);
    }
  }
}

void big_to_normal(s21_decimal *result, s21_big_decimal big_result,
                   int result_sign, int *flag) {
  for (int i = 0; i <= 2; i++) {
    result->bits[i] = big_result.bits[i];
  }
  result->bits[3] = big_result.bits[7];
  if (big_result.bits[3] > 0 || big_result.bits[4] > 0 ||
      big_result.bits[5] > 0 || big_result.bits[6] > 0) {
    BankRound(result, big_result.bits[3], result_sign);
    if (result_sign == 1)
      *flag = 2;
    else
      *flag = 1;
  }
}

void zero_scale(s21_decimal *value_1, s21_decimal *value_2, int result_scale,
                int *flag) {
  int scale1 = getScale(*value_1);
  int scale2 = getScale(*value_2);
  int min_scale = 0;
  if (scale1 < scale2)
    min_scale = scale1;
  else if (scale2 < scale1)
    min_scale = scale2;
  s21_decimal ten = {{10, 0, 0, 0}}, zero = {{0, 0, 0, 0}},
              temporary = {{0, 0, 0, 0}};
  for (int i = result_scale - min_scale; i > 0; i--) {
    if (scale1 < scale2) {
      temporary = zero;
      *flag = s21_mul(*value_1, ten, &temporary);
      *value_1 = temporary;
    } else if (scale2 < scale1) {
      temporary = zero;
      *flag = s21_mul(*value_2, ten, &temporary);
      *value_2 = temporary;
    }
  }
}

void fromDecimalToBigDecimal(s21_big_decimal *start, s21_decimal result) {
  for (int i = 2; i >= 0; i--) start->bits[i] = result.bits[i];
  // start->bits[7] = result.bits[3];
}

void decimalSubCheckOverflow(s21_decimal value_1, s21_decimal value_2,
                             int *flag) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 << 31}};
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 31}};

  if ((s21_is_equal(value_1, max) && s21_is_less(value_2, zero)))
    *flag = 1;
  else if ((s21_is_equal(value_1, min) && s21_is_less(zero, value_2)))
    *flag = 2;
  else if ((s21_is_equal(value_2, max) && s21_is_less(value_1, zero)))
    *flag = 1;
  else if (s21_is_equal(value_2, min) && s21_is_less(zero, value_1))
    *flag = 2;
}
void decimalAddCheckOverflow(s21_decimal value_1, s21_decimal value_2,
                             int *flag) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 << 31}};
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 31}};

  if ((s21_is_equal(value_1, max) && s21_is_less(zero, value_2)))
    *flag = 1;
  else if ((s21_is_equal(value_1, min) && s21_is_less(value_2, zero)))
    *flag = 2;
  else if ((s21_is_equal(value_2, max) && s21_is_less(zero, value_1)))
    *flag = 1;
  else if (s21_is_equal(value_2, min) && s21_is_less(value_1, zero))
    *flag = 2;
}

void RemoveInsignificantZeros(s21_decimal *value) {
  s21_decimal temporary, zero = {{0, 0, 0, 0}}, ten = {{10, 0, 0, 0}};
  int scale = getScale(*value);
  setScale(value, 0);
  while (div_by_10(*value) && scale > 0) {
    temporary = zero;
    s21_div(*value, ten, &temporary);
    *value = temporary;
    scale--;
  }
  setScale(value, scale);
}

int getResultScaleForAddAndSub(s21_decimal value_1, s21_decimal value_2) {
  int result_scale = 0;
  int scale1 = getScale(value_1);
  int scale2 = getScale(value_2);
  if (scale1 > scale2)
    result_scale = scale1;
  else
    result_scale = scale2;
  return result_scale;
}

int findMaxScale(s21_decimal value1, s21_decimal value2) {
  int scale1 = getScale(value1);
  int scale2 = getScale(value2);
  int maxScale = scale1;
  if (scale2 > scale1) maxScale = scale2;
  return maxScale;
}

void s21_init_decimal(s21_decimal *decimal, uint32_t bit0, uint32_t bit1,
                      uint32_t bit2, uint32_t bit3) {
  decimal->bits[0] = bit0;
  decimal->bits[1] = bit1;
  decimal->bits[2] = bit2;
  decimal->bits[3] = bit3;
};