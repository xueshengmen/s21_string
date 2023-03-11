#include "s21_string_test.h"

START_TEST(s21_sscanf_c_no_flags) {
  int expected_return_value, result_return_value;
  int expected_symbol = 0, result_symbol = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  s21_strcat(format_string, specs[0]);

  expected_return_value = sscanf(strings[_i], format_string, &expected_symbol);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_symbol);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_int_eq(expected_symbol, result_symbol);
}
END_TEST

START_TEST(s21_sscanf_s_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE] = {'\0'};
  char result_string[STRING_SIZE] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  s21_strcat(format_string, specs[1]);

  expected_return_value = sscanf(strings[_i], format_string, expected_string);
  result_return_value = s21_sscanf(strings[_i], format_string, result_string);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_str_eq(expected_string, result_string);
}
END_TEST

START_TEST(s21_sscanf_d_x_X_o_i_u_n_no_flags) {
  int expected_return_value, result_return_value;
  int expected_number = 0, result_number = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  s21_strcat(format_string, specs[numbers[_i] % 7 + 2]);

  expected_return_value = sscanf(strings[_i], format_string, &expected_number);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_number);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_int_eq(expected_number, result_number);
}
END_TEST

START_TEST(s21_sscanf_f_e_E_g_G_no_flags) {
  int expected_return_value, result_return_value;
  float expected_number = 0, result_number = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  s21_strcat(format_string, specs[numbers[_i] % 5 + 10]);

  expected_return_value = sscanf(strings[_i], format_string, &expected_number);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_number);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_int_eq(expected_number, result_number);
}
END_TEST

START_TEST(s21_sscanf_p_no_flags) {
  int expected_return_value, result_return_value;
  void *expected_pointer = 0, *result_pointer = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  s21_strcat(format_string, specs[numbers[_i] % 5 + 10]);

  expected_return_value = sscanf(strings[_i], format_string, &expected_pointer);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_pointer);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_ptr_eq(expected_pointer, result_pointer);
}
END_TEST

START_TEST(s21_sscanf_c_with_flags) {
  int expected_return_value, result_return_value;
  char expected_symbol = 0, result_symbol = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  int current_position = s21_strlen(format_string);
  format_string[current_position++] = specs[0][0];
  if (numbers[_i] % 2 == 0) {
    format_string[current_position++] = '0' + numbers[_i] % 10;
  } else {
    format_string[current_position++] = '*';
  }
  format_string[current_position++] = specs[0][1];
  format_string[current_position] = specs[0][2];

  expected_return_value = sscanf(strings[_i], format_string, &expected_symbol);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_symbol);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_int_eq(expected_symbol, result_symbol);
}
END_TEST

START_TEST(s21_sscanf_s_with_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE] = {'\0'};
  char result_string[STRING_SIZE] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  int current_position = s21_strlen(format_string);
  format_string[current_position++] = specs[1][0];
  if (numbers[_i] % 2 == 0) {
    format_string[current_position++] = '0' + numbers[_i] % 10;
  } else {
    format_string[current_position++] = '*';
  }
  format_string[current_position++] = specs[1][1];
  format_string[current_position] = specs[1][2];

  expected_return_value = sscanf(strings[_i], format_string, expected_string);
  result_return_value = s21_sscanf(strings[_i], format_string, result_string);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_str_eq(expected_string, result_string);
}
END_TEST

START_TEST(s21_sscanf_d_x_X_o_i_u_n_with_flags) {
  int expected_return_value, result_return_value;
  long long expected_number = 0, result_number = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  int current_position = s21_strlen(format_string);
  format_string[current_position++] = specs[numbers[_i] % 7 + 2][0];
  if (numbers[_i] % 2 == 0) {
    format_string[current_position++] = '0' + numbers[_i] % 10;
  } else {
    format_string[current_position++] = '*';
  }
  format_string[current_position++] = length[numbers[_i] % LENGTH_COUNT];
  format_string[current_position++] = specs[numbers[_i] % 7 + 2][1];
  format_string[current_position] = specs[numbers[_i] % 7 + 2][2];

  expected_return_value = sscanf(strings[_i], format_string, &expected_number);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_number);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_int_eq(expected_number, result_number);
}
END_TEST

START_TEST(s21_sscanf_f_e_E_g_G_with_flags) {
  int expected_return_value, result_return_value;
  long double expected_number = 0, result_number = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  int current_position = s21_strlen(format_string);
  format_string[current_position++] = specs[numbers[_i] % 5 + 10][0];
  if (numbers[_i] % 2 == 0) {
    format_string[current_position++] = '0' + numbers[_i] % 10;
  } else {
    format_string[current_position++] = '*';
  }
  format_string[current_position++] = length[numbers[_i] % LENGTH_COUNT];
  format_string[current_position++] = specs[numbers[_i] % 5 + 10][1];
  format_string[current_position] = specs[numbers[_i] % 5 + 10][2];

  expected_return_value = sscanf(strings[_i], format_string, &expected_number);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_number);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_int_eq(expected_number, result_number);
}
END_TEST

START_TEST(s21_sscanf_p_with_flags) {
  int expected_return_value, result_return_value;
  void *expected_pointer = 0, *result_pointer = 0;
  char format_string[STRING_SIZE] = {'\0'};

  s21_strncpy(format_string, strings[_i], numbers[_i]);
  int current_position = s21_strlen(format_string);
  format_string[current_position++] = specs[9][0];
  if (numbers[_i] % 2 == 0) {
    format_string[current_position++] = '0' + numbers[_i] % 10;
  } else {
    format_string[current_position++] = '*';
  }
  format_string[current_position++] = specs[9][1];
  format_string[current_position] = specs[9][2];

  expected_return_value = sscanf(strings[_i], format_string, &expected_pointer);
  result_return_value = s21_sscanf(strings[_i], format_string, &result_pointer);

  ck_assert_int_eq(expected_return_value, result_return_value);
  ck_assert_ptr_eq(expected_pointer, result_pointer);
}
END_TEST

Suite *make_sscanf_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_string_sscanf");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_loop_test(tc, s21_sscanf_c_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_s_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_d_x_X_o_i_u_n_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_f_e_E_g_G_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_p_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_c_with_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_s_with_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_d_x_X_o_i_u_n_with_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_f_e_E_g_G_with_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sscanf_p_with_flags, 0, TEST_CASES);

  return s;
}