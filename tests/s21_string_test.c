#include "s21_string_test.h"

SRunner *default_srunner_create(void) {
  SRunner *sr;

  sr = srunner_create(make_string_basic_suite());
  srunner_add_suite(sr, make_string_extended_suite());
  srunner_add_suite(sr, make_sprintf_basic_suite());
  srunner_add_suite(sr, make_sscanf_suite());

  return sr;
}

int str_cmp(const char *str1, const char *str2) {
  while ((*str1 == *str2) && (*str1 != '\0')) {
    str1++;
    str2++;
  };

  return (*str1 == *str2) ? 1 : 0;
}

void generate_input_data(void) {
  for (int i = 0; i < TEST_CASES; i++) {
    strings[i] = (char *)malloc(sizeof(char) * STRING_SIZE);
    generate_string(i);

    symbols[i] = generate_symbol();
    numbers[i] = rand() % STRING_SIZE;
    floating_point_numbers[i] = (double)rand() / (double)rand();
  }
}

void generate_string(int i) {
  for (int j = 0; j < STRING_SIZE - 1; j++) {
    strings[i][j] = generate_symbol();
  }
  strings[i][STRING_SIZE - 1] = '\0';
}

char generate_symbol(void) { return ALPHABET_START + (rand() % ALPHABET_SIZE); }

void clean_input_data(void) {
  for (int i = 0; i < TEST_CASES; i++) {
    free(strings[i]);
  }
}

/**************************************
 *             Test cases             *
 *************************************/

char *strings[TEST_CASES];
char symbols[TEST_CASES];
int numbers[TEST_CASES];
double floating_point_numbers[TEST_CASES];

const char specs[SPECS_COUNT][3] = {
    [0] = "%c",  [1] = "%s",  [2] = "%d",  [3] = "%x", [4] = "%X",  [5] = "%o",
    [6] = "%i",  [7] = "%u",  [8] = "%n",  [9] = "%p", [10] = "%f", [11] = "%g",
    [12] = "%G", [13] = "%e", [14] = "%E", [15] = "%%"};

const char flags[FLAGS_COUNT] = {'0', '-', ' ', '#', '+'};
const char length[LENGTH_COUNT] = {'h', 'l', 'L'};