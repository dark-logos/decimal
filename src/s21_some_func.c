#include "s21_decimal.h"

int s21_check_zero(s21_decimal value1) {
  return value1.bits[0] == 0 && value1.bits[1] == 0 && value1.bits[2];
}

/* функция для сравнения битов двух s21_decimal */
int compareBits(s21_decimal a, s21_decimal b) {
  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] != b.bits[i]) {
      return a.bits[i] < b.bits[i];
    }
  }
  return 0;
}

s21_decimal scaleDown(s21_decimal value, int scaleDiff) {
  int sign = getSign(value);
  uint32_t scale = getScale(value);

  for (int i = 0; i < scaleDiff; i++) {
    uint32_t remainder = 0;
    for (int j = 2; j >= 0; j--) {
      uint64_t temp = ((uint64_t)remainder << 32) | value.bits[j];
      value.bits[j] = (uint64_t)(temp / 10);
      remainder = (uint64_t)(temp % 10);
    }
  }
  value.bits[3] = (sign << 31) | ((scale - scaleDiff) << 16);
  return value;
}

int getSign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

int getScale(s21_decimal value) { return (value.bits[3] >> 16) & 0x7FFF; }

bool div_by_10(s21_decimal value) {
  unsigned int low = value.bits[0];
  unsigned int mid = value.bits[1];
  unsigned int high = value.bits[2];

  unsigned long long remainder = 0;
  unsigned long long current;

  current = ((unsigned long long)high + (remainder << 32));
  remainder = current % 10;

  current = ((unsigned long long)mid + (remainder << 32));
  remainder = current % 10;

  current = ((unsigned long long)low + (remainder << 32));
  remainder = current % 10;

  return remainder == 0;
}

int multiply_by_10(s21_decimal *num) {
  s21_decimal tmp = *num;
  uint32_t carry = 0;  // перенос-проверка от переполнения

  /* Логика работы алгоритма:
  1) текущий блок мантиссы умножается на 10, в конце добавляется carry;
  2) беру младшие 32 бита и записываю в текущий разряд;
  3) в carry инициализирую старшие 32 бита, которые и становятся значением, для
  переноса. */

  for (int i = 0; i < 3; i++) {
    uint64_t val = (uint64_t)tmp.bits[i] * 10 + carry;
    num->bits[i] = (uint32_t)(val & 0xFFFFFFFF);
    carry = (uint32_t)(val >> 32);
  }
  return carry != 0;
}

void setSign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= (1 << 31);
  } else {
    value->bits[3] &= ~(1 << 31);
  }
}
