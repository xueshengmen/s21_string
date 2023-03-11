#include "s21_string_test.h"

int main(int argc, char *argv[]) {
  int exit_status = EXIT_FAILED;
  int number_failed = 0;
  SRunner *sr = NULL;

  generate_input_data();

  if (argc <= 2) {
    if (argc == 1) {
      sr = default_srunner_create();
    } else {
      if (str_cmp(argv[1], "string")) {
        sr = srunner_create(make_string_basic_suite());
        srunner_add_suite(sr, make_string_extended_suite());
      } else if (str_cmp(argv[1], "sprintf")) {
        sr = srunner_create(make_sprintf_basic_suite());
      } else if (str_cmp(argv[1], "sscanf")) {
        sr = srunner_create(make_sscanf_suite());
      }
    }

    srunner_set_log(sr, "test.log");
    srunner_run_all(sr, CK_SILENT);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    clean_input_data();

    if (number_failed == 0) {
      exit_status = EXIT_SUCCESS;
    }
  }

  return exit_status;
}