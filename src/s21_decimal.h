#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_VALUE 1e-28
#define MAX_VALUE 79228162514264337593.0

#define likely(x) \
  __builtin_expect(!!(x), 1)  // условие выполняется в >= 90% случаях
#define unlikely(x) __builtin_expect(!!(x), 0)

#define MAX_INT 2147483648
#define MIN_INT -2147483649

typedef struct {
  uint32_t bits[4];
} s21_decimal;

typedef struct {
  uint32_t bits[8];
} s21_big_decimal;

typedef enum s21_conversion_result {
  S21_CONVERSION_OK = 0,
  S21_CONVERSION_ERROR = 1
} s21_conversion_result;

typedef struct {
  int sign1;
  int sign2;
  int resultSign;
  int scale1;
  int scale2;
  int resultScale;
} ScalesAndSigns;

/*Функции арифметики*/
// умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
uint64_t binary_multiply(uint64_t value_1, uint64_t value_2);

// сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
uint64_t binary_add(uint64_t value_1, uint64_t value_2, uint64_t *transfer);

// вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
uint64_t binary_sub(uint64_t value_1, uint64_t value_2, uint64_t *transfer,
                    uint8_t *minus);

// деление
int s21_div(s21_decimal dividend, s21_decimal divisor, s21_decimal *result);
void s21_div_int(s21_decimal dividend, s21_decimal divisor,
                 s21_big_decimal *quotient, s21_decimal *remainder);
void s21_div_float(s21_decimal dividend, s21_decimal divisor,
                   s21_big_decimal *result, int *scale);

/*Функции сравнения*/
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value_2);
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value_2);

/*Функции конвертации*/
int s21_from_int_to_decimal(int src, s21_decimal *restrict decimalValue);
int s21_from_decimal_to_int(s21_decimal src, int *restrict dst);
int s21_from_decimal_to_float(s21_decimal decimalValue,
                              float *restrict floatValue);
int s21_from_float_to_decimal(float floatValue,
                              s21_decimal *restrict decimalValue);
int s21_from_string_to_decimal(char *decimalBuffer, s21_decimal *decimalValue,
                               int lengthOfBuffer);

/*Функции округления*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*Функции Валеры*/
int getSign(s21_decimal value);
int getScale(s21_decimal value);
void setSign(s21_decimal *value, int sign);
void setScale(s21_decimal *value, int scale);
int s21_decimal_is_set_bit(s21_decimal decimal, int index);
int s21_is_set_bit(int number, int index);
void multiply_by_ten(s21_big_decimal *value);
void add_digit(s21_big_decimal *value, int digit);

/*Функции Диора*/
int compareBits(s21_decimal value1, s21_decimal value2);
int multiply_by_10(s21_decimal *num);
s21_decimal scaleDown(s21_decimal value, int scaleDiff);
int s21_check_zero(s21_decimal value1);

/*Функции Леши*/
void normalize(s21_decimal *value_1, s21_decimal *value_2);
bool div_by_10(s21_decimal value);
void remove_zero(s21_decimal *value);
void s21_shift_right(s21_decimal *number, int times);
void s21_shift_left(s21_decimal *number, int times);
int s21_checking_decimal_for_correct(s21_decimal num);

/*Функции Феди*/
void print_binary32(unsigned long int num);
void print_binary64(unsigned long int num);
void set_techInfo_big(int result_sign, int result_scale,
                      s21_big_decimal *result);  // эта для big_decimal
void set_techInfo(int result_sign, int result_scale,
                  s21_decimal *result);  // эта для decimal
void get_techInfo(int *scale1, int *scale2, int *sign1, int *sign2,
                  s21_decimal value1, s21_decimal value2);
void s21_shift_right(s21_decimal *number, int times);
void s21_shift_left(s21_decimal *number, int times);
void big_to_normal(s21_decimal *result, s21_big_decimal big_result,
                   int result_sign, int *flag);
void zero_scale(s21_decimal *value_1, s21_decimal *value_2, int scale,
                int *flag);
void fromDecimalToBigDecimal(s21_big_decimal *start, s21_decimal result);
void decimalCheckOverflow(s21_decimal value_1, s21_decimal value_2, int *flag);
void RemoveInsignificantZeros(s21_decimal *value);
int getResultScaleForAddAndSub(s21_decimal value_1, s21_decimal value_2);
int findMaxScale(s21_decimal value1, s21_decimal value2);
void decimalAddCheckOverflow(s21_decimal value_1, s21_decimal value_2,
                             int *flag);
void decimalSubCheckOverflow(s21_decimal value_1, s21_decimal value_2,
                             int *flag);
void s21_init_decimal(s21_decimal *decimal, uint32_t bit0, uint32_t bit1,
                      uint32_t bit2, uint32_t bit3);

#endif