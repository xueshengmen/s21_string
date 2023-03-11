#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#include <stdarg.h>
#include <stdlib.h>

#include "s21_common.h"
#include "s21_string.h"

/*
 *  Stores printing parameters
 */
typedef struct ScanParams {
  int i;
  int read_symbols;
  int read_specs;
  char symbol;
  int star;
  int width;
  int lenghtInt;
  int lenghtDouble;
  int base;
} ScanParams;

#define SCAN_SPECIAL_SYMBOLS_COUNT 4

extern char scan_special_symbols[SCAN_SPECIAL_SYMBOLS_COUNT];

/**************************************
 *        Function definitions        *
 *************************************/

/*
 *  Reads formatted input from a string
 */
void s21_sscanf_internal(const char *str, const char *format, va_list *arg_ptr,
                         ScanParams *params);
void SetDefaultScanParams(ScanParams *params);
int IsEmpty(const char *str);

/*
 *  Gets all spec params and returns it's type back
 */
Specs GetScanSpec(const char *format, ScanParams *params);
int IsScanSpecialSymbol(char symbol);

/* Reads from str until str[i] isn't expected for SomeSpec funtion */
int PrepareForSomeSpec(const char *str, ScanParams *params);
int PrepareForFSpec(const char *str, ScanParams *params);
void PrepareForSSpec(const char *str, ScanParams *params);

/*
 *   Definiton of functions - entry points for applying specifiers
 */

int GetNonSpec(const char *str, ScanParams *params);
void GetCSpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetSSpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetPSpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetDSpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetNSpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetUSpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetISpec(const char *str, ScanParams *params, va_list *arg_ptr);
void GetFSpec(const char *str, ScanParams *params, va_list *arg_ptr);

/*
 *   Setter functions
 */

void SetIntValue(long long value, ScanParams *params, va_list *arg_ptr);
void SetUIntValue(long long value, ScanParams *params, va_list *arg_ptr);
void SetFloatingPointValue(char *value_string, int negative, ScanParams *params,
                           va_list *arg_ptr);

/*
 *   Getter functions
 */

void GetFStr(const char *src, char *dst, ScanParams *params);

/*
 *   Definition of converter functions
 */

long long StrToDec(const char *str, ScanParams *params, int negative);
long long StrToHex(const char *str, ScanParams *params, int negative);
long long StrToOct(const char *str, ScanParams *params, int negative);

int AcceptSign(const char *str, ScanParams *params);
int IsSpecialFloat(const char *str, ScanParams *params);
int IsInf(const char *str, ScanParams *params);
int IsNan(const char *str, ScanParams *params);
int IsSpace(char symbol);

#endif  // SRC_SSCANF_H_
