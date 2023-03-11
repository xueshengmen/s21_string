#include "s21_sscanf.h"

int PrepareForSomeSpec(const char *str, ScanParams *params) {
  int status = 1;

  while (((IsDigit(str[params->i], params->base) == 0) &&
          (str[params->i] != '+') && (str[params->i] != '-')) &&
         (status)) {
    if (str[params->i] != ' ' && str[params->i] != '\t' &&
        str[params->i] != '\n')
      status = 0;

    if (str[params->i] != '\0') {
      params->i++;
    }
  }

  if ((str[params->i] == '+') || (str[params->i] == '-')) {
    if ((str[(params->i) + 1] == '+') || (str[(params->i) + 1] == '-') ||
        params->width == 1)
      status = 0;
  }
  return status;
}

int PrepareForFSpec(const char *str, ScanParams *params) {
  int status = 1;

  while (!((IsDigit(str[params->i], 10) || str[params->i] == '+' ||
            str[params->i] == '-' || IsSpecialFloat(str, params)) &&
           (status))) {
    if (str[params->i] != ' ' && str[params->i] != '\t' &&
        str[params->i] != '\n')
      status = 0;

    if (str[params->i] != '\0') {
      params->i++;
    } else {
      break;
    }
  }

  return status;
}

void PrepareForSSpec(const char *str, ScanParams *params) {
  while ((str[params->i] == ' ') || (str[params->i] == '\t') ||
         (str[params->i] == '\n')) {
    params->i++;
  }
}