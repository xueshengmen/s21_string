#include "s21_sprintf.h"

char* AddSymbAtBegining(char* dest, char symb) {
  char* res = malloc(s21_strlen(dest) + 2);
  int i = 0;
  res[i++] = symb;
  for (int j = 0; j < s21_strlen(dest); j++, i++) {
    res[i] = dest[j];
  }
  res[i] = '\0';
  free(dest);
  return res;
}

void WriteResultString(char* str, char* dest, PrintParams* params) {
  int current = params->written_symbols;
  int str_len = s21_strlen(dest);

  for (int i = 0; i < str_len; i++) str[current++] = dest[i];
  str[current] = '\0';

  free(dest);  // если будет статически заданная строка - упадёт invalid pointer
               // обработать коды возврата

  params->written_symbols = current;
}

char* AddSymbArrayToStr(char* dest, int dest_position, char* symb_array) {
  // Handle \0 case
  int dest_len = s21_strlen(dest);
  int symb_array_len = s21_strlen(symb_array);
  char* res = malloc(dest_len + symb_array_len + 1);

  if (dest_position == LEFT) {
    s21_strcpy(res, dest);
    s21_strcat(res, symb_array);
  } else if (dest_position == RIGHT) {
    s21_strcpy(res, symb_array);
    s21_strcat(res, dest);
  }

  res[dest_len + symb_array_len] = '\0';
  free(dest);
  free(symb_array);
  return res;
}

char* GetSymbolsArray(char symb, int len) {
  len = len < 0 ? 0 : len;
  char* res = malloc(len + 1);
  for (int i = 0; i < len; i++) {
    res[i] = symb;
  }
  res[len] = '\0';
  return res;
}

int GetSymbPosition(const char* str, char symb) {
  int idx = -1;
  int str_len = s21_strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] == symb) {
      idx = i;
      break;
    }
  }
  return idx;
}

int IsCorrespond(Specs type, int count, ...) {
  int res = 0;
  va_list(ptr);
  va_start(ptr, count);
  for (; count > 0; count--) {
    Specs tmp = va_arg(ptr, Specs);
    if (type == tmp) {
      res = 1;
      break;
    }
  }
  return res;
}

char* RemoveCharFromStr(char* str, char chr, int count_of_chr) {
  int str_len = s21_strlen(str);
  char* res = malloc(str_len + 1 - count_of_chr);
  int j = 0;
  for (int i = 0; i < str_len; i++, j++) {
    if (str[i] != chr)
      res[j] = str[i];
    else
      j--;
  }
  res[j] = '\0';
  free(str);
  return res;
}

int IsNegative(double x) {
  return (*((unsigned long long*)&x) & SIGN_64) == SIGN_64;
}

int PointOrZeroAndNotLast(char* str, int start) {
  return (str[start] == '0' || str[start] == '.') && start != 0;
}

int NotPointOrZeroAndNotLast(char* str, int start) {
  return str[start] == '0' && str[start] != '.' && start != 0;
}

char* RemoveLeadingZerosFrom(char* str, int start, StoppPredicate pred) {
  char* res = str;
  int str_len = s21_strlen(str);
  int buff_size = 0;
  char* buff = NULL;

  if (start + 1 != str_len) {  // check that start not the last symb, it means
                               // we need to safe part after start
    buff_size =
        str_len - (start + 1);  // buffer for symbols, that contains after start
    buff = malloc(buff_size + 1);
    for (int i = 0; i <= buff_size; i++) {
      buff[i] = str[start + 1 + i];  // copy symbols after start
    }
    buff[buff_size] = '\0';
  }
  // walking from right to left (<-)
  while (pred(str, start)) {
    str[start--] = '\0';
  }

  if (pred == NotPointOrZeroAndNotLast && str[start] == '.')
    str[start--] = '\0';

  int res_len = s21_strlen(str);  // find new len
  if (res_len != str_len) {       // check, that leading zeros removed
    res = malloc(res_len + buff_size + 1);
    s21_strcpy(res, str);
    if (buff) s21_strcat(res, buff);
    res[res_len + buff_size] = '\0';
    free(str);
  }
  if (buff) free(buff);
  return res;
}

char* ApplySspecAccuracy(char* dest, PrintParams* params) {
  char* res = dest;
  if (params->accuracy < s21_strlen(dest) && params->set_accuracy) {
    res = malloc(params->accuracy + 1);
    for (int i = 0; i < params->accuracy; i++) res[i] = dest[i];
    res[params->accuracy] = '\0';
    free(dest);
  }
  return res;
}

char* ApplyDspecAccuracy(char* dest, PrintParams* params) {
  char* res = dest;
  if (params->set_accuracy) {
    int place_for_sign = dest[0] == '-' ? 1 : 0;
    int src_len = s21_strlen(dest);
    char* zeros_aray =
        GetSymbolsArray('0', params->accuracy - src_len + place_for_sign);
    res = AddSymbArrayToStr(dest, RIGHT, zeros_aray);
    res = HandleZeroAndSign(res, params);
  }
  return res;
}

char* GetDynamicStrFromConstStr(const char* str) {
  int str_len = s21_strlen(str);
  char* res = malloc(str_len + 1);
  s21_strcpy(res, str);
  res[str_len] = '\0';
  return res;
}

char* GetDynamicStrFromSymb(char chr) {
  int res_len = chr == '\0' ? 1 : 2;
  char* res = malloc(res_len);
  res[0] = chr;
  if (res_len == 2) res[1] = '\0';
  return res;
}