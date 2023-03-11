#include "s21_sscanf.h"

long long StrToDec(const char *str, ScanParams *params, int negative) {
  long long int result = 0;

  if (params->width != 0) {
    result = str[params->i] - '0';
    params->width--;
    params->read_symbols++;
  }

  while (IsDigit(str[++params->i], 10) && params->width != 0) {
    result = result * 10 + (str[params->i] - '0');
    params->read_symbols++;
    params->width--;
  }

  if (negative) result *= -1;

  return result;
}

long long StrToHex(const char *str, ScanParams *params, int negative) {
  long long int result = 0;

  if (str[params->i] == '0' &&
      (str[params->i + 1] == 'x' || str[params->i + 1] == 'X')) {
    params->i += 2;
  }

  int status = 1;
  while (params->width != 0 && status) {
    if (str[params->i] - '0' >= 0 && str[params->i] - '0' <= 9) {
      result = result * 16 + (str[params->i] - '0');
    } else if (str[params->i] >= 'a' && str[params->i] <= 'f') {
      result = result * 16 + (str[params->i] - 'a' + 10);
    } else if (str[params->i] >= 'A' && str[params->i] <= 'F') {
      result = result * 16 + (str[params->i] - 'A' + 10);
    } else {
      status = 0;
    }
    params->read_symbols++;
    params->width--;
    params->i++;
  }

  if (negative) result *= -1;

  return result;
}

long long StrToOct(const char *str, ScanParams *params, int negative) {
  long long int result = 0;

  if (str[params->i] == '0') {
    params->i++;
  }

  int status = 1;
  while (params->width != 0 && status) {
    if (str[params->i] >= '0' && str[params->i] <= '7') {
      result = result * 8 + (str[params->i] - '0');
    } else {
      status = 0;
    }
    params->read_symbols++;
    params->width--;
    params->i++;
  }

  if (negative) result *= -1;

  return result;
}