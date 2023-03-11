#include "s21_sscanf.h"

#include <stdio.h>
int s21_sscanf(const char *str, const char *format, ...) {
  int read_specs = 0;
  va_list arg_ptr;
  ScanParams params;
  params.i = 0;
  params.read_specs = read_specs;
  params.read_symbols = 0;

  SetDefaultScanParams(&params);
  va_start(arg_ptr, format);

  if (!IsEmpty(str)) {
    s21_sscanf_internal(str, format, &arg_ptr, &params);
    read_specs = params.read_specs;
  } else {
    read_specs = EOF;
  }

  va_end(arg_ptr);

  return read_specs;
}

void SetDefaultScanParams(ScanParams *params) {
  params->symbol = 0;  // default 0 means no symbol was given
  params->star = 0;    // default 0 means no star was set
  params->width = -1;  // default -1 width means no fixed width set
  // default 0 lenght means neither short or long set
  // < 0 - short; > 0 - long
  params->lenghtInt = 0;
  params->lenghtDouble = 0;
  params->base = 10;
}

int IsEmpty(const char *str) {
  int status = 1;

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
      status = 0;
    }
  }

  return status;
}

void s21_sscanf_internal(const char *str, const char *format, va_list *arg_ptr,
                         ScanParams *params) {
  Specs spec;
  int status = 1, error_occured = 0;

  while (((spec = GetScanSpec(format, params)) != End) && (status)) {
    switch (spec) {
      case NonSpec:
        status = GetNonSpec(str, params);
        break;
      case CSpec:
        status = str[params->i];
        if (status) GetCSpec(str, params, arg_ptr);
        break;
      case ISpec:
        status = PrepareForSomeSpec(str, params);
        if (status) GetISpec(str, params, arg_ptr);
        break;
      case xSpec:
      case XSpec:
      case OSpec:
      case DSpec:
        status = PrepareForSomeSpec(str, params);
        if (status) GetDSpec(str, params, arg_ptr);
        break;
      case NSpec:
        GetNSpec(str, params, arg_ptr);
        break;
      case fSpec:
      case gSpec:
      case GSpec:
      case eSpec:
      case ESpec:
        status = PrepareForFSpec(str, params);
        if (status) GetFSpec(str, params, arg_ptr);
        break;
      case SSpec:
        PrepareForSSpec(str, params);
        GetSSpec(str, params, arg_ptr);
        break;
      case USpec:
        status = PrepareForSomeSpec(str, params);
        if (status) GetUSpec(str, params, arg_ptr);
        break;
      case PSpec:
        status = PrepareForSomeSpec(str, params);
        if (status) GetPSpec(str, params, arg_ptr);
        break;
    }

    if (!status) error_occured = 1;
    if (spec != NonSpec && spec != NSpec && !params->star && status)
      params->read_specs++;
    if (str[params->i] == '\0') {
      if (spec == NonSpec && status) params->read_specs = EOF;
      status = 0;

      if (error_occured) params->i = 0;
      do {
        spec = GetScanSpec(format, params);
        if (spec == NSpec) GetNSpec(str, params, arg_ptr);
      } while (spec != End);
    }

    SetDefaultScanParams(params);
  }
}

Specs GetScanSpec(const char *format, ScanParams *params) {
  Specs spec = NonSpec;
  static size_t i = 0;

  if (format[i] == '%') {
    while (!IsSpec(format[++i]) && IsScanSpecialSymbol(format[i])) {
      if (format[i] == '*') {
        params->star = 1;
      } else if (format[i] == 'h') {
        // Set lenght as short
        params->lenghtInt--;
      } else if (format[i] == 'l') {
        // Set lenght as long
        params->lenghtInt++;
        params->lenghtDouble = 1;
      } else if (format[i] == 'L') {
        params->lenghtDouble = 2;
      } else if (IsDigit(format[i], 10)) {
        // Reads width and writes to width variable
        params->width = format[i] - '0';
        while (IsDigit(format[++i], 10))
          params->width = params->width * 10 + (format[i] - '0');
        if (params->width == 0) params->width = -1;
        i--;
      }
    }
    if (IsSpec(format[i])) {
      spec = format[i];
      if (spec == xSpec || spec == XSpec || spec == PSpec) params->base = 16;
      if (spec == OSpec) params->base = 8;
    } else {
      params->symbol = format[i];
    }
  } else if (format[i] == '\0') {
    spec = End;
    i = -1;
  } else {
    params->symbol = format[i];
  }

  i++;  // Moves right over format string for next iteration

  return spec;
}

int IsScanSpecialSymbol(char symbol) {
  int result = 0;

  if (IsDigit(symbol, 10)) {
    result = 1;
  }

  for (int i = 0; i < SCAN_SPECIAL_SYMBOLS_COUNT; i++) {
    if (symbol == scan_special_symbols[i]) {
      result = 1;
    }
  }

  return result;
}

char scan_special_symbols[SCAN_SPECIAL_SYMBOLS_COUNT] = {
    [0] = '*', [1] = 'h', [2] = 'l', [3] = 'L'};
