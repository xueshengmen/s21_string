#include "s21_sprintf.h"

// Limits on convert: 52 digit after point (with not null fractal part); 70
// digit after point (with null fractal part) Limits on arounding: correctly
// round in range from 0 to 40; if accuracy in the range from 40 to 70 (0.05%
// fails)

/**
 * @brief 
 * Limits on convert: 52 digit after point (with not null fractal part); 70
 * digit after point (with null fractal part) Limits on arounding: correctly
 * round in range from 0 to 40; if accuracy in the range from 40 to 70 (0.05%
 * fails)
 * @param num 
 * @param accuracy number of digit after point
 * @param params 
 * @return char* - Double converted in string
 */
char* DoubleToString(double num, int accuracy, PrintParams* params) {
  accuracy = accuracy < 0 ? DEFAULT_ACCURACY : accuracy;
  char* res = CheckSpecialValue(num);
  if (!res) {
    unsigned long long num_buff = (*((unsigned long long*)(&num)));
    int exponent = GetExponent(num_buff);

    unsigned long long mantis = GetMantis(num_buff);
    unsigned long long whole_part, fract_part;

    int shift = GetWHoleAndFractPartFromMantis(mantis, exponent, &whole_part,
                                               &fract_part);

    char *whole_part_str, *fract_part_str;
    fract_part_str =
        GetFractPartInString(fract_part, exponent, shift, accuracy);

    if (fract_part_str[0] == '1') whole_part++;

    if (num_buff & SIGN_64) whole_part *= -1;

    if (num_buff & SIGN_64 && (long long int)whole_part == 0) {
      whole_part_str = malloc(3);
      whole_part_str[0] = '-';
      whole_part_str[1] = '0';
      whole_part_str[2] = '\0';
    } else {
      whole_part_str = WholePartToString((long long int)whole_part, 10);
    }
    if (!accuracy) {
      res = whole_part_str;
      free(fract_part_str);
    } else {
      res = ConcatenateWholeAndFractParts(whole_part_str, fract_part_str);
      free(fract_part_str);
      free(whole_part_str);
    }

    if ((params->flags & HASHFLAG) && params->accuracy == 0) {
      int res_len = s21_strlen(res);
      char* tmp = malloc(res_len + 2);
      s21_strcpy(tmp, res);
      tmp[res_len] = '.';
      tmp[res_len + 1] = '\0';
      free(res);
      res = tmp;
    }
  }
  return res;
}

// TO-DO remove params and add func to change register
char* WholePartToString(long long int num, int base) {
  char tmp[BUFFERSIZE] = {'\0'};
  int negative = num >= 0 ? 0 : 1;
  num = negative ? -num : num;

  if (num == 0) tmp[0] = '0';
  for (int i = 0; num > 0; i++, num /= base) {
    tmp[i] = "0123456789abcdef"[num % base];
  }

  int str_len = negative ? s21_strlen(tmp) + 1 : s21_strlen(tmp);
  char* result = malloc(str_len + 1);
  int i = 0;
  if (negative) result[i++] = '-';

  for (int j = str_len - (negative ? 2 : 1); i < str_len; i++, j--) {
    result[i] = tmp[j];
  }

  result[str_len] = '\0';

  return result;
}

char* UIntToString(unsigned long long int num, int base, PrintParams* params) {
  char tmp[BUFFERSIZE] = {'\0'};

  int negative = num >= 0 ? 0 : 1;
  num = negative ? -num : num;

  if (num == 0) tmp[0] = '0';
  for (int i = 0; num > 0; i++, num /= base) {
    if (params->symbol == 'X') {
      tmp[i] = "0123456789ABCDEF"[num % base];
    } else {
      tmp[i] = "0123456789abcdef"[num % base];
    }
  }

  int str_len = negative ? s21_strlen(tmp) + 2 : s21_strlen(tmp) + 1;
  char* result = malloc(str_len + 1);
  int i = 0;
  if (negative) result[i++] = '-';
  for (int j = str_len - (negative ? 3 : 2); i < str_len; i++, j--) {
    result[i] = tmp[j];
  }
  result[str_len] = '\0';
  return result;
}

char* DoubleToExponentialForm(double num, int accuracy, int* exponent,
                              PrintParams* params) {
  accuracy = accuracy < 0 ? DEFAULT_ACCURACY : accuracy;
  char* res = CheckSpecialValue(num);
  *exponent = 0;
  if (!res) {
    char* double_str = PrepareMantis(fabs(num), accuracy, params, exponent);
    double_str = GetMantisForExponentialForm(double_str, accuracy);

    char* exponent_str = GetExponentForExponentialForm(*exponent, params);

    res = UniteMantisAndExponent(num, double_str, exponent_str);
  }
  return res;
}

// ========================DoubleToString utility func========================

