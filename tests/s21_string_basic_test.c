#include "s21_string_test.h"

START_TEST(test_s21_memchr) {
  int n = numbers[_i];
  char c = symbols[_i];

  void *expected = memchr(strings[_i], c, n);
  void *result = s21_memchr(strings[_i], c, n);

  ck_assert_ptr_eq(expected, result);
}
END_TEST

START_TEST(test_s21_memcmp) {
  int n = numbers[_i];

  int expected = memcmp(strings[_i], strings[_i + 1], n);
  int result = s21_memcmp(strings[_i], strings[_i + 1], n);

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(test_s21_memcpy) {
  int n = numbers[_i];

  char expected[STRING_SIZE];
  char result[STRING_SIZE];

  memcpy(expected, strings[_i], n);
  s21_memcpy(result, strings[_i], n);

  ck_assert_mem_eq(expected, result, n);
}
END_TEST

START_TEST(test_s21_memmove) {
  int n = numbers[_i];

  char expected[STRING_SIZE];
  char result[STRING_SIZE];

  memcpy(expected, strings[_i], n);
  s21_memcpy(result, strings[_i], n);

  ck_assert_mem_eq(expected, result, n);
}
END_TEST

START_TEST(test_s21_memset) {
  int n = numbers[_i];
  char c = symbols[_i];

  char expected[STRING_SIZE];
  char result[STRING_SIZE];

  s21_memcpy(expected, strings[_i], STRING_SIZE);
  s21_memcpy(result, strings[_i], STRING_SIZE);

  memset(expected, c, n);
  s21_memset(result, c, n);

  ck_assert_str_eq(expected, result);
}

START_TEST(test_s21_strcat) {
  int n = numbers[_i];

  char expected[STRING_SIZE * 2];
  char result[STRING_SIZE * 2];

  s21_memcpy(expected, strings[_i], n);
  s21_memcpy(result, strings[_i], n);

  expected[n] = '\0';
  result[n] = '\0';

  strcat(expected, strings[_i + 1]);
  s21_strcat(result, strings[_i + 1]);

  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strncat) {
  int n = numbers[_i];

  char expected[STRING_SIZE * 2];
  char result[STRING_SIZE * 2];

  s21_memcpy(expected, strings[_i], n);
  s21_memcpy(result, strings[_i], n);

  expected[n] = '\0';
  result[n] = '\0';

  strncat(expected, strings[_i + 1], n);
  s21_strncat(result, strings[_i + 1], n);

  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strchr) {
  ck_assert_pstr_eq(strchr(strings[_i], symbols[_i]),
                    s21_strchr(strings[_i], symbols[_i]));
}
END_TEST

START_TEST(test_s21_strcmp) {
  ck_assert_int_eq(strcmp(strings[_i], strings[_i]),
                   s21_strcmp(strings[_i], strings[_i]));

  ck_assert_int_eq(strcmp(strings[_i], strings[_i + 1]),
                   s21_strcmp(strings[_i], strings[_i + 1]));
}
END_TEST

START_TEST(test_s21_strncmp) {
  ck_assert_int_eq(strncmp(strings[_i], strings[_i], numbers[_i]),
                   s21_strncmp(strings[_i], strings[_i], numbers[_i]));

  ck_assert_int_eq(strncmp(strings[_i], strings[_i + 1], numbers[_i]),
                   s21_strncmp(strings[_i], strings[_i + 1], numbers[_i]));
}
END_TEST

START_TEST(test_s21_strcpy) {
  char expected[STRING_SIZE] = "";
  char result[STRING_SIZE] = "";

  strcpy(expected, strings[_i]);
  s21_strcpy(result, strings[_i]);

  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strncpy) {
  char expected[STRING_SIZE] = "";
  char result[STRING_SIZE] = "";

  strncpy(expected, strings[_i], numbers[_i]);
  s21_strncpy(result, strings[_i], numbers[_i]);

  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strcspn) {
  ck_assert_int_eq(strcspn(strings[_i], strings[_i + 1]),
                   s21_strcspn(strings[_i], strings[_i + 1]));
}
END_TEST

START_TEST(test_s21_strerror) {
  char *expected = strerror(numbers[_i]);
  char *result = s21_strerror(numbers[_i]);

  ck_assert_str_eq(expected, result);
}
END_TEST

START_TEST(test_s21_strlen) {
  char expected[STRING_SIZE] = "";
  char result[STRING_SIZE] = "";

  strncpy(expected, strings[_i], numbers[_i]);
  s21_strncpy(result, strings[_i], numbers[_i]);

  ck_assert_int_eq(strlen(expected), s21_strlen(result));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  ck_assert_pstr_eq(strpbrk(strings[_i], strings[_i + 1]),
                    s21_strpbrk(strings[_i], strings[_i + 1]));
}
END_TEST

START_TEST(test_s21_strrchr) {
  ck_assert_pstr_eq(strchr(strings[_i], symbols[_i]),
                    s21_strchr(strings[_i], symbols[_i]));
}
END_TEST

START_TEST(test_s21_strspn) {
  char charset[STRING_SIZE] = "";
  s21_strncpy(charset, strings[_i], numbers[_i]);

  ck_assert_int_eq(strspn(strings[_i], charset),
                   s21_strspn(strings[_i], charset));
}
END_TEST

START_TEST(test_s21_strstr) {
  char needle[STRING_SIZE] = "";
  s21_strncpy(needle, strings[_i], numbers[_i]);

  ck_assert_pstr_eq(strstr(strings[_i], needle),
                    s21_strstr(strings[_i], needle));
}
END_TEST

START_TEST(test_s21_strtok) {
  char original_string_1[STRING_SIZE] = "";
  char original_string_2[STRING_SIZE] = "";
  char delims[STRING_SIZE] = "";

  s21_strncpy(delims, strings[_i + 1], 2);
  s21_strcpy(original_string_1, strings[_i]);
  s21_strcpy(original_string_2, strings[_i]);

  char *expected = strtok(original_string_1, delims);
  char *result = s21_strtok(original_string_2, delims);

  ck_assert_int_eq(s21_strlen(expected), s21_strlen(result));
  ck_assert_str_eq(expected, result);

  while (expected && result) {
    expected = strtok(NULL, delims);
    result = s21_strtok(NULL, delims);

    ck_assert_int_eq(s21_strlen(expected), s21_strlen(result));

    if (expected || result) {
      ck_assert_str_eq(expected, result);
    } else {
      ck_assert_ptr_null(expected);
      ck_assert_ptr_null(result);
    }
  }
}
END_TEST

Suite *make_string_basic_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_string_basic");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_loop_test(tc, test_s21_memchr, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_memcmp, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_memcpy, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_memmove, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_memset, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strcat, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_strncat, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_strchr, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strcmp, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_strncmp, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_strcpy, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strncpy, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strcspn, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_strerror, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strlen, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strpbrk, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_strchr, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strspn, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strstr, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_strtok, 0, TEST_CASES - 1);

  return s;
}
