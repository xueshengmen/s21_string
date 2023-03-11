#ifndef SRC_TEST_S21_STRING_TEST_H_
#define SRC_TEST_S21_STRING_TEST_H_

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_string.h"

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILED
#define EXIT_FAILED 1
#endif

#define TEST_CASES 100
#define STRING_SIZE 100
#define ALPHABET_START 32
#define ALPHABET_SIZE 95  // Number of characters from 'space' to 'tilda'
#define SPECS_COUNT 16
#define FLAGS_COUNT 5
#define LENGTH_COUNT 3

/**************************************
 *        Function definitions        *
 *************************************/

SRunner *default_srunner_create(void);

void generate_input_data(void);
void generate_string(int i);
char generate_symbol(void);
void clean_input_data(void);

Suite *make_string_basic_suite(void);
Suite *make_string_extended_suite(void);
Suite *make_sprintf_basic_suite(void);
Suite *make_sprintf_externed_suite(void);
Suite *make_sscanf_suite(void);

int str_cmp(const char *, const char *);

void generate_s21_sprintf_format_string(char **format_string, int spec_index,
                                        int flags_enabled, int i);

typedef enum additional_arg_mode {
  NO_STAR,
  STAR_WIDTH,
  STAR_ACCURACY,
  STAR_ACCURACY_AND_WIDTH
} additional_arg_mode;

#endif  // SRC_TEST_S21_STRING_TEST_H_

/**************************************
 *             Test cases             *
 *************************************/

extern char *strings[TEST_CASES];
extern char symbols[TEST_CASES];
extern int numbers[TEST_CASES];
extern double floating_point_numbers[TEST_CASES];

extern const char specs[SPECS_COUNT][3];
extern const char flags[FLAGS_COUNT];
extern const char length[LENGTH_COUNT];