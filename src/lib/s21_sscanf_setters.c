#include "s21_sscanf.h"

void SetIntValue(long long value, ScanParams *params, va_list *arg_ptr) {
  void *ptr;

  if (!params->star) {
    if (params->lenghtInt == 0) {
      ptr = va_arg(*arg_ptr, int *);
      *(int *)ptr = (int)value;
    } else if (params->lenghtInt < 0) {
      ptr = va_arg(*arg_ptr, short *);
      *(short *)ptr = (short)value;
    } else if (params->lenghtInt % 2 == 1) {
      ptr = va_arg(*arg_ptr, long *);
      *(long *)ptr = (long)value;
    } else if (params->lenghtInt % 2 == 0) {
      ptr = va_arg(*arg_ptr, long long *);
      *(long long *)ptr = value;
    }
  }
}

void SetUIntValue(long long value, ScanParams *params, va_list *arg_ptr) {
  void *ptr;

  if (!params->star) {
    if (params->lenghtInt == 0) {
      ptr = va_arg(*arg_ptr, unsigned *);
      *(unsigned *)ptr = (unsigned)value;
    } else if (params->lenghtInt < 0) {
      ptr = va_arg(*arg_ptr, unsigned short *);
      *(unsigned short *)ptr = (unsigned short)value;
    } else if (params->lenghtInt % 2 == 1) {
      ptr = va_arg(*arg_ptr, long *);
      *(unsigned long *)ptr = (unsigned long)value;
    } else if (params->lenghtInt % 2 == 0) {
      ptr = va_arg(*arg_ptr, long long *);
      *(unsigned long long *)ptr = value;
    }
  }
}

void SetFloatingPointValue(char *value_string, int negative, ScanParams *params,
                           va_list *arg_ptr) {
  void *ptr;

  if (!params->star) {
    if (params->lenghtDouble == 0) {
      ptr = va_arg(*arg_ptr, float *);
      float result = strtof(value_string, NULL);
      if (negative) result *= -1;
      *(float *)ptr = result;
    } else if (params->lenghtDouble % 2 == 1) {
      ptr = va_arg(*arg_ptr, double *);
      double result = strtod(value_string, NULL);
      if (negative) result *= -1;
      *(double *)ptr = result;
    } else if (params->lenghtDouble % 2 == 0) {
      ptr = va_arg(*arg_ptr, long double *);
      long double result = strtold(value_string, NULL);
      if (negative) result *= -1;
      *(long double *)ptr = result;
    }
  }
}
