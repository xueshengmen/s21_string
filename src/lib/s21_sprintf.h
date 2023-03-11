#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_common.h"
#include "s21_string.h"

/*
 *  Stores printing parameters
 */
typedef struct PrintParams {
  int written_symbols;
  char symbol;
  int flags;
  int width;
  int set_accuracy;
  int accuracy;
  int lenghtInt;
  int lenghtDouble;
} PrintParams;

#define MINUSFLAG 0b00000001
#define PLUSFLAG 0b00000010
#define SPACEFLAG 0b00000100
#define STARFLAG 0b00001000
#define DOTFLAG 0b00010000
#define DOTSTARFLAG 0b00100000
#define ZEROFLAG 0b01000000
#define HASHFLAG 0b10000000

#define BUFFERSIZE 256
#define DEFAULT_ACCURACY 6

#define LEFT 0
#define RIGHT 1

#define SIGN_64 0x8000000000000000
#define EXPONENT_64 0x7FF0000000000000
#define MANTISSA_64 0x000FFFFFFFFFFFFF
#define CONSTANT_MANTIS_DOUBLE 1023
#define MANTISSA_SIZE 52
#define EXPONENT_SIZE 11

#define PRINT_SPECIAL_SYMBOLS_COUNT 10

extern char print_special_symbols[PRINT_SPECIAL_SYMBOLS_COUNT];
extern char *const fract_value[73];

/**************************************
 *        Function definitions        *
 *************************************/

/*
 *  Sends formatted output to a string pointed to, by str.
 */
void s21_sprintf_internal(char *str, const char *format, va_list *arg_ptr,
                          PrintParams *params);
void SetDefaultPrintParams(PrintParams *params);

/*
 *  Gets all spec params and returns it's type back
 */
Specs GetPrintSpec(const char *format, PrintParams *params);
int IsPrintSpecialSymbol(char symbol);

/*
 *   Definiton of functions - entry points for applying specifiers
 */

void ApplyNonSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyCSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyDSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyISpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyFSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplySSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyUSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyGSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyESpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyXSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyOSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyNSpec(char *str, PrintParams *params, va_list *arg_ptr);
void ApplyPSpec(char *str, PrintParams *params, va_list *arg_ptr);

/*
 *   Definition of converter functions
 */

void Reverse(char *str, int sz);
char *WholePartToString(long long int num, int base);
char *UIntToString(unsigned long long int num, int base, PrintParams *params);
char *DoubleToString(double num, int accuracy, PrintParams *params);

unsigned long long GetMantis(unsigned long long num);
int GetExponent(unsigned long long num);
int GetWHoleAndFractPartFromMantis(unsigned long long mantis, int exponent,
                                   unsigned long long *whole_part,
                                   unsigned long long *fract_part);
void SumForChar(char **res, const char *str);
void RecursiveIncrement(char *fract_part, int accuracy);
char *CutOffInsignificantPart(char *fract_part, int accuracy);
char *GetFractPartInString(unsigned long long fract_part, int exponent,
                           int shift, int accuracy);
char *CheckSpecialValue(double num);
char *ConcatenateWholeAndFractParts(char *whole_part_str, char *fract_part_str);
int DoubleToExponentialNotation(double *num, PrintParams *params);

char *RemoveCharFromStr(char *str, char chr, int count_of_chr);
int IsNegative(double x);

char *DoubleToExponentialForm(double num, int accuracy, int *exponent,
                              PrintParams *params);
char *UniteMantisAndExponent(double num, char *double_str, char *exponent_str);
char *GetExponentForExponentialForm(int exponent, PrintParams *params);
char *GetMantisForExponentialForm(char *double_str, int accuracy);
//  Возвращает цифры мантисы без точки и считает экспоненту
char *PrepareMantis(double num, int accuracy, PrintParams *params,
                    int *exponent);
void RoundForExp(char *fract_part, int accuracy, int other_zero, int *exponent);
int OtherZero(char *double_str, int start);
int GetFirstNotNullDigitIndex(char *str);

typedef int (*StoppPredicate)(char *, int);

int PointOrZeroAndNotLast(char *str, int start);
int NotPointOrZeroAndNotLast(char *str, int start);
char *RemoveLeadingZerosFrom(char *str, int start, StoppPredicate pred);

/*
 *   Definition of applying flags functions
 */
char *ApplyFlags(Specs type, char *dest, PrintParams *params);
void StarPriority(PrintParams *params, va_list *arg_ptr);
void ApplyStarFlags(PrintParams *params, va_list *arg_ptr);
char *ApplyMinusFlag(char *dest, PrintParams *params);
char *ApplyWidth(char *dest, PrintParams *params);
char *ApplyZeroFlag(Specs type, char *dest, PrintParams *params);
char *HandleZeroAndHashFlagHex(char *dest, PrintParams *params);
char *HandleZeroAndSign(char *dest, PrintParams *params);
char *ApplyHashFlag(Specs type, char *dest, PrintParams *params);
char *ApplyHashFlagOctal(char *dest, PrintParams *params);
char *ApplyHashFlagHex(Specs type, char *dest, PrintParams *params);
char *ApplyHashFlagDouble(char *dest, PrintParams *params);
void WriteResultString(char *str, char *dest, PrintParams *params);
char *ApplyPlusFlag(char *dest, PrintParams *params);
char *ApplySpaceFlag(char *dest, PrintParams *params);

void WriteExponent(char *dest, int exponent, PrintParams *params);
char *AddSymbAtBegining(char *dest, char symb);
void WriteResultString(char *str, char *dest, PrintParams *params);
char *AddSymbArrayToStr(char *dest, int dest_position, char *symb_array);
char *GetSymbolsArray(char symb, int len);
int GetSymbPosition(const char *str, char symb);
int IsCorrespond(Specs type, int count, ...);
char *ApplySspecAccuracy(char *dest, PrintParams *params);
char *ApplyDspecAccuracy(char *dest, PrintParams *params);

long long int GetIntValue(PrintParams *params, va_list *arg_ptr);
unsigned long long int GetUIntValue(PrintParams *params, va_list *arg_ptr);
double GetDoubleValue(PrintParams *params, va_list *arg_ptr);
char *GetChar(int wchar);
char *GetDynamicStrFromConstStr(const char *str);
char *GetDynamicStrFromSymb(char chr);

#endif  // SRC_SPRINTF_H_