char* CheckSpecialValue(double num) {
  char* res = NULL;
  if (isnan(num)) {
    res = malloc(4);
    s21_strcpy(res, "nan");
  } else if (num == -INFINITY) {
    res = malloc(5);
    s21_strcpy(res, "-inf");
  } else if (num == INFINITY) {
    res = malloc(4);
    s21_strcpy(res, "inf");
  }
  return res;
}

char* ConcatenateWholeAndFractParts(char* whole_part_str,
                                    char* fract_part_str) {
  int res_len = s21_strlen(whole_part_str) + s21_strlen(fract_part_str) - 1;
  char* res = malloc(res_len + 1);
  int i = 0;
  for (; i < s21_strlen(whole_part_str); ++i) {
    res[i] = whole_part_str[i];
  }
  for (int j = 1; j < s21_strlen(fract_part_str); ++j, ++i) {
    res[i] = fract_part_str[j];
  }
  res[i] = '\0';

  return res;
}

unsigned long long GetMantis(unsigned long long num) {
  num <<= EXPONENT_SIZE;
  num |= SIGN_64;
  num >>= EXPONENT_SIZE;
  return num;
}

int GetExponent(unsigned long long num) {
  return ((num & EXPONENT_64) >> MANTISSA_SIZE) - CONSTANT_MANTIS_DOUBLE;
}

int GetWHoleAndFractPartFromMantis(unsigned long long mantis, int exponent,
                                   unsigned long long* whole_part,
                                   unsigned long long* fract_part) {
  int shift = 0;
  if (exponent >= MANTISSA_SIZE + 1) {
    *whole_part = mantis << (exponent - MANTISSA_SIZE);
    *fract_part = 0;
  } else if (exponent >= 0) {
    *whole_part = mantis >> ((MANTISSA_SIZE + 1) - exponent - 1);
    *fract_part = (mantis << (exponent + 1 + EXPONENT_SIZE)) >> (EXPONENT_SIZE);
  } else {
    *whole_part = 0;
    *fract_part = mantis;
    while (!((*fract_part) & 1)) {
      *fract_part >>= 1;
      shift++;
    }
  }
  return shift;
}

void SumForChar(char** res, const char* str) {
  int buffer = 0;
  for (int i = 70; i > 1; --i) {
    int a = ((*res)[i] - 48);
    int b = (str[i] - 48);
    (*res)[i] = ((a + b + buffer) % 10) + 48;
    buffer = (a + b + buffer) / 10;
  }
}

void RecursiveIncrement(char* fract_part, int accuracy) {
  if (fract_part[accuracy + 2] >= '5') (fract_part[accuracy + 1])++;
  int idx = accuracy + 1;
  while (fract_part[idx] > '9' && idx != 2) {
    if (fract_part[idx] > '9') fract_part[idx] = '0';
    (fract_part[--idx])++;
  }
  if (fract_part[idx] > '9') fract_part[0] = '1';
}

char* CutOffInsignificantPart(char* fract_part, int accuracy) {
  char* res = malloc(2 + accuracy + 1);
  for (int i = 0; i < accuracy + 2 && fract_part[0] == '0'; ++i) {
    res[i] = fract_part[i];
  }
  for (int i = 0; i < accuracy + 2 && fract_part[0] == '1'; ++i) {
    if (i < 2)
      res[i] = fract_part[i];
    else
      res[i] = '0';
  }
  res[2 + accuracy] = '\0';
  free(fract_part);
  return res;
}

char* GetFractPartInString(unsigned long long fract_part, int exponent,
                           int shift, int accuracy) {
  int size_fract_part = accuracy > 70 ? accuracy : 70;
  char* res = malloc(size_fract_part + 3);
  for (int i = 2; i < size_fract_part + 2; ++i) {
    res[i] = '0';
  }
  res[0] = '0';
  res[1] = '.';
  res[size_fract_part + 2] = '\0';
  unsigned long long idx = 1;
  for (int i = 0; i <= MANTISSA_SIZE && exponent >= 0; ++i) {
    if (fract_part & idx) {
      SumForChar(&res, fract_value[MANTISSA_SIZE - i]);
    }
    idx <<= 1;
  }

  // handle zero whole part case
  int max_idx = (MANTISSA_SIZE + (abs(exponent) - shift - 1));
  for (int i = 0; i <= max_idx && exponent < 0; ++i) {
    if ((fract_part & idx) && (max_idx - i < 73)) {
      SumForChar(&res, fract_value[max_idx - i]);
    }
    idx <<= 1;
  }

  if (!accuracy && res[2] >= '5') {
    res[0] = '1';
    char* tmp = malloc(2);
    tmp[0] = res[0];
    tmp[1] = '\0';
    free(res);
    res = tmp;
  } else {
    RecursiveIncrement(res, accuracy);
    res = CutOffInsignificantPart(res, accuracy);
  }
  return res;
}

