#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/s21_sprintf.h"
#include "s21_string.h"

#define BUFF_SIZE BUFSIZ

#define SPECS_COUNT 16
#define FLAGS_COUNT 5
#define FLAGS_COMBINATION 255
#define LENGTH_COUNT 3
#define ACCURACY_AND_WIDTH_COUNT 100
#define VALUES_COUNT 100

int ck_assert_str_equal(char* verifiable, char* original_str);

const char specs[SPECS_COUNT][3] = {
    [0] = "%c",  [1] = "%s",  [2] = "%d",  [3] = "%x", [4] = "%X",  [5] = "%o",
    [6] = "%i",  [7] = "%u",  [8] = "%n",  [9] = "%p", [10] = "%f", [11] = "%g",
    [12] = "%G", [13] = "%e", [14] = "%E", [15] = "%%"};

const char flags[FLAGS_COUNT] = {'0', '-', ' ', '#', '+'};
const char length[LENGTH_COUNT] = {'h', 'l', 'L'};

const char* flags_combination[FLAGS_COMBINATION];

const int width_and_accuracy_values[ACCURACY_AND_WIDTH_COUNT];

#define ldouble long double
#define ulong unsigned long
#define ullong unsigned long long
#define llong long long
#define char_ptr char*
#define ushort unsigned short

#define MAX 100

int generate_combination(char** source_string, char** combination_string,
                         unsigned long int* comb_mask,
                         unsigned long int* max_mask_length);
int factorial(int n) { return (n < 2) ? 1 : n * factorial(n - 1); }

int CalculateOfFlagCombination(int flags_count) {
  int res = 0;
  for (int i = 1; i <= flags_count; ++i) {
    res += factorial(flags_count) / (factorial(i) * factorial(flags_count - i));
  }
  return res;
}

char** GetArrayOfFlagCombination(char** flags, int flags_count,
                                 int* flags_combination_count) {
  char* combination_string = malloc(MAX);
  (*flags_combination_count) = CalculateOfFlagCombination(flags_count);
  char** res = malloc((*flags_combination_count));

  unsigned long int comb_mask = 0x0000000000000001;
  unsigned long int max_mask_length = ~(0x0000000000000001 << flags_count);
  int count = 0;

  while (1) {
    if (!generate_combination(flags, &combination_string, &comb_mask,
                              &max_mask_length))
      break;

    int comb_len = s21_strlen(combination_string);
    res[count] = malloc(comb_len + 1);
    s21_strcpy(res[count], combination_string);
    res[count][comb_len] = '\0';
    count++;
  }
  return res;
}

int generate_combination(char** source_string, char** combination_string,
                         unsigned long int* comb_mask,
                         unsigned long int* max_mask_length) {
  unsigned int mask = 0x0000000000000001;
  int s_pos = 0, c_pos = 0;

  while ((mask & (*max_mask_length))) {
    if (((*comb_mask) & mask)) {
      (*combination_string) =
          s21_insert((*combination_string), source_string[s_pos], c_pos);
      if (s_pos == 6) c_pos++;  // Handle .* case
      c_pos++;
    }
    s_pos++;
    mask <<= 1;
  }

  (*comb_mask)++;

  (*combination_string)[c_pos] = 0;

  return (c_pos == 0 ? 0 : 1);
}

void printf_flags_combination(char** flags_combination,
                              int flags_combination_count) {
  for (int i = 0; i < flags_combination_count; ++i) {
    printf("%s\n", flags_combination[i]);
  }
}

#define generate_input_array(type)                                        \
  type* generate_input_array_of_##type(int size, type step, type start) { \
    type* array = malloc(size * sizeof(type));                            \
    int i = 0;                                                            \
    for (type value = start; i < size; i++, value += step) {              \
      array[i] = value;                                                   \
    }                                                                     \
                                                                          \
    return array;                                                         \
  }

