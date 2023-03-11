#include "s21_sprintf.h"

void ApplyNonSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  char *dest = GetDynamicStrFromSymb(params->symbol);
  dest = ApplyFlags(CSpec, dest, params);
  WriteResultString(str, dest, params);
}

void ApplyCSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  char *chr = GetChar(va_arg(*arg_ptr, int));
  if (s21_strlen(chr) == 0) {  // Handle \0
    int current = params->written_symbols;
    str[current] = '\0';
    params->written_symbols += params->width == 0 ? 1 : params->width;
    free(chr);
  } else {
    chr = ApplyFlags(CSpec, chr, params);
    WriteResultString(str, chr, params);
  }
}

void ApplySSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  char *orig = va_arg(*arg_ptr, char *);
  char *dest;
  if (orig) {
    dest = GetDynamicStrFromConstStr(orig);
  } else {
    dest = GetDynamicStrFromConstStr("(null)");
  }

  dest = ApplySspecAccuracy(dest, params);
  dest = ApplyFlags(SSpec, dest, params);
  WriteResultString(str, dest, params);
}

void ApplyDSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  long long int value = GetIntValue(params, arg_ptr);

  char *dest;
  if (params->set_accuracy && value == 0 && params->accuracy >= 0) {
    dest = GetDynamicStrFromSymb('\0');
  } else if (value == LONG_MIN) {
    dest = GetDynamicStrFromConstStr("-9223372036854775808");
  } else {
    dest = WholePartToString(value, 10);
  }

  dest = ApplyDspecAccuracy(dest, params);

  dest = ApplyFlags(DSpec, dest, params);
  WriteResultString(str, dest, params);
}

void ApplyUSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  unsigned long long int value = GetUIntValue(params, arg_ptr);

  char *dest;
  if (params->set_accuracy && value == 0) {
    dest = GetDynamicStrFromSymb('\0');
  } else if (value == LONG_MIN) {
    dest = GetDynamicStrFromConstStr("-9223372036854775808");
  } else {
    dest = UIntToString(value, 10, params);
  }

  dest = ApplyDspecAccuracy(dest, params);

  dest = ApplyFlags(USpec, dest, params);
  WriteResultString(str, dest, params);
}

void ApplyFSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  double num = GetDoubleValue(params, arg_ptr);
  char *double_str = DoubleToString(num, params->accuracy, params);
  double_str = ApplyFlags(fSpec, double_str, params);

  WriteResultString(str, double_str, params);
}

void ApplyESpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  double num = GetDoubleValue(params, arg_ptr);
  int exponent = 0;

  char *double_str =
      DoubleToExponentialForm(num, params->accuracy, &exponent, params);
  double_str = ApplyFlags(eSpec, double_str, params);
  WriteResultString(str, double_str, params);
}

void ApplyGSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  char *res = NULL;
  params->symbol -= 2;  // g->e G->E
  int P = params->accuracy;
  P = P == 0 ? 1 : P;
  int exponent = 0;

  double num = GetDoubleValue(params, arg_ptr);
  char *expon_form =
      DoubleToExponentialForm(num, params->accuracy, &exponent, params);
  free(expon_form);

  // https://stackoverflow.com/questions/54162152/what-precisely-does-the-g-printf-specifier-mean
  if (P > exponent && exponent >= -4) {
    params->accuracy = P - (exponent + 1);
    res = DoubleToString(num, params->accuracy, params);
    int res_len = s21_strlen(res);
    if (!(params->flags & HASHFLAG))
      res = RemoveLeadingZerosFrom(res, res_len - 1, NotPointOrZeroAndNotLast);
    //с конца, пока 0 или точка удаляем
  } else {
    params->accuracy = P - 1;
    res = DoubleToExponentialForm(num, params->accuracy, &exponent, params);
    if (!(params->flags & HASHFLAG))
      res = RemoveLeadingZerosFrom(
          res, GetSymbPosition(res, params->symbol) - 1, PointOrZeroAndNotLast);
    //с позиции e, пока 0 или точка удаляем
  }
  res = ApplyFlags(gSpec, res, params);
  WriteResultString(str, res, params);
}

void ApplyOSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  unsigned long long int value = GetUIntValue(params, arg_ptr);

  char *dest;
  if (params->set_accuracy && value == 0) {
    dest = GetDynamicStrFromSymb('\0');
  } else {
    dest = UIntToString(value, 8, params);
  }

  dest = ApplyDspecAccuracy(dest, params);

  dest = ApplyFlags(OSpec, dest, params);
  WriteResultString(str, dest, params);
}

void ApplyXSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  StarPriority(params, arg_ptr);
  unsigned long long int value = GetUIntValue(params, arg_ptr);
  char *dest;
  if (params->set_accuracy && value == 0) {
    dest = GetDynamicStrFromSymb('\0');
  } else {
    dest = UIntToString(value, 16, params);
  }

  dest = ApplyDspecAccuracy(dest, params);

  dest = ApplyFlags(XSpec, dest, params);
  WriteResultString(str, dest, params);
}

void ApplyPSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  params->flags |= HASHFLAG;
  params->symbol = 'x';

  /* required size for address storage - unsigned long long int */
  params->lenghtInt = 2;

  StarPriority(params, arg_ptr);

  unsigned long long int value = GetUIntValue(params, arg_ptr);
  char *dest;
  if (params->set_accuracy && value == 0) {
    dest = GetDynamicStrFromSymb('\0');
  } else {
    dest = UIntToString(value, 16, params);
  }

  // TO-DO Обработать ситуацию для точности как для ширины
  // Также учитывать что может быть ситуация типа 10.5p
  // То ест просто заменять второй 0 на x не получится

  dest = ApplyDspecAccuracy(dest, params);
  dest = ApplyFlags(PSpec, dest, params);

#ifdef LINUX
  if (value == 0) {
    s21_strcpy(dest, "(nil)");
  }
#endif

  WriteResultString(str, dest, params);
}

/* %n is the only specifier that requires writing multiple characters from the
 * format string. */
/* Any other implementation that allows you to keep the same definition of
 * functions carries  */
/* a number of problems. The optimal solution is to pass format to the function
 * explicitly.   */
// TO-DO Set flags and width to zero
void ApplyNSpec(char *str, PrintParams *params, va_list *arg_ptr) {
  void *value = va_arg(*arg_ptr, void *);
  *((int *)value) = params->written_symbols;
}
