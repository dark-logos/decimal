#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int s21_from_float_to_decimal(float floatValue, s21_decimal *decimalValue) {
  if (decimalValue == NULL) return S21_CONVERSION_ERROR;

  setScale(decimalValue, 0);
  setSign(decimalValue, 0);

  if (isinf(floatValue) || fabs(floatValue) > MAX_VALUE ||
      (fabs(floatValue) < MIN_VALUE && floatValue != 0.0)) {
    return S21_CONVERSION_ERROR;
  }

  char decimalBuffer[50], preciseBuffer[100] = {0};
  snprintf(preciseBuffer, sizeof(preciseBuffer), "%.7g", floatValue);
  int i = 0, y = 0, positionOfDot = -1, exponent = 0;
  int sign = (floatValue < 0) ? 1 : 0;

  while (preciseBuffer[i] != 'e' && preciseBuffer[i] != 'E' &&
         preciseBuffer[i] != '\0') {
    if (preciseBuffer[i] ==
        '.') {  // участок можно переработать (чтобы после нахождения точки код
                // не проверял символ на то, что он точка)
      positionOfDot = y;
    } else if (preciseBuffer[i] != '-') {
      decimalBuffer[y++] = preciseBuffer[i];
    }
    i++;
  }
  decimalBuffer[y] = '\0';
  if (preciseBuffer[i] == 'e' || preciseBuffer[i] == 'E') {
    exponent = strtol(&preciseBuffer[++i], NULL, 10);
  }
  int digitsAfter = (positionOfDot != -1) ? (y - positionOfDot) : 0;
  int effective_scale = (exponent > digitsAfter)
                            ? 0
                            : (digitsAfter - exponent);  // необходимая точность

  if (exponent > digitsAfter) {  // добавляем недостоющие нули
    memset(decimalBuffer + y, '0', exponent - digitsAfter);
    y += exponent - digitsAfter;
    decimalBuffer[y] = '\0';
  }
  setScale(decimalValue, effective_scale);
  setSign(decimalValue, sign);
  s21_from_string_to_decimal(decimalBuffer, decimalValue, y);
  return S21_CONVERSION_OK;
}

int s21_from_string_to_decimal(char *decimalBuffer, s21_decimal *decimalValue,
                               int lengthOfBuffer) {
  s21_big_decimal value = {0};

  for (int j = 0; j < lengthOfBuffer; j++) {
    if (decimalBuffer[j] >= '0' && decimalBuffer[j] <= '9') {
      multiply_by_ten(&value);
      add_digit(&value, decimalBuffer[j] - '0');
    }
  }

  decimalValue->bits[0] = value.bits[0];
  decimalValue->bits[1] = value.bits[1];
  decimalValue->bits[2] = value.bits[2];
  return 0;
}

void multiply_by_ten(s21_big_decimal *value) {
  unsigned int carry = 0;
  for (int i = 0; i < 8; i++) {
    unsigned long long temp = (unsigned long long)value->bits[i] * 10 + carry;
    value->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    carry = (unsigned int)(temp >> 32);
  }
}

void add_digit(s21_big_decimal *value, int digit) {
  unsigned int carry = digit;
  for (int i = 0; i < 8; i++) {
    unsigned long long temp = (unsigned long long)value->bits[i] + carry;
    value->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    carry = (unsigned int)(temp >> 32);
    //if (carry == 0) break; 
  }
}