#define generate_tests(spec, type)                                            \
  void star_width_and_star_accuracy_##spec##_##type(type value) {             \
    char s21_str[BUFF_SIZE];                                                  \
    char orig_str[BUFF_SIZE];                                                 \
    char msg_buffer[BUFF_SIZE];                                               \
    int flags_count = 7;                                                      \
    char* s_string[MAX] = {"0", "-", " ", "#", "+", "*", ".*"};               \
    int flags_combination_count = 0;                                          \
    char** flags_combination = GetArrayOfFlagCombination(                     \
        s_string, flags_count, &flags_combination_count);                     \
    int s21_res, orig_res;                                                    \
                                                                              \
    int spec_len = s21_strlen(#spec);                                         \
    char* format = malloc(1 + spec_len + 1);                                  \
    s21_strcpy(format, "%");                                                  \
    format[1] = '\0';                                                         \
    format = s21_strcat(format, #spec);                                       \
    format[1 + spec_len] = '\0';                                              \
    char* base_format = malloc(1 + spec_len + 1);                             \
    s21_strcpy(base_format, format);                                          \
    base_format[1 + spec_len] = '\0';                                         \
                                                                              \
    int width = 0, accuracy = 0;                                              \
                                                                              \
    for (int flag_idx = 19; flag_idx < flags_combination_count; flag_idx++) { \
      format = s21_strcat(format, flags_combination[flag_idx]);               \
      for (int accuracy_idx = 0; accuracy_idx < ACCURACY_AND_WIDTH_COUNT;     \
           accuracy_idx++) {                                                  \
        for (int width_idx = 0; width_idx < ACCURACY_AND_WIDTH_COUNT;         \
             width_idx++) {                                                   \
          accuracy = -50 + accuracy_idx;                                      \
          width = -50 + width_idx;                                            \
          s21_res = s21_sprintf(s21_str, format, accuracy, value, width);     \
          orig_res = sprintf(orig_str, format, accuracy, value, width);       \
                                                                              \
          ck_assert_str_equal(s21_str, orig_str);                             \
        }                                                                     \
        free(format);                                                         \
        format = malloc(1 + spec_len + 1);                                    \
        format = s21_strcpy(format, base_format);                             \
        format[s21_strlen(format) + 1] = '\0';                                \
      }                                                                       \
    }                                                                         \
  }                                                                           \
                                                                              \
  void str_width_and_star_accuracy_##spec##_##type(type value) {              \
    char s21_str[BUFF_SIZE];                                                  \
    char orig_str[BUFF_SIZE];                                                 \
    char msg_buffer[BUFF_SIZE];                                               \
    int s21_res, orig_res;                                                    \
    int flags_count = 6;                                                      \
    char* s_string[MAX] = {"0", "-", " ", "#", "+", ".*"};                    \
    int flags_combination_count = 0;                                          \
    char** flags_combination = GetArrayOfFlagCombination(                     \
        s_string, flags_count, &flags_combination_count);                     \
                                                                              \
    int spec_len = s21_strlen(#spec);                                         \
    char* format = malloc(1 + spec_len + 1);                                  \
    s21_strcpy(format, "%");                                                  \
    format[1] = '\0';                                                         \
    format = s21_strcat(format, #spec);                                       \
    format[1 + spec_len] = '\0';                                              \
    char* base_format = malloc(1 + spec_len + 1);                             \
    s21_strcpy(base_format, format);                                          \
    base_format[1 + spec_len] = '\0';                                         \
                                                                              \
    int width = 0, accuracy = 0;                                              \
                                                                              \
    for (int flag_idx = 19; flag_idx < flags_count; flag_idx++) {             \
      for (int width_idx = 0; width_idx < ACCURACY_AND_WIDTH_COUNT;           \
           width_idx++) {                                                     \
        width = width_idx;                                                    \
        char* width_str = WholePartToString(width, 10);                       \
        char* tmp = s21_insert(format, width_str, 1);                         \
        free(format);                                                         \
        format = s21_insert(tmp, flags_combination[flag_idx], 1);             \
        free(tmp);                                                            \
                                                                              \
        for (int accuracy_idx = 0; accuracy_idx < ACCURACY_AND_WIDTH_COUNT;   \
             accuracy_idx++) {                                                \
          accuracy = -50 + accuracy_idx;                                      \
          s21_res = s21_sprintf(s21_str, format, accuracy, value);            \
          orig_res = sprintf(orig_str, format, accuracy, value);              \
                                                                              \
          ck_assert_str_equal(s21_str, orig_str);                             \
        }                                                                     \
        free(format);                                                         \
        format = malloc(1 + spec_len + 1);                                    \
        format = s21_strcpy(format, base_format);                             \
        format[s21_strlen(format) + 1] = '\0';                                \
      }                                                                       \
    }                                                                         \
  }                                                                           \
                                                                              \
  void star_width_and_str_accuracy_##spec##_##type(type value) {              \
    char s21_str[BUFF_SIZE];                                                  \
    char orig_str[BUFF_SIZE];                                                 \
    char msg_buffer[BUFF_SIZE];                                               \
    int s21_res, orig_res;                                                    \
    int flags_count = 6;                                                      \
    char* s_string[MAX] = {"0", "-", " ", "#", "+", "*"};                     \
    int flags_combination_count = 0;                                          \
    char** flags_combination = GetArrayOfFlagCombination(                     \
        s_string, flags_count, &flags_combination_count);                     \
                                                                              \
    int spec_len = s21_strlen(#spec);                                         \
    char* format = malloc(1 + spec_len + 1);                                  \
    s21_strcpy(format, "%");                                                  \
    format[1] = '\0';                                                         \
    format = s21_strcat(format, #spec);                                       \
    format[1 + spec_len] = '\0';                                              \
    char* base_format = malloc(1 + spec_len + 1);                             \
    s21_strcpy(base_format, format);                                          \
    base_format[1 + spec_len] = '\0';                                         \
    int width = 0, accuracy = 0;                                              \
                                                                              \
    for (int flag_idx = 19; flag_idx < flags_count; flag_idx++) {             \
      printf("|format      |%s|\n", format);                                  \
                                                                              \
      for (int accuracy_idx = 0; accuracy_idx < ACCURACY_AND_WIDTH_COUNT;     \
           accuracy_idx++) {                                                  \
        accuracy = -50 + accuracy_idx;                                        \
        char* accuracy_str = WholePartToString(accuracy, 10);                 \
        char* tmp = s21_insert(format, accuracy_str, 1);                      \
        free(format);                                                         \
        format = s21_insert(tmp, ".", 1);                                     \
        free(tmp);                                                            \
        tmp = s21_insert(format, flags_combination[flag_idx], 1);             \
        free(format);                                                         \
        format = tmp;                                                         \
                                                                              \
        for (int width_idx = 0; width_idx < ACCURACY_AND_WIDTH_COUNT;         \
             width_idx++) {                                                   \
          width = -50 + width_idx;                                            \
          s21_res = s21_sprintf(s21_str, format, width, value);               \
          orig_res = sprintf(orig_str, format, width, value);                 \
                                                                              \
          ck_assert_str_equal(s21_str, orig_str);                             \
        }                                                                     \
        free(format);                                                         \
        format = malloc(1 + spec_len + 1);                                    \
        format = s21_strcpy(format, base_format);                             \
        format[s21_strlen(format) + 1] = '\0';                                \
      }                                                                       \
    }                                                                         \
  }

generate_tests(d, int) generate_input_array(int)

    generate_tests(ld, long) generate_input_array(long)

        generate_tests(lld, llong) generate_input_array(llong)

            generate_tests(lu, ulong) generate_input_array(ulong)

                generate_tests(llu, ullong) generate_input_array(ullong)

    // *.*
    // n.*
    // *.n
    // сочетнаия всех флагов в нормальном виде
    // сочетнаия всех флагов в рандомном порядке
    // str < format
    // str = NULL
    // format = NULL
    // double/int в ширине и точности
    // спецификатор без аргумента

    // int для f и тп
    // прогон для f и g по интересующим диапазонам
    int main(void) {
  int* int_data = generate_input_array_of_int(500, 5, INT_MIN);
  for (int i = 0; i < 500; i++) {
    star_width_and_star_accuracy_d_int(int_data[i]);
    str_width_and_star_accuracy_d_int(int_data[i]);
    //        star_width_and_str_accuracy_d_int(i);
  }
  //  str_width_and_star_accuracy_d_int(0);
  //  star_width_and_str_accuracy_d_int(0);
  return 0;
}

int ck_assert_str_equal(char* verifiable, char* original_str) {
  int res = 0;
  if (strcmp(verifiable, original_str) != 0) {
    printf("\033[31m\033 |FAIL!\033[0m\n");
    printf("|s21_str     |%s| |%ld|\n", verifiable, s21_strlen(verifiable));
    printf("|orig_str    |%s| |%ld|\n\n", original_str,
           s21_strlen(original_str));
    res = 1;
  }
  //   else{
  //     printf("SUCCESS!\n");
  //     printf("verifiable = %s\n", verifiable);
  //     printf("original   = %s\n", original_str);
  //   }
  // free(verifiable);
  // verifiable = NULL;
  return res;
}