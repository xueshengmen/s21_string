#include "s21_string_test.h"

START_TEST(test_s21_to_upper) {
  char *result = s21_to_upper(strings[_i]);

  if (result != NULL) {
    int status = 1;
    for (int i = 0; i < strlen(result) && status; i++) {
      if (result[i] >= 'a' && result[i] <= 'z') {
        status = 0;
      }
    }

    ck_assert_int_eq(status, 1);
    free(result);
  } else {
    ck_assert_ptr_eq(result, NULL);
  }
}
END_TEST

START_TEST(test_s21_to_lower) {
  char *result = s21_to_lower(strings[_i]);

  if (result != NULL) {
    int status = 1;
    for (int i = 0; i < strlen(result) && status; i++) {
      if (result[i] >= 'A' && result[i] <= 'Z') {
        status = 0;
      }
    }

    ck_assert_int_eq(status, 1);
    free(result);
  } else {
    ck_assert_ptr_eq(result, NULL);
  }
}
END_TEST

START_TEST(test_s21_insert) {
  char *result = NULL;
  char expected[STRING_SIZE * 2] = "";
  char buffer[STRING_SIZE * 2] = "";
  char str[STRING_SIZE] = "";

  s21_strcpy(expected, strings[_i + 1]);
  s21_strncpy(str, strings[_i], numbers[_i]);

  result = s21_insert(strings[_i + 1], str, numbers[_i] % 10);

  s21_strcpy(buffer, expected + numbers[_i] % 10);
  expected[numbers[_i] % 10] = '\0';
  s21_strcat(expected, str);
  s21_strcat(expected, buffer);

  if (result != NULL) {
    ck_assert_str_eq(result, expected);
    free(result);
  } else {
    ck_assert_ptr_eq(result, NULL);
  }
}
END_TEST

START_TEST(test_s21_trim) {
  char *result = NULL;
  char expected[STRING_SIZE] = "";
  char buff[STRING_SIZE] = "";
  char trim_chars[STRING_SIZE] = "";

  s21_strcpy(expected, strings[_i]);
  s21_strncpy(trim_chars, strings[_i], 2);

  result = s21_trim(strings[_i], trim_chars);

  for (int i = 1; expected[STRING_SIZE - i] == trim_chars[0] ||
                  expected[STRING_SIZE - i] == trim_chars[1];
       i++) {
    expected[STRING_SIZE - i] = '\0';
  }

  s21_strcpy(buff, expected);

  int status = 1;
  for (int i = 0; buff[i] != '\0' && status; i++) {
    if (expected[i] == trim_chars[0] || expected[i] == trim_chars[1]) {
      continue;
    } else {
      status = 0;
      int j = 0;
      for (; buff[i] != '\0'; j++) {
        expected[j] = buff[i++];
      }
      expected[j] = '\0';
    }
  }

  if (result != NULL) {
    ck_assert_str_eq(result, expected);
    free(result);
  } else {
    ck_assert_ptr_eq(result, NULL);
  }
}

Suite *make_string_extended_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_string_extended");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_loop_test(tc, test_s21_to_upper, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_to_lower, 0, TEST_CASES);
  tcase_add_loop_test(tc, test_s21_insert, 0, TEST_CASES - 1);
  tcase_add_loop_test(tc, test_s21_trim, 0, TEST_CASES);

  return s;
}
