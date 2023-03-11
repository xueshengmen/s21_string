#include "s21_string.h"

#include <stdlib.h>

void *s21_memchr(const void *str, int symbol, size_t length) {  // Tested
  void *result = NULL;
  unsigned char *BuffStr = (unsigned char *)str;

  for (size_t n = 0; n < length && result == NULL && BuffStr; n++) {
    if (*BuffStr == (unsigned char)symbol) result = BuffStr;
    BuffStr++;
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, size_t length) {  // Tested
  char *BuffStr1 = (char *)str1;
  char *BuffStr2 = (char *)str2;
  size_t n;
  for (n = 0; n < length && (BuffStr1[n] == BuffStr2[n]); n++)
    ;
  return (n == length) ? 0 : (BuffStr1[n] - BuffStr2[n]);
}

void *s21_memcpy(void *str1, const void *str2,
                 size_t lenght) {  // Tested, found bugs
  size_t i;
  char *sstr1 = (char *)str1;
  const char *sstr2 = (char *)str2;
  for (i = 0; i < lenght; ++i) *sstr1++ = *sstr2++;

  return str1;
}

void *s21_memmove(void *str1, const void *str2, size_t lenght) {  // Tested
  if (str1 < str2) {
    char *BuffStr1 = (char *)str1;
    char *BuffStr2 = (char *)str2;

    while (lenght--) *BuffStr1++ = *BuffStr2++;
  } else {
    char *BuffStr1 = (char *)str1 + lenght;
    char *BuffStr2 = (char *)str2 + lenght;

    while (lenght--) *--BuffStr1 = *--BuffStr2;
  }

  return (void *)str1;
}

void *s21_memset(void *str, int ch, size_t lenght) {  // Tested
  if (str) {
    char *tmp_mem = (char *)str;
    while (lenght--) *tmp_mem++ = ch;
  }

  return str;
}

char *s21_strcat(char *dest, const char *src) {  // Tested
  char *result = dest;
  size_t dest_len = s21_strlen(dest);
  size_t src_len = s21_strlen(src);

  for (size_t i = 0; i <= src_len; i++) {
    result[dest_len + i] = src[i];
  }

  return result;
}

char *s21_strncat(char *dest, const char *src, size_t n) {  // Tested
  char *result = dest;
  size_t dest_len = s21_strlen(dest);
  size_t src_len = s21_strlen(src);

  for (size_t i = 0; i < src_len && i <= n; i++) {
    if (i < n)
      result[dest_len + i] = src[i];
    else
      result[dest_len + i] = '\0';
  }

  return result;
}

char *s21_strchr(const char *str, int c) {  // Tested
  char *result = NULL;
  char *BuffStr = (char *)str;
  int found = 0;

  for (int i = 0; i < s21_strlen(BuffStr) + 1 && !found; i++) {
    if (BuffStr[i] == c) {
      result = &BuffStr[i];
      found = 1;
    }
  }

  return result;
}

int s21_strcmp(const char *str1, const char *str2) {  // Tested
  while ((*str1 == *str2) && (*str1 != '\0')) {
    str1++;
    str2++;
  };

  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2,
                size_t n) {  // Tested, found bugs
  const char *end = str1 + n;
  int result = 0;
  for (; result == 0 && str1 != end && (*str1 || *str2);
       result = *(str1++) - *(str2++))
    ;
  return result;
}

char *s21_strcpy(char *dest, const char *src) {  // Tested
  char *result = dest;
  size_t src_len = s21_strlen(src);

  for (size_t i = 0; i <= src_len; i++) dest[i] = src[i];

  return result;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  int size = s21_strlen(src);
  char *buff = dest;
  if (size > n) {
    s21_memcpy(buff, src, n);
  } else {
    s21_memcpy(buff, src, size);
    int offset = n - size;
    char *buff2 = buff + size;
    while (offset--) *buff2++ = '\0';
  }
  return dest;
}

size_t s21_strcspn(const char *str1, const char *str2) {  // Tested
  size_t result = 0;
  int CheckSymbol = 0;
  char *BuffStr1 = (char *)str1;
  char *BuffStr2 = (char *)str2;

  for (int i = 0; BuffStr1[i] != '\0' && CheckSymbol == 0; i++) {
    for (int j = 0; BuffStr2[j] != '\0' && CheckSymbol == 0; j++) {
      if (BuffStr2[j] == BuffStr1[i]) CheckSymbol++;
    }
    if (CheckSymbol == 0) result++;
  }
  return result;
}

size_t s21_strlen(const char *str) {  // Tested
  size_t result = 0;

  if (str) {
    for (size_t i = 0; str[i]; i++) result++;
  }
  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {  // Tested
  char *result = NULL;
  char *BuffStr1 = (char *)str1;
  char *BuffStr2 = (char *)str2;

  for (int i = 0; BuffStr1[i] != '\0' && result == NULL; i++)
    for (int j = 0; BuffStr2[j] != '\0' && result == NULL; j++)
      if (BuffStr2[j] == BuffStr1[i]) result = &BuffStr1[i];

  return result;
}

char *s21_strrchr(const char *str, int c) {  // Tested, found bugs
  char *buff = (char *)str;
  char *res = NULL;
  size_t buff_len = s21_strlen(buff);

  for (int j = buff_len; j >= 0 && !res; j--)
    if (buff[j] == c) res = buff + j;
  return res;
}

size_t s21_strspn(const char *str1, const char *str2) {  // Tested, found bugs
  size_t len;
  const char *buff;
  for (len = 0; *str1; str1++, len++) {
    for (buff = str2; *buff && *buff != *str1; buff++)
      ;
    if (!*buff) break;
  }
  return len;
}

char *s21_strstr(const char *haystack,
                 const char *needle) {  // Tested, found bugs
  size_t n = s21_strlen(needle);
  char *res = NULL;
  while ((*haystack || (haystack[0] == needle[0])) && res == NULL) {
    if (!s21_memcmp(haystack, needle, n)) res = (char *)haystack;
    haystack++;
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {  // Tested
  static char *ptr, *last_ptr;
  static int delim_not_exist, next_null;
  if (str) {
    ptr = str + s21_strspn(str, delim);  // move pointer to the first litteral
    last_ptr = str + s21_strlen(str);    // set the end of the string
    next_null = 0;
  }
  char *res = NULL;
  if (!(ptr >= last_ptr || next_null)) {
    delim_not_exist = 1;
    size_t delim_step;
    int i;
    for (i = 0; ptr[i] && delim_not_exist;
         i++) {  // iterate over the string until we define no delim in string
      delim_step = s21_strspn(ptr + i, delim);
      if (delim_step) {
        delim_not_exist = 0;
        for (size_t j = i; j < i + delim_step; j++)
          ptr[j] = '\0';  // iterate over delim in the string and set the char
                          // by null
        i--;
      }
    }
    if (str && delim_not_exist) next_null = 1;  // case no delim in string
    res = ptr;
    ptr += delim_step + i;  // move pointer to the start next segment
  }
  return res;
}

char *s21_strerror(int errnum) {  // Tested
  char *res = NULL;
  static char s21_undef_buffer[4096] = {'\0'};
  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE) {
#if defined(__APPLE__)
    s21_sprintf(s21_undef_buffer, "Unknown error: %d",
                errnum);  // Change on s21_sprintf
#else
    s21_sprintf(s21_undef_buffer, "Unknown error %d",
                errnum);  // Change on s21_sprintf
#endif
    res = s21_undef_buffer;
  } else {
    res = (char *)s21_sys_errlist[errnum];
  }
  return res;
}

void *s21_to_upper(const char *str) {
  char *res = NULL;
  if (str != NULL) {
    res = malloc(sizeof(char) * s21_strlen(str) + 1);
    if (res) {
      int i = 0;
      for (; str[i] != '\0'; i++) {
        if (str[i] <= 'z' && str[i] >= 'a') {
          res[i] = str[i] - 'a' + 'A';
        } else {
          res[i] = str[i];
        }
      }
      res[i] = '\0';
    }
  }
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = NULL;
  if (str != NULL) {
    res = malloc(sizeof(char) * s21_strlen(str) + 1);
    if (res) {
      int i = 0;
      for (; str[i] != '\0'; i++) {
        if (str[i] <= 'Z' && str[i] >= 'A') {
          res[i] = str[i] + 'a' - 'A';
        } else {
          res[i] = str[i];
        }
      }
      res[i] = '\0';
    }
  }
  return res;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *res = NULL;
  if (str == NULL) str = "";
  if (src != NULL)
    if (start_index <= s21_strlen(src) && start_index >= 0) {
      res = malloc(sizeof(char) * s21_strlen(src) +
                   sizeof(char) * s21_strlen(str) + 1);
      size_t len =
          sizeof(char) * s21_strlen(src) + sizeof(char) * s21_strlen(str) + 1;
      for (int i = 0; i < len; i++) res[i] = '\0';
      if (res != NULL) {
        int i = 0, pos = 0;
        size_t src_str_len = s21_strlen(src) + s21_strlen(str);
        size_t str_len = s21_strlen(str);
        for (; i < src_str_len; i++) {
          if (i == start_index) {
            for (; pos < str_len; pos++) {
              res[i + pos] = str[pos];
            }
            i += pos;
          }
          res[i] = src[i - pos];
        }
      }
    }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = NULL;
  if (trim_chars == NULL) trim_chars = "";
  if (src != NULL) {
    res = malloc(sizeof(char) * s21_strlen(src) + 1);

    int begin = s21_strlen(src), end = 0, check;
    for (int k = 0; src[k] != '\0'; k++) {
      check = 1;
      for (int i = 0; trim_chars[i] != '\0'; i++) {
        if (src[k] == trim_chars[i]) check = 0;
      }

      if (check == 1 && begin == s21_strlen(src)) {
        begin = k - 1;
      } else if (check == 1) {
        end = k;
      }
    }

    int i = 0, pos = 0, diff = 1;
    for (; src[i] != '\0'; i++) {
      for (int j = 0;
           trim_chars[j] != '\0' && (i <= begin || i > end) && diff == 1; j++) {
        if (src[i] == trim_chars[j]) {
          pos++;
          diff = 0;
        }
      }
      if (diff == 0) {
        diff = 1;
      } else {
        res[i - pos] = src[i];
      }
    }
    res[i - pos] = '\0';
  }
  return res;
}
