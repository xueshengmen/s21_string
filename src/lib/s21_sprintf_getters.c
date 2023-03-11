#include "s21_sprintf.h"

long long int GetIntValue(PrintParams *params, va_list *arg_ptr) {
  long long int value;

  if (params->lenghtInt == 0) {
    value = va_arg(*arg_ptr, int);
  } else if (params->lenghtInt < 0) {
    value = va_arg(*arg_ptr, int);
    params->lenghtInt *= -1;
    if (params->lenghtInt % 2 == 1) value = value << 48 >> 48;
    if (params->lenghtInt % 2 == 0) value = value << 56 >> 56;
  } else if (params->lenghtInt % 2 == 1) {
    value = va_arg(*arg_ptr, unsigned long int);
  } else if (params->lenghtInt % 2 == 0) {
    value = va_arg(*arg_ptr, long long int);
  }

  return value;
}

unsigned long long int GetUIntValue(PrintParams *params, va_list *arg_ptr) {
  unsigned long long int value;

  if (params->lenghtInt == 0) {
    value = va_arg(*arg_ptr, unsigned int);
  } else if (params->lenghtInt < 0) {
    value = va_arg(*arg_ptr, unsigned int);
    params->lenghtInt *= -1;
    if (params->lenghtInt % 2 == 1) value = value << 48 >> 48;
    if (params->lenghtInt % 2 == 0) value = value << 56 >> 56;
  } else if (params->lenghtInt % 2 == 1) {
    value = va_arg(*arg_ptr, unsigned long int);
  } else if (params->lenghtInt % 2 == 0) {
    value = va_arg(*arg_ptr, unsigned long long int);
  }

  return value;
}

double GetDoubleValue(PrintParams *params, va_list *arg_ptr) {
  double value;

  if (params->lenghtDouble) {
    value = (double)va_arg(*arg_ptr, long double);
  } else {
    value = va_arg(*arg_ptr, double);
  }

  return value;
}

// If get \0, return string, wich contain only \0
// char *GetChar(int wchar) {
//   int len = 0;
//   char *ptr = (char *)&wchar;
//   for (; len <= 4; len++)
//     if (*(ptr + len) == 0) break;
//   char *res = malloc(len + 1);
//   for (int i = 0; i < len; i++) res[i] = *(ptr + ((len - 1) - i));
//   res[len] = '\0';
//   return res;
// }

// If get \0, return string, wich contain only \0
char *GetChar(int wchar) {
  char *res = malloc(2);
  res[0] = wchar;
  res[1] = '\0';
  return res;
}