// ========================DoubleToString utility func========================

// ========================DoubleToExponentialForm utility func===============

int GetFirstNotNullDigitIndex(char* str) {
  int idx = 1;
  int str_len = s21_strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] != '0' && str[i] != '.') {
      idx = i;
      break;
    }
  }
  return idx == 0 ? 1 : idx;
  ;
}

int OtherZero(char* double_str, int start) {
  size_t len = s21_strlen(double_str);
  len = len >= 80 ? 80 : len;
  int res = 1;
  for (int i = start; i < len; ++i) {
    if (double_str[i] != '0') {
      res = 0;
      break;
    }
  }
  return res;
}

void RoundForExp(char* fract_part, int accuracy, int other_zero,
                 int* exponent) {
  if ((fract_part[accuracy] - 48) % 2 == 0 && fract_part[accuracy + 1] == '5' &&
      other_zero) {
    (fract_part[accuracy])--;
  }
  if (fract_part[accuracy + 1] >= '5') {
    (fract_part[accuracy])++;
  }  // 99 -> :0
  int idx = accuracy;
  while (fract_part[idx] > '9' && idx != 0) {
    if (fract_part[idx] > '9') fract_part[idx] = '0';
    (fract_part[--idx])++;
  }
  if (fract_part[idx] > '9') {
    fract_part[0] = '1';
    (*exponent)++;
  }
}

char* PrepareMantis(double num, int accuracy, PrintParams* params,
                    int* exponent) {
  int max_accuracy = accuracy > 150 ? accuracy : 150;
  char* double_str = DoubleToString(num, max_accuracy, params);
  int first_digit = GetFirstNotNullDigitIndex(double_str);
  int point_idx = GetSymbPosition(double_str, '.');

  if (double_str[0] == '0') {
    (*exponent) = -(first_digit - 1);
  } else {
    (*exponent) = point_idx - 1;
  }

  double_str = RemoveCharFromStr(double_str, '.', 1);
  int shift = first_digit == 1 ? 0 : first_digit;
  int other_zero = OtherZero(double_str, accuracy + shift + 2);
  char* digit_array =
      malloc(1 + accuracy + 1 + 1);  // accuracy + 1 digit after point
  int i = 0;
  for (; i <= accuracy + 1; i++) {
    digit_array[i] = double_str[first_digit - 1 + i];
  }
  digit_array[i] = '\0';
  free(double_str);
  //    printf("%s\n",digit_array);
  RoundForExp(digit_array, accuracy, other_zero, exponent);
  digit_array[accuracy + 1] = '\0';
  //    printf("%s\n",digit_array);

  char* res = malloc(accuracy + 2);
  s21_strcpy(res, digit_array);

  res[accuracy + 1] = '\0';
  free(digit_array);

  return res;
}

char* GetMantisForExponentialForm(char* double_str, int accuracy) {
  int double_len = s21_strlen(double_str);
  char* res = double_str;
  if (double_len != 1) {
    res = malloc(double_len + 2);
    int i = 0;
    res[i++] = double_str[0];
    if (accuracy) res[i++] = '.';
    for (i = 1; i < double_len; i++) {
      res[i + 1] = double_str[i];
    }
    res[i + 1] = '\0';
    free(double_str);
  }
  return res;
}

char* GetExponentForExponentialForm(int exponent, PrintParams* params) {
  char* exponent_str = WholePartToString(abs(exponent), 10);

  if (s21_strlen(exponent_str) == 1) {
    char* tmp = malloc(3);
    tmp[0] = '0';
    tmp[1] = exponent_str[0];
    tmp[2] = '\0';
    free(exponent_str);
    exponent_str = tmp;
  }
  int exponent_len = s21_strlen(exponent_str);

  char* res = malloc(2 + exponent_len + 2);
  res[0] = params->symbol;
  res[1] = IsNegative(exponent) ? '-' : '+';
  res[2] = '\0';
  s21_strcat(res, exponent_str);
  res[2 + exponent_len + 1] = '\0';
  free(exponent_str);
  return res;
}

char* UniteMantisAndExponent(double num, char* mantis_str, char* exponent_str) {
  int i = 0;
  int mantis_str_len = s21_strlen(mantis_str);
  int exponent_str_len = s21_strlen(exponent_str);
  char* res = malloc(IsNegative(num) + mantis_str_len + exponent_str_len + 1);
  if (IsNegative(num)) res[i++] = '-';
  res[i++] = '\0';
  s21_strcat(res, mantis_str);
  s21_strcat(res, exponent_str);
  res[IsNegative(num) + mantis_str_len + exponent_str_len] = '\0';
  free(exponent_str);
  free(mantis_str);
  return res;
}
