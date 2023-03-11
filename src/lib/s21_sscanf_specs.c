#include "s21_sscanf.h"

int GetNonSpec(const char *str, ScanParams *params) {
  int status = 1;

  if (IsSpace(params->symbol)) {
    while (IsSpace(str[params->i])) {
      params->i++;
    }
  } else {
    if (str[params->i] == params->symbol) {
      params->i++;
    } else {
      status = 0;
    }
  }

  return status;
}

void GetCSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  if (params->star) {
    params->i++;
  } else {
    char *ptr = va_arg(*arg_ptr, char *);
    *ptr = str[params->i++];
    params->read_symbols++;
  }
}

void GetSSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  int i = 0;

  if (params->star) {
    while (!IsSpace(str[params->i]) && str[params->i] != '\0') {
      i++;
      params->i++;
    }
  } else {
    char *ptr = va_arg(*arg_ptr, char *);

    ptr[0] = '\0';
    while (!IsSpace(str[params->i]) && str[params->i] != '\0' &&
           params->width != 0) {
      ptr[i++] = str[params->i++];
      params->read_symbols++;
      params->width--;
    }
    ptr[i] = '\0';
  }
}

void GetPSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  long long hex = StrToHex(str, params, 0);

  if (!params->star) {
    void **ptr = va_arg(*arg_ptr, void **);
    *ptr = (void *)hex;
  }
}

void GetDSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  void *ptr = NULL;

  int negative = AcceptSign(str, params);

  long long result = 0;
  if (params->base == 16) {
    result = StrToHex(str, params, negative);
  } else if (params->base == 8) {
    result = StrToOct(str, params, negative);
  } else {
    result = StrToDec(str, params, negative);
  }

  SetIntValue(result, params, arg_ptr);
}

void GetNSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  long long result = params->i;
  SetIntValue(result, params, arg_ptr);
}

void GetUSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  void *ptr = NULL;

  int negative = AcceptSign(str, params);
  unsigned long long result = 0;
  result = StrToDec(str, params, negative);

  SetUIntValue(result, params, arg_ptr);
}

void GetISpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  void *ptr = NULL;

  int negative = AcceptSign(str, params);

  long long result = 0;
  if (str[params->i] == '0' &&
      (str[params->i + 1] == 'x' || str[params->i + 1] == 'X')) {
    result = StrToHex(str, params, negative);
  } else if (str[params->i] == '0') {
    result = StrToOct(str, params, negative);
  } else {
    result = StrToDec(str, params, negative);
  }

  SetIntValue(result, params, arg_ptr);
}

void GetFSpec(const char *str, ScanParams *params, va_list *arg_ptr) {
  int status = 1;
  void *ptr = NULL;

  int negative = AcceptSign(str, params);

  char buffer[100];
  GetFStr(str, buffer, params);

  SetFloatingPointValue(buffer, negative, params, arg_ptr);
}

int AcceptSign(const char *str, ScanParams *params) {
  int negative = 0;

  if (str[params->i] == '-') {
    negative = 1;
    params->i++;
    params->read_symbols++;
    params->width--;
  } else if (str[params->i] == '+') {
    params->width--;
    params->i++;
  }

  return negative;
}

void GetFStr(const char *src, char *dst, ScanParams *params) {
  int status = 1, j = 0;

  if (IsInf(src, params)) {
    dst[0] = 'i';
    dst[1] = 'n';
    dst[2] = 'f';
    dst[3] = '\0';
    params->i += 3;
  } else if (IsNan(src, params)) {
    dst[0] = 'n';
    dst[1] = 'a';
    dst[2] = 'n';
    dst[3] = '\0';
    params->i += 3;
  } else {
    while (params->width != 0 && status) {
      if (IsFloat(src[params->i])) {
        dst[j++] = src[params->i++];
      } else {
        status = 0;
      }
    }
    dst[j] = '\0';
  }
}

int IsSpecialFloat(const char *str, ScanParams *params) {
  int not_special = 0, infinity = 1, nan = 2;
  int result = not_special;

  if (IsInf(str, params)) {
    result = infinity;
  } else if (IsNan(str, params)) {
    result = nan;
  }

  return result;
}

int IsInf(const char *str, ScanParams *params) {
  int status = 1;

  for (int i = 0; i < 3 && status; i++) {
    if ((i == 0 && !(str[params->i + i] == 'i' || str[params->i + i] == 'I')) ||
        (i == 1 && !(str[params->i + i] == 'n' || str[params->i + i] == 'N')) ||
        (i == 2 && !(str[params->i + i] == 'f' || str[params->i + i] == 'F'))) {
      status = 0;
    }
  }

  return status;
}

int IsNan(const char *str, ScanParams *params) {
  int status = 1;

  for (int i = 0; i < 3 && status; i++) {
    if ((i == 0 && !(str[params->i + i] == 'n' || str[params->i + i] == 'N')) ||
        (i == 1 && !(str[params->i + i] == 'a' || str[params->i + i] == 'A')) ||
        (i == 2 && !(str[params->i + i] == 'n' || str[params->i + i] == 'N'))) {
      status = 0;
    }
  }

  return status;
}

int IsSpace(char symbol) {
  int status = 0;

  if ((symbol == ' ') || (symbol == '\t') || (symbol == '\n')) {
    status = 1;
  }

  return status;
}
