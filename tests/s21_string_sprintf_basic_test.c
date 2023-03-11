#include "s21_string_test.h"

void generate_s21_sprintf_format_string(char **format_string, int spec_index,
                                        int flags_enabled, int i) {
  s21_strcat(*format_string, "TEST:(");
  if (flags_enabled) {
    int current_position = s21_strlen(*format_string);
    *format_string[current_position++] = specs[spec_index][0];
    if (numbers[i] % 4 == 0) {
      *format_string[current_position++] = flags[numbers[i] % FLAGS_COUNT];
    }
    if (numbers[i] % 2 == 0) {
      *format_string[current_position++] = '0' + numbers[i] % 10;
    }
    if (numbers[i] % 3 == 0) {
      *format_string[current_position++] = '.';
      *format_string[current_position++] = '0' + numbers[i] * 13 % 10;
    }
    if (numbers[i] % 5 == 0) {
      *format_string[current_position++] = length[numbers[i] % FLAGS_COUNT];
    }
    *format_string[current_position++] = specs[spec_index][1];
    *format_string[current_position] = specs[spec_index][2];
    s21_strcat(*format_string, ") with flags");
  } else {
    s21_strcat(*format_string, specs[spec_index]);
    s21_strcat(*format_string, ") no flags");
  }
}

START_TEST(test_name) {
  // Объявляем нулевую строку для записи и формата
  // Выбираем некоторое значение для записи
  // Генерируем строку формата
  // Записываем шляпу
  // Сравниваем результат
}
END_TEST

START_TEST(s21_sprintf_c_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  char symbol = numbers[_i];

  char *converter = format_string;
  generate_s21_sprintf_format_string(&converter, 0, 0, _i);

  expected_return_value = sprintf(expected_string, format_string, symbol);
  result_return_value = s21_sprintf(result_string, format_string, symbol);

  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

START_TEST(s21_sprintf_s_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  char *converter = format_string;
  generate_s21_sprintf_format_string(&converter, 1, 0, _i);

  expected_return_value = sprintf(expected_string, format_string, strings[_i]);
  result_return_value = s21_sprintf(result_string, format_string, strings[_i]);

  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

START_TEST(s21_sprintf_d_i_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  int number = numbers[_i];

  char *converter = format_string;
  generate_s21_sprintf_format_string(&converter, number % 2 == 0 ? 2 : 6, 0,
                                     _i);

  expected_return_value = sprintf(expected_string, format_string, number);
  result_return_value = s21_sprintf(result_string, format_string, number);

  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

START_TEST(s21_sprintf_o_x_X_u_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  unsigned int number = numbers[_i];

  char *converter = format_string;
  generate_s21_sprintf_format_string(
      &converter, number % 4 == 3 ? 7 : number % 4 + 3, 0, _i);

  expected_return_value = sprintf(expected_string, format_string, number);
  result_return_value = s21_sprintf(result_string, format_string, number);

  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

START_TEST(s21_sprintf_f_e_E_g_G_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  double number = floating_point_numbers[_i];

  char *converter = format_string;
  generate_s21_sprintf_format_string(&converter, (int)number % 5 + 10, 0, _i);

  expected_return_value = sprintf(expected_string, format_string, number);
  result_return_value = s21_sprintf(result_string, format_string, number);

  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

START_TEST(s21_sprintf_n_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  int expected_n_value = 0;
  int result_n_value = 0;

  char *converter = "%n";

  expected_return_value =
      sprintf(expected_string, converter, &expected_n_value);
  result_return_value = s21_sprintf(result_string, converter, &result_n_value);

  ck_assert_int_eq(expected_n_value, result_n_value);
  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

START_TEST(s21_sprintf_p_no_flags) {
  int expected_return_value, result_return_value;
  char expected_string[STRING_SIZE * 2] = {'\0'};
  char result_string[STRING_SIZE * 2] = {'\0'};
  char format_string[STRING_SIZE] = {'\0'};

  void *pointer = &numbers[_i];

  char *converter = format_string;
  generate_s21_sprintf_format_string(&converter, 9, 0, _i);

  expected_return_value = sprintf(expected_string, format_string, pointer);
  result_return_value = s21_sprintf(result_string, format_string, pointer);

  ck_assert_str_eq(expected_string, result_string);
  ck_assert_int_eq(expected_return_value, result_return_value);
}
END_TEST

Suite *make_sprintf_basic_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_string_sscanf");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  // tcase_add_loop_test(tc, test_name, 0, TEST_CASES)
  tcase_add_loop_test(tc, s21_sprintf_c_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sprintf_s_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sprintf_d_i_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sprintf_o_x_X_u_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sprintf_f_e_E_g_G_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sprintf_n_no_flags, 0, TEST_CASES);
  tcase_add_loop_test(tc, s21_sprintf_p_no_flags, 0, TEST_CASES);

  return s;
}
