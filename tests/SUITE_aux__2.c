#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define BUFF_SIZE 512

int accuracy_or_width[512];
double double_array[512];
long double long_double_array[512];

#define fill_array(type, array)                              \
  void fill_##array(int size, type step, type start) {       \
    int i = 0;                                               \
    for (type value = start; i < size; i++, value += step) { \
      array[i] = value;                                      \
    }                                                        \
  }

fill_array(int, accuracy_or_width);
fill_array(double, double_array);
#define ldouble long double
fill_array(ldouble, long_double_array);

START_TEST(s21_memchr_test) {
  int line = __LINE__;
  char *str = "This is a test";

  ck_assert_ptr_eq(s21_memchr(str, 's', 0), memchr(str, 's', 0));
  ck_assert_ptr_eq(s21_memchr(str, 's', 2), memchr(str, 's', 2));
  ck_assert_ptr_eq(s21_memchr(str, 's', 15), memchr(str, 's', 15));
  ck_assert_ptr_eq(s21_memchr(str, 'u', 15), memchr(str, 'u', 15));
  ck_assert_ptr_eq(s21_memchr(str, ' ', 8), memchr(str, ' ', 8));
}
END_TEST

START_TEST(s21_memcmp_test) {
  int line = __LINE__;
  char test1[] = "This is a test";
  char test2[] = "Ai ento ne to";
  char test3[] = "\0";
  char test4[] = "gud\0 job";
  char test5[] = "gud\0 job";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 14) < 0,
                    memcmp(test1, test2, 14) < 0);
  ck_assert_uint_eq(s21_memcmp(test1, test3, 2) > 0,
                    memcmp(test1, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test2, test3, 2) > 0,
                    memcmp(test2, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test1, 9) > 0,
                    memcmp(test4, test1, 9) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test5, 7) == 0,
                    memcmp(test4, test5, 7) == 0);
}
END_TEST

START_TEST(s21_memcpy_test) {
  int line = __LINE__;
  char *str = "Iweg hes rdrgwt/ 0sfdsfd45 22451 sfesr";
  int len = s21_strlen(str);
  char dest1[100] = {0};
  char dest2[100] = {0};
  char dest3[100] = {0};
  char dest4[100] = {0};
  char dest5[100] = {0};
  char dest6[100] = {0};
  char dest7[100] = {0};
  char dest8[100] = {0};
  char dest9[100] = {0};
  char dest10[100] = {0};

  s21_memcpy(dest1, str, len + 1);
  memcpy(dest2, str, len + 1);

  s21_memcpy(dest3, str, 5);
  memcpy(dest4, str, 5);

  s21_memcpy(dest5, str, 0);
  memcpy(dest6, str, 0);

  s21_memcpy(dest7, str, 18);
  memcpy(dest8, str, 18);

  s21_memcpy(dest9, str, 1);
  memcpy(dest10, str, 1);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_str_eq(dest3, dest4);
  ck_assert_str_eq(dest5, dest6);
  ck_assert_str_eq(dest7, dest8);
  ck_assert_str_eq(dest9, dest10);
}
END_TEST

START_TEST(s21_memmove_test) {
  int line = __LINE__;
  char *src1 = "Iweg hes rdrgwt/ 0sfdsfd45 22451 sfesr";
  int len = s21_strlen(src1);
  char dest1[100];
  char dest2[100];
  char dest3[100];
  char dest4[100];
  char dest5[100];
  char dest6[100];
  char dest7[100];
  char dest8[100];
  char dest9[100];
  char dest10[100];

  s21_memmove(dest1, src1, len + 1);
  memmove(dest2, src1, len + 1);

  s21_memmove(dest3, src1, 5);
  memmove(dest4, src1, 5);

  s21_memmove(dest5, src1, 0);
  memmove(dest6, src1, 0);

  s21_memmove(dest7, src1, 18);
  memmove(dest8, src1, 18);

  s21_memmove(dest9, src1, 1);
  memmove(dest10, src1, 1);

  ck_assert_msg(memcmp(dest1, dest2, len) == 0, "1 test fail");
  ck_assert_msg(memcmp(dest3, dest4, 5) == 0, "2 test fail");
  ck_assert_msg(memcmp(dest5, dest6, 0) == 0, "3 test fail");
  ck_assert_msg(memcmp(dest7, dest8, 18) == 0, "4 test fail");
  ck_assert_msg(memcmp(dest9, dest10, 1) == 0, "5 test fail");
}
END_TEST

START_TEST(s21_memset_test) {
  int line = __LINE__;
  char str1[] = "Here w0 are123\0";
  char o1[] = "Here w0 are123\0";
  ck_assert_str_eq(s21_memset(str1, '-', 4), memset(o1, '-', 4));

  char str2[] = "Here w0 are\n\0";
  char o2[] = "Here w0 are\n\0";
  ck_assert_str_eq(s21_memset(str2, '-', 4), memset(o2, '-', 4));

  char str3[] = "a\n\0";
  char o3[] = "a\n\0";
  ck_assert_str_eq(s21_memset(str3, '-', 2), memset(o3, '-', 2));

  char str4[] = " \n\0";
  char o4[] = " \n\0";
  ck_assert_str_eq(s21_memset(str4, '-', 2), memset(o4, '-', 2));

  char str5[] = " \0";
  char o5[] = " \0";
  ck_assert_str_eq(s21_memset(str5, '-', 1), memset(o5, '-', 1));

  char str6[] = "\n\0";
  char o6[] = "\n\0";
  ck_assert_str_eq(s21_memset(str6, '-', 1), memset(o6, '-', 1));

  char str7[] = "\0";
  char o7[] = "\0";
  ck_assert_str_eq(s21_memset(str7, '-', 1), memset(o7, '-', 1));
}
END_TEST

START_TEST(s21_strcat_test) {
  int line = __LINE__;
  char str1[20] = "i am";
  char str2[8] = "test";
  char str3[9] = "!!";
  char str4[1] = "\0";
  char str5[2] = " ";

  s21_strcat(str1, str5);
  ck_assert_msg(!memcmp(str1, "i am ", 4), "1 test fail");

  s21_strcat(str1, str2);
  ck_assert_msg(!memcmp(str1, "i am test", 9), "2 test fail");

  s21_strcat(str1, str5);
  ck_assert_msg(!memcmp(str1, "i am test ", 10), "3 test fail");

  s21_strcat(str1, str3);
  ck_assert_msg(!memcmp(str1, "i am test !!", 11), "4 test fail");

  s21_strcat(str1, str4);
  ck_assert_msg(!memcmp(str1, "i am test !!", 11), "5 test fail");
}
END_TEST

START_TEST(s21_strncat_test) {
  int line = __LINE__;
  char str1[21] = "i am";
  char str2[8] = " test";
  char str4[1] = "";

  s21_strncat(str1, str2, 5);
  ck_assert_msg(!memcmp(str1, "i am test", 9), "1 test fail");

  s21_strncat(str1, str4, 1);
  ck_assert_msg(!memcmp(str1, "i am test", 9), "2 test fail");

  s21_strncat(str2, str4, 1);
  ck_assert_msg(!memcmp(str2, " test", 6), "3 test fail");
}
END_TEST

START_TEST(s21_strchr_test) {
  int line = __LINE__;
  char *str1 = "I ";
  char *str2 = "am";
  char *str3 = " the ";
  char *str4 = "";
  char *str5 = "TEST";
  char *str6 = " 1235 4523 13245291 !";
  ck_assert_msg(s21_strchr(str1, 'I') == strchr(str1, 'I'), "1 test fail");
  ck_assert_msg(s21_strchr(str3, ' ') == strchr(str3, ' '), "2 test fail");
  ck_assert_msg(s21_strchr(str5, 'a') == strchr(str5, 'a'), "3 test fail");
  ck_assert_msg(s21_strchr(str2, 'm') == strchr(str2, 'm'), "4 test fail");
  ck_assert_msg(s21_strchr(str3, 'h') == strchr(str3, 'h'), "5 test fail");
  ck_assert_msg(s21_strchr(str4, ' ') == strchr(str4, ' '), "6 test fail");
  ck_assert_msg(s21_strchr(str5, 'e') == strchr(str5, 'e'), "7 test fail");
  ck_assert_msg(s21_strchr(str6, '9') == strchr(str6, '9'), "8 test fail");
}
END_TEST

START_TEST(s21_strcmp_test) {
  int line = __LINE__;
  char *str1 = "12345";
  char *str2 = "12344";
  char *str3 = " ";
  char *str4 = "qwrfv34t    !2-30fk";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
  ck_assert_int_eq(s21_strcmp(str1, str4), strcmp(str1, str4));
  ck_assert_int_eq(s21_strcmp(str2, str3), strcmp(str2, str3));
}
END_TEST

START_TEST(s21_strncmp_test) {
  int line = __LINE__;
  char *str1 = "12345";
  char *str2 = "12344";
  char *str3 = "";
  char *str5 = " ";
  char *str6 = "23rkgi    =20394i!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp(str3, str6, 0), strncmp(str3, str6, 0));
  ck_assert_int_eq(s21_strncmp(str3, str5, 1), strncmp(str3, str5, 1));
}
END_TEST

START_TEST(s21_strcpy_test) {
  int line = __LINE__;
  char s1[50] = "I am the test";
  char d1[50] = "";
  s21_strcpy(d1, s1);
  ck_assert_msg(!strcmp(d1, s1), "1 test fail");

  char s2[50] = "";
  char d2[50] = "I am the test";
  s21_strcpy(d2, s2);
  ck_assert_msg(!strcmp(d2, s2), "2 test fail");

  char s4[50] = "I AM THE TEST";
  char d4[50] = "i am the test";
  s21_strcpy(d4, s4);
  ck_assert_msg(!strcmp(d4, s4), "4 test fail");

  char s5[50] = "";
  char d5[50] = "";
  s21_strcpy(d5, s5);
  ck_assert_msg(!strcmp(d5, s5), "5 test fail");

  char s6[50] = " \n\0";
  char d6[50] = " \n\0";
  s21_strcpy(d6, s6);
  ck_assert_msg(!strcmp(d6, s6), "6 test fail");
}
END_TEST

START_TEST(s21_strncpy_test) {
  int line = __LINE__;
  char s1[50] = "I am the test";
  char d1[50] = "";
  s21_strncpy(d1, s1, 2);
  ck_assert_msg(!strcmp(d1, "I "), "1 test fail");

  char s2[50] = "weg3rg24567rth3reh4";
  char d2[50] = "I am the test";
  s21_strncpy(d2, s2, 0);
  ck_assert_msg(!strcmp(d2, "I am the test"), "2 test fail");

  char s3[50] = "I";
  char d3[50] = "  am the test";
  s21_strncpy(d3, s3, 1);
  ck_assert_msg(!strcmp(d3, "I am the test"), "3 test fail");

  char s4[50] = "123";
  char d4[50] = "123456";
  s21_strncpy(d4, s4, 3);
  ck_assert_msg(!strcmp(d4, "123456"), "4 test fail");

  char s5[50] = "i am the test";
  char d5[50] = "I";
  s21_strncpy(d5, s5, 13);
  ck_assert_msg(!strcmp(d5, "i am the test"), "5 test fail");
  char str1[9] = " ";
  char str2[] = " ";
  char str3[9] = " ";
  int n = 0;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(s21_strcspn_test) {
  int line = __LINE__;
  char *str1 = "012345bsb6789";
  char *str2 = "9876";
  ck_assert_msg(s21_strcspn(str1, str2) == strcspn(str1, str2), "1 test fail");

  char *str3 = "0123xcvz456789";
  char *str4 = "";
  ck_assert_msg(s21_strcspn(str3, str4) == strcspn(str3, str4), "2 test fail");

  char *str5 = "";
  char *str6 = "123";
  ck_assert_msg(s21_strcspn(str5, str6) == strcspn(str5, str6), "3 test fail");

  char *str7 = "13r 45se37";
  char *str8 = "228";
  ck_assert_msg(s21_strcspn(str7, str8) == strcspn(str7, str8), "4 test fail");

  char *str9 = "1964 her2";
  char *str10 = "64";
  ck_assert_msg(s21_strcspn(str9, str10) == strcspn(str9, str10),
                "5 test fail");
}
END_TEST

START_TEST(s21_strerror_test) {
  int line = __LINE__;
  char *str1 = s21_strerror(0);
  char *str5 = strerror(0);
  ck_assert_str_eq(str1, str5);

  char *str6 = strerror(101);
  char *str2 = s21_strerror(101);
  ck_assert_str_eq(str2, str6);

  char *str3 = s21_strerror(200);
  char *str7 = strerror(200);
  ck_assert_str_eq(str3, str7);

  char *str4 = s21_strerror(-15);
  char *str8 = strerror(-15);
  ck_assert_str_eq(str4, str8);
}
END_TEST

START_TEST(s21_strlen_test) {
  int line = __LINE__;
  char *str = "Test string";

  ck_assert_int_eq(s21_strlen(str), strlen(str));
  ck_assert_int_eq(s21_strlen("12345"), strlen("12345"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen(" "), strlen(" "));
  ck_assert_int_eq(s21_strlen("\n"), strlen("\n"));
  ck_assert_int_eq(s21_strlen("I have \0a string"),
                   strlen("I have \0a string"));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  int line = __LINE__;
  char str1[] = "this is a test";
  char str2[] = "this";
  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));

  char *str3 = "ab";
  char *res3, *res4;
  res3 = s21_strpbrk(str1, str3);
  res4 = strpbrk(str1, str3);
  ck_assert_ptr_eq(res3, res4);

  char *str5 = "abcdefgrwe qwe hjkl";
  char *str6 = "abcd";
  char *res7, *res8;
  res7 = s21_strpbrk(str5, str6);
  res8 = strpbrk(str5, str6);
  ck_assert_str_eq(res7, res8);

  char str7[] = "abc123";
  char str8[] = "123";
  ck_assert_ptr_eq(strpbrk(str7, str8), s21_strpbrk(str7, str8));

  char str10[] = "ab.,c";
  char str11[] = "127863";
  ck_assert_ptr_eq(strpbrk(str10, str11), s21_strpbrk(str10, str11));

  char str4[] = " ";
  char str9[] = " ";
  ck_assert_ptr_eq(strpbrk(str4, str9), s21_strpbrk(str4, str9));

  char str12[] = " ";
  char str13[] = " ";
  ck_assert_ptr_eq(strpbrk(str12, str13), s21_strpbrk(str12, str13));
}
END_TEST

START_TEST(s21_strrchr_test) {
  int line = __LINE__;
  char *str1 = "I ";
  char *str2 = "am";
  char *str3 = " the ";
  char *str4 = "";
  char *str5 = "TEST";
  ck_assert_msg(s21_strrchr(str1, 'I') == strrchr(str1, 'I'), "1 test fail");
  ck_assert_msg(s21_strrchr(str3, ' ') == strrchr(str3, ' '), "2 test fail");
  ck_assert_msg(s21_strrchr(str5, 'a') == strrchr(str5, 'a'), "3 test fail");
  ck_assert_msg(s21_strrchr(str2, 'm') == strrchr(str2, 'm'), "4 test fail");
  ck_assert_msg(s21_strrchr(str3, 'h') == strrchr(str3, 'h'), "5 test fail");
  ck_assert_msg(s21_strrchr(str4, ' ') == strrchr(str4, ' '), "6 test fail");
  ck_assert_msg(s21_strrchr(str5, 'e') == strrchr(str5, 'e'), "7 test fail");
}
END_TEST

START_TEST(s21_strspn_test) {
  int line = __LINE__;
  char *s1 = "I am the TEST";
  char *s2 = "am";
  char *s3 = "";

  ck_assert_msg(s21_strspn(s1, s2) == strspn(s1, s2), "1 test fail");
  ck_assert_msg(s21_strspn(s3, s2) == strspn(s3, s2), "2 test fail");
  ck_assert_msg(s21_strspn(s2, s3) == strspn(s2, s3), "3 test fail");
  ck_assert_msg(s21_strspn(s1, s3) == strspn(s1, s3), "4 test fail");
  ck_assert_msg(s21_strspn(s3, s1) == strspn(s3, s1), "5 test fail");
}
END_TEST

START_TEST(s21_strstr_test) {
  int line = __LINE__;
  char *s1 = "I am the TEST";
  char *s2 = "am";
  char *s3 = "";

  ck_assert_msg(s21_strstr(s1, s2) == strstr(s1, s2), "1st strstr test failed");
  ck_assert_msg(s21_strstr(s1, s3) == strstr(s1, s3), "2nd strstr test failed");
  ck_assert_msg(s21_strstr(s3, s2) == strstr(s3, s2), "3rd strstr test failed");
  ck_assert_msg(s21_strstr(s2, s3) == strstr(s2, s3),
                "4rth strstr test failed");
  ck_assert_msg(s21_strstr(s3, s1) == strstr(s3, s1), "5th strstr test failed");
}
END_TEST

START_TEST(s21_strtok_test) {
  int line = __LINE__;
  char str1[100] = "1fgfdh/2dsgsdg/3sdfsf/4sdfsd";
  char str2[100] = "776832768178";
  char str3[100] = "-1213002%s";
  char str4[100] = "";
  char str5[100] = "/0";
  char str6[100] = "-sdg-swedf-wqe3rd-s";
  char str7[100] = "d";
  ck_assert_msg(s21_strtok(str1, str5) == strtok(str1, str5), "1 test fail");
  ck_assert_msg(s21_strtok(str2, str4) == strtok(str2, str4), "2 test fail");
  ck_assert_msg(s21_strtok(str3, str5) == strtok(str3, str5), "3 test fail");
  ck_assert_msg(s21_strtok(str6, str7) == strtok(str6, str7), "4 test fail");

  char str_str1[] = "one/two/three(four)five";
  char delim1[] = "/()";
  char str_str2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_str1, delim1);
  char *origin_strtok = strtok(str_str2, delim2);
  while (my_strtok != NULL) {
    int line = __LINE__;
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(NULL, delim1);
    origin_strtok = strtok(NULL, delim2);
  }
}
END_TEST

START_TEST(s21_to_upper_test) {
  int line = __LINE__;
  char *str1 = (char *)s21_to_upper("slish! a nu vstal!");
  char *str2 = "SLISH! A NU VSTAL!";
  ck_assert_str_eq(str1, str2);
  free(str1);
  char *str3 = (char *)s21_to_upper("AAAAA14353423AA!!!");
  char *str4 = "AAAAA14353423AA!!!";
  ck_assert_str_eq(str3, str4);
  free(str3);
  char *str7 = (char *)s21_to_upper("KomM hieR! scHneLl!");
  char *str8 = "KOMM HIER! SCHNELL!";
  ck_assert_str_eq(str7, str8);
  free(str7);
}
END_TEST

START_TEST(s21_to_lower_test) {
  int line = __LINE__;
  char *str1 = (char *)s21_to_lower("SLISH! A NU VSTAL!");
  char *str2 = "slish! a nu vstal!";
  ck_assert_str_eq(str1, str2);
  free(str1);

  char *str3 = (char *)s21_to_lower("aaa14353423aa!!!");
  char *str4 = "aaa14353423aa!!!";
  ck_assert_str_eq(str3, str4);
  free(str3);

  char *str7 = (char *)s21_to_lower("KomM hieR! scHneLl!");
  char *str8 = "komm hier! schnell!";
  ck_assert_str_eq(str7, str8);
  free(str7);
}
END_TEST

START_TEST(s21_trim_test) {
  int line = __LINE__;
  char *str = (char *)s21_trim("****skat-riba*****", "*");
  char *str2 = "skat-riba";
  ck_assert_str_eq(str, str2);
  free(str);
  char *str3 = (char *)s21_trim("Sloniki", "iki");
  char *str4 = "Slon";
  ck_assert_str_eq(str3, str4);
  free(str3);

  char *str5 = (char *)s21_trim("", "999");
  char *str6 = "";
  ck_assert_str_eq(str5, str6);
  free(str5);

  char *str7 = (char *)s21_trim("1", "huli*5682");
  char *str8 = "1";
  ck_assert_str_eq(str7, str8);
  free(str7);

  char *str9 = (char *)s21_trim("66236934599", "69");
  char *str10 = "2369345";
  ck_assert_str_eq(str9, str10);
  free(str9);
}
END_TEST

START_TEST(s21_insert_test) {
  int line = __LINE__;
  char *str1 = (char *)s21_insert("Sloniki", "iki", 2);
  char *str2 = "Slikioniki";
  ck_assert_str_eq(str1, str2);
  free(str1);
  char *str3 = (char *)s21_insert("salo", "ska", 3);
  char *str4 = "salskao";
  ck_assert_str_eq(str3, str4);
  free(str3);
  char *str5 = (char *)s21_insert("", "help", 5);
  char *str6 = NULL;
  fail_unless(str5 == str6);
  free(str5);
  char *str7 = (char *)s21_insert("help!", "111", 5);
  char *str8 = "help!111";
  ck_assert_str_eq(str7, str8);
  free(str7);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn22) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  sprintf(data, "|%32s|\n", "111");
  s21_sprintf(data1, "|%32s|\n", "111");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn23) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  sprintf(data, "|%32s|\n", "abc");
  s21_sprintf(data1, "|%32s|\n", "abc");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn24) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  sprintf(data, "|%-32s|\n", "abc");
  s21_sprintf(data1, "|%-32s|\n", "abc");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn25) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  sprintf(data, "|%16s|\n", "nark nark");
  s21_sprintf(data1, "|%16s|\n", "nark nark");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn26) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  sprintf(data, "|%16s|\n", "nark nark");
  s21_sprintf(data1, "|%16s|\n", "nark nark");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn27) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%.03s|\n", "hello");
  int d = sprintf(data1, "|%.03s|\n", "hello");
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn28) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c =
      s21_sprintf(data, "|%.3s| kushat nado |%20s|\n", "MneEEEEEEEEE", "arbuz");
  int d =
      sprintf(data1, "|%.3s| kushat nado |%20s|\n", "MneEEEEEEEEE", "arbuz");
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn30) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%3.7d|\n", -2375);
  int d = sprintf(data1, "|%3.7d|\n", -2375);
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn31) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%-20.18u|\n", -345);
  int d = sprintf(data1, "|%-20.18u|\n", -345);
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn32) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%-20.18d|\n", -345);
  int d = sprintf(data1, "|%-20.18d|\n", -345);
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn33) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%20.2d|\n", -345);
  int d = sprintf(data1, "|%20.2d|\n", -345);
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn34) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%20d|\n", -345);
  int d = sprintf(data1, "|%20d|\n", -345);
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn37) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|test %-12i et %24s !|\n", 0, "coco");
  int d = sprintf(data1, "|test %-12i et %24s !|\n", 0, "coco");
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn38) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|test %-12i et %--2.4d %24s !|\n", 0, 25, "coco");
  int d = sprintf(data1, "|test %-12i et %--2.4d %24s !|\n", 0, 25, "coco");
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn39) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%c|\n", 'a');
  sprintf(data1, "01)SPRINTF : |%c|\n", 'a');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn40) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-c|\n", 'z');
  sprintf(data1, "01)SPRINTF : |%-c|\n", 'z');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn41) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-----c|\n", '!');
  sprintf(data1, "01)SPRINTF : |%-----c|\n", '!');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn42) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%5c|\n", 'R');
  sprintf(data1, "01)SPRINTF : |%5c|\n", 'R');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn43) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-5c|\n", 'R');
  sprintf(data1, "01)SPRINTF : |%-5c|\n", 'R');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn44) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%1c|\n", '3');
  sprintf(data1, "01)SPRINTF : |%1c|\n", '3');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn45) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%c|\n", '\0');
  sprintf(data1, "01)SPRINTF : |%c|\n", '\0');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn47) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-5c|\n", '\0');
  sprintf(data1, "01)SPRINTF : |%-5c|\n", '\0');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn48) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%1c|\n", '\0');
  sprintf(data1, "01)SPRINTF : |%1c|\n", '\0');
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn49) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%s|\n", "salut");
  sprintf(data1, "01)SPRINTF : |%s|\n", "salut");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn50) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-s|\n", "test");
  sprintf(data1, "01)SPRINTF : |%-s|\n", "test");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn51) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%---------s|\n", "test2");
  sprintf(data1, "01)SPRINTF : |%---------s|\n", "test2");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn52) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%10s|\n", "42");
  sprintf(data1, "01)SPRINTF : |%10s|\n", "42");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn53) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  char test[5] = "42";
  s21_sprintf(data, "01)SPRINTF : |%-10s|\n", test);
  sprintf(data1, "01)SPRINTF : |%-10s|\n", test);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn54) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%2s|\n", "string");
  sprintf(data1, "01)SPRINTF : |%2s|\n", "string");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn55) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-2s|\n", "string");
  sprintf(data1, "01)SPRINTF : |%-2s|\n", "string");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn56) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%.15s|\n", "precision");
  sprintf(data1, "01)SPRINTF : |%.15s|\n", "precision");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn57) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%.4s|\n", "precision");
  sprintf(data1, "01)SPRINTF : |%.4s|\n", "precision");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn58) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%.0s|\n", "precision");
  sprintf(data1, "01)SPRINTF : |%.0s|\n", "precision");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn59) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%s|\n", "\0\0\0\0\0");
  sprintf(data1, "01)SPRINTF : |%s|\n", "\0\0\0\0\0");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn60) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%10s|\n", "\0\0\0\0\0");
  sprintf(data1, "01)SPRINTF : |%10s|\n", "\0\0\0\0\0");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn61) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%s|\n", "");
  sprintf(data1, "01)SPRINTF : |%s|\n", "");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn62) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-.2s|\n", "boom");
  sprintf(data1, "01)SPRINTF : |%-.2s|\n", "boom");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn63) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%10.8s|\n", "google");
  sprintf(data1, "01)SPRINTF : |%10.8s|\n", "google");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn64) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%10.2s|\n", "twitter");
  sprintf(data1, "01)SPRINTF : |%10.2s|\n", "twitter");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn65) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%2.10s|\n", "samsung");
  sprintf(data1, "01)SPRINTF : |%2.10s|\n", "samsung");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn66) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%2.5s|\n", "sprintf");
  sprintf(data1, "01)SPRINTF : |%2.5s|\n", "sprintf");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn67) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-10.2s|\n", "424242424242");
  sprintf(data1, "01)SPRINTF : |%-10.2s|\n", "424242424242");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn68) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%1.0s|\n", "123456789");
  sprintf(data1, "01)SPRINTF : |%1.0s|\n", "123456789");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn69) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-1.0s|\n", "123456789");
  sprintf(data1, "01)SPRINTF : |%-1.0s|\n", "123456789");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn70) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%.1s|\n", "covid-19");
  sprintf(data1, "01)SPRINTF : |%.1s|\n", "covid-19");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn71) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%10.2s|\n", "covid-19");
  sprintf(data1, "01)SPRINTF : |%10.2s|\n", "covid-19");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn72) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%2.5s|\n", "covid-19");
  sprintf(data1, "01)SPRINTF : |%2.5s|\n", "covid-19");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn73) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%-10.2s|\n", "covid-19");
  sprintf(data1, "01)SPRINTF : |%-10.2s|\n", "covid-19");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn74) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "01)SPRINTF : |%1.4s| et |%-6.8s| et |%4.2s|\n", "tuuu",
              "12345", "hu");
  sprintf(data1, "01)SPRINTF : |%1.4s| et |%-6.8s| et |%4.2s|\n", "tuuu",
          "12345", "hu");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn88) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%1.1d|\n", -20);
  sprintf(data1, "02) standart PRINTF :|%1.1d|\n", -20);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn89) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%-10d|\n", -50);
  sprintf(data1, "02) standart PRINTF :|%-10d|\n", -50);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn90) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%2d|\n", -20);
  sprintf(data1, "02) standart PRINTF :|%2d|\n", -20);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn91) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%.2d|\n", -20);
  sprintf(data1, "02) standart PRINTF :|%.2d|\n", -20);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn92) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%d|\n", 42);
  sprintf(data1, "02) standart PRINTF :|%d|\n", 42);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn93) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%i|\n", 42);
  sprintf(data1, "02) standart PRINTF :|%i|\n", 42);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn94) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%-d|\n", 42);
  sprintf(data1, "02) standart PRINTF :|%-d|\n", 42);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn95) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%10d|\n", 100);
  sprintf(data1, "02) standart PRINTF :|%10d|\n", 100);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn96) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%-10d|\n", 100);
  sprintf(data1, "02) standart PRINTF :|%-10d|\n", 100);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn97) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%.10d|\n", 100);
  sprintf(data1, "02) standart PRINTF :|%.10d|\n", 100);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn98) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%10.5d|\n", 100);
  sprintf(data1, "02) standart PRINTF :|%10.5d|\n", 100);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn99) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%5.10d|\n", 64);
  sprintf(data1, "02) standart PRINTF :|%5.10d|\n", 64);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn100) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%1.1d|\n", 16);
  sprintf(data1, "02) standart PRINTF :|%1.1d|\n", 16);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn101) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%d|\n", -42);
  sprintf(data1, "02) standart PRINTF :|%d|\n", -42);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn102) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%10d|\n", -42);
  sprintf(data1, "02) standart PRINTF :|%10d|\n", -42);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn103) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%.10d|\n", -42);
  sprintf(data1, "02) standart PRINTF :|%.10d|\n", -42);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn104) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%10.5d|\n", -16);
  sprintf(data1, "02) standart PRINTF :|%10.5d|\n", -16);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn105) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%5.10d|\n", -16);
  sprintf(data1, "02) standart PRINTF :|%5.10d|\n", -16);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn106) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.2d|\n", -1);
  sprintf(data1, "02) standart PRINTF : |%.2d|\n", -1);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn107) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%-10d|\n", -80);
  sprintf(data1, "02) standart PRINTF : |%-10d|\n", -80);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn108) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%-.10d|\n", -80);
  sprintf(data1, "02) standart PRINTF : |%-.10d|\n", -80);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn109) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%6d|\n", 35);
  sprintf(data1, "02) standart PRINTF : |%6d|\n", 35);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn110) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%6d|\n", -35);
  sprintf(data1, "02) standart PRINTF : |%6d|\n", -35);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn111) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%5.3d|\n", 5);
  sprintf(data1, "02) standart PRINTF : |%5.3d|\n", 5);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn112) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%3.5d|\n", 5);
  sprintf(data1, "02) standart PRINTF : |%3.5d|\n", 5);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn113) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%5.3d|\n", -5);
  sprintf(data1, "02) standart PRINTF : |%5.3d|\n", -5);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn114) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%3.5d|\n", -5);
  sprintf(data1, "02) standart PRINTF : |%3.5d|\n", -5);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn116) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.d|\n", 100);
  sprintf(data1, "02) standart PRINTF : |%.d|\n", 100);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn155) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%u|\n", 34);
  sprintf(data1, "02) standart PRINTF : |%u|\n", 34);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn156) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%u|\n", -34);
  sprintf(data1, "02) standart PRINTF : |%u|\n", -34);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn157) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%-u|\n", 50);
  sprintf(data1, "02) standart PRINTF : |%-u|\n", 50);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn158) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%10u|\n", 90);
  sprintf(data1, "02) standart PRINTF : |%10u|\n", 90);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn159) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.10u|\n", 90);
  sprintf(data1, "02) standart PRINTF : |%.10u|\n", 90);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn160) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%15u|\n", -100);
  sprintf(data1, "02) standart PRINTF : |%15u|\n", -100);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn161) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%10.5u|\n", 52);
  sprintf(data1, "02) standart PRINTF : |%10.5u|\n", 52);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn162) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%5.10u|\n", 52);
  sprintf(data1, "02) standart PRINTF : |%5.10u|\n", 52);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn163) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%20.15u|\n", -100000);
  sprintf(data1, "02) standart PRINTF : |%20.15u|\n", -100000);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn164) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%15.20u|\n", -100000);
  sprintf(data1, "02) standart PRINTF : |%15.20u|\n", -100000);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn165) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%-10u|\n", 144);
  sprintf(data1, "02) standart PRINTF : |%-10u|\n", 144);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn166) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%-.10u|\n", 144);
  sprintf(data1, "02) standart PRINTF : |%-.10u|\n", 144);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn167) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%-20u|\n", -20000000);
  sprintf(data1, "02) standart PRINTF : |%-20u|\n", -20000000);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn168) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%8u|\n", 64);
  sprintf(data1, "02) standart PRINTF : |%8u|\n", 64);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn169) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%3.4u|\n", 10);
  sprintf(data1, "02) standart PRINTF : |%3.4u|\n", 10);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn170) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF :|%u|\n", 0);
  sprintf(data1, "02) standart PRINTF :|%u|\n", 0);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn172) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%10u|\n", 0);
  sprintf(data1, "02) standart PRINTF : |%10u|\n", 0);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn173) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.u|\n", 88);
  sprintf(data1, "02) standart PRINTF : |%.u|\n", 88);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn174) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.s|\n", "bratok");
  sprintf(data1, "02) standart PRINTF : |%.s|\n", "bratok");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn175) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.d|\n", 5, 5);
  sprintf(data1, "02) standart PRINTF : |%.d|\n", 5, 5);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn176) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.d|\n", 5, 0);
  sprintf(data1, "02) standart PRINTF : |%.d|\n", 5, 0);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn177) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "02) standart PRINTF : |%.3s|\n", "21");
  sprintf(data1, "02) standart PRINTF : |%.3s|\n", "21");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn183) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%u|\n", -1);
  sprintf(data1, "|%u|\n", -1);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn184) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%u|\n", -1);
  sprintf(data1, "|%u|\n", -1);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn185) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%f|\n", 324.34);
  sprintf(data1, "|%f|\n", 324.34);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn186) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10f|\n", 324.343);
  sprintf(data1, "|%10f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn187) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10.3f|\n", 324.343);
  sprintf(data1, "|%10.3f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn189) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-1.10f|\n", 324.343);
  sprintf(data1, "|%-1.10f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn190) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-1.10f|\n", -324.343);
  sprintf(data1, "|%-1.10f|\n", -324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn191) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.10f|\n", -324.343);
  sprintf(data1, "|%.10f|\n", -324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn192) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.10f|\n", 324.343);
  sprintf(data1, "|%.10f|\n", 324.343);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn193) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|% 10f|\n", 324.1);
  sprintf(data1, "|% 10f|\n", 324.1);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn194) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%+10f|\n", 324.1);
  sprintf(data1, "|%+10f|\n", 324.1);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn195) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10f|\n", 324.1);
  sprintf(data1, "|%10f|\n", 324.1);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn196) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10f|\n", 324.1123132);
  sprintf(data1, "|%10f|\n", 324.1123132);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn198) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.0f|\n", 324.1123132);
  sprintf(data1, "|%.0f|\n", 324.1123132);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn199) {
  int line = __LINE__;
  //
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10.0f|\n", 3.14);
  sprintf(data1, "|%10.0f|\n", 3.14);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn200) {
  int line = __LINE__;
  //
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%10.10f|\n", 320.3);
  sprintf(data1, "|%10.10f|\n", 320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn201) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-10.10f|\n", 320.3);
  sprintf(data1, "|%-10.10f|\n", 320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn202) {
  int line = __LINE__;
  //
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-10.10f|\n", 320.3);
  sprintf(data1, "|%-10.10f|\n", 320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn203) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%-10.10f|\n", -320.3);
  sprintf(data1, "|%-10.10f|\n", -320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn204) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%.0f|\n", -320.3);
  sprintf(data1, "|%.0f|\n", -320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn205) {
  int line = __LINE__;
  char data[100];
  char data1[100];

  s21_sprintf(data, "|%.0f|\n", -320.3);
  sprintf(data1, "|%.0f|\n", -320.3);

  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn206) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.0f|\n", -320.3);
  sprintf(data1, "|%5.0f|\n", -320.3);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn207) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.0f|\n", 3.141592653589793);
  sprintf(data1, "|%5.0f|\n", 3.141592653589793);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn208) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.0f|\n", 3.141592653589793);
  sprintf(data1, "|%5.0f|\n", 3.141592653589793);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn209) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|% -5.1f|\n", 0.001);
  sprintf(data1, "|% -5.1f|\n", 0.001);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn210) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.1f|\n", 324.324);
  sprintf(data1, "|%5.1f|\n", 324.324);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestLaslhyn211) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "|%5.3f|\n", 0.0001);
  sprintf(data1, "|%5.3f|\n", 0.0001);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho6) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%i|\n", 10);
  s21_sprintf(str1, "|%i|\n", 10);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho54) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%5.0d|\n", 0);
  s21_sprintf(str1, "|%5.0d|\n", 0);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho55) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%-5.d|\n", 0);
  s21_sprintf(str1, "|%-5.d|\n", 0);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho68) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%20.18u|\n", -345);
  s21_sprintf(str1, "|%20.18u|\n", -345);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho69) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%-20.18u|\n", -345);
  s21_sprintf(str1, "|%-20.18u|\n", -345);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho127) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%8s|\n", "abra");
  s21_sprintf(str1, "|%8s|\n", "abra");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho128) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%-8s|\n", "abrafdefgbr");
  s21_sprintf(str1, "|%-8s|\n", "abrafdefgbr");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho129) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%8s|\n", "abra");
  s21_sprintf(str1, "|%8s|\n", "abra");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho130) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%8s|\n", "abrafdefgbr");
  s21_sprintf(str1, "|%8s|\n", "abrafdefgbr");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho131) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%8s|\n", "abra");
  s21_sprintf(str1, "|%8s|\n", "abra");
  ck_assert_str_eq(str, str1);
}

START_TEST(SPRINTFTestdogletho187) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "%i", 0);
  s21_sprintf(str1, "%i", 0);
  ck_assert_str_eq(str, str1);
}
END_TEST

// --------------Check for c-------------

START_TEST(SPRINTFTestdogletho190) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%c|\n", 'a');
  s21_sprintf(str1, "|%c|\n", 'a');
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho197) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%.c|\n", 'a');
  s21_sprintf(str1, "|%.c|\n", 'a');
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho198) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%-.c|\n", 'a');
  s21_sprintf(str1, "|%-.c|\n", 'a');
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho232) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  for (int i = -101; i <= 101; i++) {
    int line = __LINE__;
    sprintf(str, "%+i", i);
    s21_sprintf(str1, "%+i", i);
    ck_assert_str_eq(str, str1);
  }
}
END_TEST

START_TEST(SPRINTFTestdogletho233) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  for (int i = -101; i <= 101; i++) {
    int line = __LINE__;
    sprintf(str, "%+d", i);
    s21_sprintf(str1, "%+d", i);
    ck_assert_str_eq(str, str1);
  }
}
END_TEST

START_TEST(SPRINTFTestdogletho234) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, " %+d %+i %+d %+d", 2147483647, -2147483647, 21, 0);
  s21_sprintf(str1, " %+d %+i %+d %+d", 2147483647, -2147483647, 21, 0);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho235) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, " %+li ", 9223372036854775807);
  s21_sprintf(str1, " %+li ", 9223372036854775807);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho236) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, " %+ld ", 9223372036854775807);
  s21_sprintf(str1, " %+ld ", 9223372036854775807);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho237) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, " %+-5d %+-5i", -7, 0);
  s21_sprintf(str1, " %+-5d %+-5i", -7, 0);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho239) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  sprintf(str, "|%u|\n", 10);
  s21_sprintf(str1, "|%u|\n", 10);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(SPRINTFTestdogletho259) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  for (int i = -101; i <= 101;) {
    int line = __LINE__;
    sprintf(str, "% d", i);
    s21_sprintf(str1, "% d", i);
    i = i + 7;
    ck_assert_str_eq(str, str1);
  }
}
END_TEST

START_TEST(SPRINTFTestdogletho261) {
  int line = __LINE__;
  char str[100];
  char str1[100];
  for (int i = -101; i <= 101;) {
    int line = __LINE__;
    sprintf(str, "% -i % -d % -5d", i, i + 1, 143646235);
    s21_sprintf(str1, "% -i % -d % -5d", i, i + 1, 143646235);
    i = i + 7;
    ck_assert_str_eq(str, str1);
  }
}
END_TEST

START_TEST(SPRINTFTestdogletho282) {
  int line = __LINE__;
  char data[100];
  char data1[100];

  s21_sprintf(data, "%s ", "hello world");
  sprintf(data1, "%s ", "hello world");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestdogletho283) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  s21_sprintf(data, "%-3.1s", "\0");
  sprintf(data1, "%-3.1s", "\0");
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard1) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  s21_sprintf(data, "%li", 100000000000000000);
  sprintf(data1, "%li", 100000000000000000);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard3) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  s21_sprintf(data, "%lu", 100000000000000000);
  sprintf(data1, "%lu", 100000000000000000);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard6) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  s21_sprintf(data, "%ld", 100000000000000000);
  sprintf(data1, "%ld", 100000000000000000);
  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard7) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  short int i = -30000;
  s21_sprintf(data, "%hi", i);
  sprintf(data1, "%hi", i);

  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard9) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  short int i = -30000;
  s21_sprintf(data, "%hu", i);
  sprintf(data1, "%hu", i);

  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard12) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  short int i = -30000;
  s21_sprintf(data, "%hd", i);
  sprintf(data1, "%hd", i);

  ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(SPRINTFTestRleonard13) {
  int line = __LINE__;
  char data[200];
  char data1[200];
  s21_sprintf(data, "%lc", 'c');
  sprintf(data1, "%lc", 'c');

  ck_assert_str_eq(data, data1);
}
END_TEST

// ###############################################################################################################################################

START_TEST(simple_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple value %d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(precise_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(minus_width_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(plus_width_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(padding_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%12i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_long_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+5.31li";
  long int val = 698518581899;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flags_short_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16.9hi";
  short int val = 6958;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(space_flag_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_width) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_flags) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_precision) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_many_flags) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 5.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_short) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hu";
  unsigned short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_long) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_many) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(octal_short) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hd";
  short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_zero) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_char) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(one_precision) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_flags) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% -5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_width) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many_flags) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_precision) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_width) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_flags) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_long) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_many) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_width_huge) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_flags) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(all_empty) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(empty_format_and_parameters) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_char) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_string) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                   sprintf(str2, "%s", "Drop Sega PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_string) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
      sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_dec) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_dec) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
                   sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_int) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
                   sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_float) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_float) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_unsigned_dec) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_unsigned_dec) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100),
                   sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
                           (unsigned)666, (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char_with_alignment_left) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf1) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%10ld";

  ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf2) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%1.1f";

  ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf3) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%8.3c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf4) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+5.5d aboba";

  int val = 10000;
  int a = s21_sprintf(str1, format, val);
  int b = sprintf(str2, format, val);
  ck_assert_int_eq(a, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf7) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.4s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"),
                   sprintf(str2, format, "aboba floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf8) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%6.6u";

  ck_assert_int_eq(s21_sprintf(str1, format, 12341151),
                   sprintf(str2, format, 12341151));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf9) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%li%ld%lu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666666666666, 777, 111),
                   sprintf(str2, format, 666666666666, 777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf10) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%hi%hd%hu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111),
                   sprintf(str2, format, 666, -777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf11) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+li%+lu%+d%+lf";

  ck_assert_int_eq(s21_sprintf(str1, format, -123, 321, -5555, -1213.123),
                   sprintf(str2, format, -123, 321, -5555, -1213.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf16) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf17) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba likes floppa"),
                   sprintf(str2, format, "aboba likes floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf18) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s% c";

  ck_assert_int_eq(s21_sprintf(str1, format, "", 'f'),
                   sprintf(str2, format, "", 'f'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf19) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%210s";

  ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
                   sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf20) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-115s";

  ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"),
                   sprintf(str2, format, "Nick her"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf24) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+2.1c%+4.2d%+5.4i%+10.2f%+55.55s%+1.1u";

  ck_assert_int_eq(
      s21_sprintf(str1, format, 'f', 21, 42, 666.666,
                  "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11),
      sprintf(str2, format, 'f', 21, 42, 666.666,
              "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf25) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 121.123),
                   sprintf(str2, format, 121.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf26) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%%";

  ck_assert_int_eq(s21_sprintf(str1, format), sprintf(str2, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf27) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%%%%%%%%";

  ck_assert_int_eq(s21_sprintf(str1, format), sprintf(str2, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf29) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.111),
                   sprintf(str2, format, 111.111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf30) {
  int line = __LINE__;
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.1d";

  ck_assert_int_eq(s21_sprintf(str1, format, 111), sprintf(str2, format, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_pr_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %%");
  s21_sprintf(test_your, "Hello %%");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_pr_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello 2022 World");
  s21_sprintf(test_your, "Hello 2022 World");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %c", 'W');
  s21_sprintf(test_your, "Hello %c", 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %-5c", 'W');
  s21_sprintf(test_your, "Hello %-5c", 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_3) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %5c", 'W');
  s21_sprintf(test_your, "Hello %5c", 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_4) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %-c", 'W');
  s21_sprintf(test_your, "Hello %-c", 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_5) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %c", 'W');
  s21_sprintf(test_your, "Hello %c", 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_6) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%cHello %c", 's', 'W');
  s21_sprintf(test_your, "%cHello %c", 's', 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_7) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "He%cllo %-5c", 's', 'W');
  s21_sprintf(test_your, "He%cllo %-5c", 's', 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_8) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%5cHello %5c", 's', 'W');
  s21_sprintf(test_your, "%5cHello %5c", 's', 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_9) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%-10cHello %-c", 's', 'W');
  s21_sprintf(test_your, "%-10cHello %-c", 's', 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_10) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "He%%llo %c", 'W');
  s21_sprintf(test_your, "He%%llo %c", 'W');
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %d", 23);
  s21_sprintf(test_your, "Hello %d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %5d", 23);
  s21_sprintf(test_your, "Hello %5d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_3) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %-6d", 23);
  s21_sprintf(test_your, "Hello %-6d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_4) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %+d", 23);
  s21_sprintf(test_your, "Hello %+d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_5) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello % d", 23);
  s21_sprintf(test_your, "Hello % d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_6) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %hd", 23);
  s21_sprintf(test_your, "Hello %hd", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_7) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %ld", 238230000006325000);
  s21_sprintf(test_your, "Hello %ld", 238230000006325000);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_8) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello % 10d", 23);
  s21_sprintf(test_your, "Hello % 10d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_9) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %+10d", 23);
  s21_sprintf(test_your, "Hello %+10d", 23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_10) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %+10d", -23);
  s21_sprintf(test_your, "Hello %+10d", -23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_11) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello % 10d", -23);
  s21_sprintf(test_your, "Hello % 10d", -23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_and_c_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %d %18d", 5, -23);
  s21_sprintf(test_your, "Hello %d %18d", 5, -23);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %d %f", 5, -23.0);
  s21_sprintf(test_your, "Hello %d %f", 5, -23.0);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %s %f", "abc", -23.0);
  s21_sprintf(test_your, "Hello %s %f", "abc", -23.0);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_3) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hel%ulo %s %f", 100, "abc", -23.0);
  s21_sprintf(test_your, "Hel%ulo %s %f", 100, "abc", -23.0);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_4) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %s %.3f", "abc", -23.0000001);
  s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.0000001);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_5) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %s %.7f", "abc", -23.999999);
  s21_sprintf(test_your, "Hello %s %.7f", "abc", -23.999999);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_6) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "Hello %s %.3f", "abc", -23.999999);
  s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.999999);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_7) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "H%ldello %s", 1234567890123456789,
          "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght");
  s21_sprintf(test_your, "H%ldello %s", 1234567890123456789,
              "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_8) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "H%uello %s", 123456789,
          "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght");
  s21_sprintf(test_your, "H%uello %s", 123456789,
              "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_9) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%lfdslkj", 1234.0);
  s21_sprintf(test_your, "saeflkahj%lfdslkj", 1234.0);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_12) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% 10.12f dslkj", 0.235300);
  s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", 0.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_16) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%-f dslkj", -4353.235300);
  s21_sprintf(test_your, "saeflkahj%-f dslkj", -4353.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_18) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%-f dslkj", 0.235300);
  s21_sprintf(test_your, "saeflkahj%-f dslkj", 0.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_19) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%+f dslkj", 0.235300);
  s21_sprintf(test_your, "saeflkahj%+f dslkj", 0.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_20) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% f dslkj", -4353.235300);
  s21_sprintf(test_your, "saeflkahj% f dslkj", -4353.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_21) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% 8f dslkj", -4353.235300);
  s21_sprintf(test_your, "saeflkahj% 8f dslkj", -4353.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_22) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% -f dslkj", 4353.235300);
  s21_sprintf(test_your, "saeflkahj% -f dslkj", 4353.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_23) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% -10f dslkj", -0.235300);
  s21_sprintf(test_your, "saeflkahj% -10f dslkj", -0.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_24) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% .10f dslkj", -4353.235300);
  s21_sprintf(test_your, "saeflkahj%.10f dslkj", -4353.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_25) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%.10f dslkj", 13.235300);
  s21_sprintf(test_your, "saeflkahj%.10f dslkj", 13.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_26) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%.f dslkj", 12.235300);
  s21_sprintf(test_your, "saeflkahj%.f dslkj", 12.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_27) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj% .f dslkj", 345.235300);
  s21_sprintf(test_your, "saeflkahj% .f dslkj", 345.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_28) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%10.f dslkj", 0.235300);
  s21_sprintf(test_your, "saeflkahj%10.f dslkj", 0.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_30) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%-.f dslkj", 20.235300);
  s21_sprintf(test_your, "saeflkahj%-.f dslkj", 20.235300);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_31) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%f dslkj", 0.000000006);
  s21_sprintf(test_your, "saeflkahj%f dslkj", 0.000000006);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_32) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%.f dslkj", 0.000000006);
  s21_sprintf(test_your, "saeflkahj%.f dslkj", 0.000000006);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_33) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%12f dslkj", 0.000000006);
  s21_sprintf(test_your, "saeflkahj%12f dslkj", 0.000000006);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_34) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%.12f dslkj", 0.000000006);
  s21_sprintf(test_your, "saeflkahj%.12f dslkj", 0.000000006);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_35) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%-.12f dslkj", 0.000000006);
  s21_sprintf(test_your, "saeflkahj%-.12f dslkj", 0.000000006);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_36) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%%%%%%%%%% dslkj");
  s21_sprintf(test_your, "saeflkahj%%%%%%%%%% dslkj");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_37) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%%%%%%%%%%%-.12f dslkj", 0.000000006);
  s21_sprintf(test_your, "saeflkahj%%%%%%%%%%%-.12f dslkj", 0.000000006);
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_38) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahj%s dslkj", "0.000000006");
  s21_sprintf(test_your, "saeflkahj%s dslkj", "0.000000006");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_39) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "saeflkahjdslkj%s", "^&*(=...%");
  s21_sprintf(test_your, "saeflkahjdslkj%s", "^&*(=...%");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_40) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%ssaeflkahj dslkj", "^&*(=...%");
  s21_sprintf(test_your, "%ssaeflkahj dslkj", "^&*(=...%");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_41) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%ssaeflkahj%sdslkj%s", "^&*(=...%", "jk", "");
  s21_sprintf(test_your, "%ssaeflkahj%sdslkj%s", "^&*(=...%", "jk", "");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_42) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%ssaeflkahj%sdslkj%s", "", "", " ");
  s21_sprintf(test_your, "%ssaeflkahj%sdslkj%s", "", "", " ");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_43) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%-ssaeflkahj%1sdslkj%s", "^&*(=...%", "jk", "");
  s21_sprintf(test_your, "%-ssaeflkahj%1sdslkj%s", "^&*(=...%", "jk", "");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_44) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  sprintf(test_original, "%3ssaeflkahj%1sdslkj%10s", "^&*(=...%", " ", "");
  s21_sprintf(test_your, "%3ssaeflkahj%1sdslkj%10s", "^&*(=...%", " ", "");
  ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(int_sprintf_pr_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %%"),
                   s21_sprintf(test_your, "Hello %%"));
}
END_TEST

START_TEST(int_sprintf_pr_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello 2022 World"),
                   s21_sprintf(test_your, "Hello 2022 World"));
}
END_TEST

START_TEST(int_sprintf_c_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %c", 'W'),
                   s21_sprintf(test_your, "Hello %c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %-5c", 'W'),
                   s21_sprintf(test_your, "Hello %-5c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_3) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %5c", 'W'),
                   s21_sprintf(test_your, "Hello %5c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_4) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %-c", 'W'),
                   s21_sprintf(test_your, "Hello %-c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_5) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %c", 'W'),
                   s21_sprintf(test_your, "Hello %c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_6) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "%cHello %c", 's', 'W'),
                   s21_sprintf(test_your, "%cHello %c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_7) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "He%cllo %-5c", 's', 'W'),
                   s21_sprintf(test_your, "He%cllo %-5c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_8) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "%5cHello %5c", 's', 'W'),
                   s21_sprintf(test_your, "%5cHello %5c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_9) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "%-10cHello %-c", 's', 'W'),
                   s21_sprintf(test_your, "%-10cHello %-c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_10) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "He%%llo %c", 'W'),
                   s21_sprintf(test_your, "He%%llo %c", 'W'));
}
END_TEST

START_TEST(int_sprintf_d_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %d", 23),
                   s21_sprintf(test_your, "Hello %d", 23));
}
END_TEST

START_TEST(int_sprintf_d_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %5d", 23),
                   s21_sprintf(test_your, "Hello %5d", 23));
}
END_TEST

START_TEST(int_sprintf_d_3) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %-6d", 23),
                   s21_sprintf(test_your, "Hello %-6d", 23));
}
END_TEST

START_TEST(int_sprintf_d_4) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %+d", 23),
                   s21_sprintf(test_your, "Hello %+d", 23));
}
END_TEST

START_TEST(int_sprintf_d_5) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello % d", 23),
                   s21_sprintf(test_your, "Hello % d", 23));
}
END_TEST

START_TEST(int_sprintf_d_6) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %hd", 23),
                   s21_sprintf(test_your, "Hello %hd", 23));
}
END_TEST

START_TEST(int_sprintf_d_7) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %ld", 238230000006325000),
                   s21_sprintf(test_your, "Hello %ld", 238230000006325000));
}
END_TEST

START_TEST(int_sprintf_d_8) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello % 10d", 23),
                   s21_sprintf(test_your, "Hello % 10d", 23));
}
END_TEST

START_TEST(int_sprintf_d_9) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %+10d", 23),
                   s21_sprintf(test_your, "Hello %+10d", 23));
}
END_TEST

START_TEST(int_sprintf_d_10) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %+10d", -23),
                   s21_sprintf(test_your, "Hello %+10d", -23));
}
END_TEST

START_TEST(int_sprintf_d_11) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello % 10d", -23),
                   s21_sprintf(test_your, "Hello % 10d", -23));
}
END_TEST

START_TEST(int_sprintf_d_and_c_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %d %18d", 5, -23),
                   s21_sprintf(test_your, "Hello %d %18d", 5, -23));
}
END_TEST

START_TEST(int_sprintf_1) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %d %f", 5, -23.0),
                   s21_sprintf(test_your, "Hello %d %f", 5, -23.0));
}
END_TEST

START_TEST(int_sprintf_2) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %s %f", "abc", -23.0),
                   s21_sprintf(test_your, "Hello %s %f", "abc", -23.0));
}
END_TEST

START_TEST(int_sprintf_3) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hel%ulo %s %f", 100, "abc", -23.0),
                   s21_sprintf(test_your, "Hel%ulo %s %f", 100, "abc", -23.0));
}
END_TEST

START_TEST(int_sprintf_4) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %s %.3f", "abc", -23.0000001),
                   s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.0000001));
}
END_TEST

START_TEST(int_sprintf_5) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %s %.7f", "abc", -23.999999),
                   s21_sprintf(test_your, "Hello %s %.7f", "abc", -23.999999));
}
END_TEST

START_TEST(int_sprintf_6) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "Hello %s %.3f", "abc", -23.999999),
                   s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.999999));
}
END_TEST

START_TEST(int_sprintf_7) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "H%ldello %s", 1234567890123456789,
              "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"),
      s21_sprintf(test_your, "H%ldello %s", 1234567890123456789,
                  "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"));
}
END_TEST

START_TEST(int_sprintf_8) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "H%uello %s", 123456789,
              "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"),
      s21_sprintf(test_your, "H%uello %s", 123456789,
                  "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"));
}
END_TEST

START_TEST(int_sprintf_9) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj%lfdslkj", 1234.0),
                   s21_sprintf(test_your, "saeflkahj%lfdslkj", 1234.0));
}
END_TEST

START_TEST(int_sprintf_11) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "saeflkahj%+10.12f dslkj", 4353.235300),
      s21_sprintf(test_your, "saeflkahj%+10.12f dslkj", 4353.235300));
}
END_TEST

START_TEST(int_sprintf_12) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj% 10.12f dslkj", 0.235300),
                   s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", 0.235300));
}
END_TEST

START_TEST(int_sprintf_13) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "saeflkahj% 10.12f dslkj", -4353.235300),
      s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_14) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "saeflkahj%-.12f dslkj", 4353.235300),
      s21_sprintf(test_your, "saeflkahj%-.12f dslkj", 4353.235300));
}
END_TEST

START_TEST(int_sprintf_15) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "saeflkahj%-.12f dslkj", -4353.235300),
      s21_sprintf(test_your, "saeflkahj%-.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_16) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj%-f dslkj", -4353.235300),
                   s21_sprintf(test_your, "saeflkahj%-f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_17) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "saeflkahj%-.12f dslkj", -4353.235300),
      s21_sprintf(test_your, "saeflkahj%-.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_18) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj%-f dslkj", 0.235300),
                   s21_sprintf(test_your, "saeflkahj%-f dslkj", 0.235300));
}
END_TEST

START_TEST(int_sprintf_19) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj%+f dslkj", 0.235300),
                   s21_sprintf(test_your, "saeflkahj%+f dslkj", 0.235300));
}
END_TEST

START_TEST(int_sprintf_20) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj% f dslkj", -4353.235300),
                   s21_sprintf(test_your, "saeflkahj% f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_21) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(sprintf(test_original, "saeflkahj% 8f dslkj", -4353.235300),
                   s21_sprintf(test_your, "saeflkahj% 8f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_22) {
  int line = __LINE__;
  char test_original[1024] = "";
  char test_your[1024] = "";
  ck_assert_int_eq(
      sprintf(test_original, "%s%s%s%s%s%ssaeflkahj% 8f dslkj", "ds", " ", " ",
              "0", "+", "9999999", -4353.235300),
      s21_sprintf(test_your, "%s%s%s%s%s%ssaeflkahj% 8f dslkj", "ds", " ", " ",
                  "0", "+", "9999999", -4353.235300));
}
END_TEST

START_TEST(sprintf_221) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %8d", 34);
  char str2[1024] = "";
  sprintf(str2, "Hola %8d", 34);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_222) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %8d", 34);
  char str2[1024] = "";
  sprintf(str2, "Hola %8d", 34);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_223) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %-8d", 34);
  char str2[1024] = "";
  sprintf(str2, "Hola %-8d", 34);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_224) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %18d", 34);
  char str2[1024] = "";
  sprintf(str2, "Hola %18d", 34);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_225) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %18d", 34);
  char str2[1024] = "";
  sprintf(str2, "Hola %18d", 34);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_226) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %-18d", 34);
  char str2[1024] = "";
  sprintf(str2, "Hola %-18d", 34);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_227) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %2d", 343432);
  char str2[1024] = "";
  sprintf(str2, "Hola %2d", 343432);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_228) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %-2d", 34423342);
  char str2[1024] = "";
  sprintf(str2, "Hola %-2d", 34423342);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_229) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %9s", "Mundo");
  char str2[1024] = "";
  sprintf(str2, "Hola %9s", "Mundo");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2210) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %-9s", "Mundo");
  char str2[1024] = "";
  sprintf(str2, "Hola %-9s", "Mundo");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2211) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %2s", "Mundo");
  char str2[1024] = "";
  sprintf(str2, "Hola %2s", "Mundo");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2212) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %-2s", "Mundo");
  char str2[1024] = "";
  sprintf(str2, "Hola %-2s", "Mundo");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2213) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %12s", "Mundo");
  char str2[1024] = "";
  sprintf(str2, "Hola %12s", "Mundo");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2214) {
  int line = __LINE__;
  char str1[1024] = "";
  s21_sprintf(str1, "Hola %-12s", "Mundo");
  char str2[1024] = "";
  sprintf(str2, "Hola %-12s", "Mundo");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_231) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %d", 7);
  sprintf(str1, "Hola %d", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_232) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%d:%d:%d", 7, 4, 0);
  sprintf(str1, "%d:%d:%d", 7, 4, 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_233) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MAX %d", INT_MAX);
  sprintf(str1, "MAX %d", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_234) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MIN %d", INT_MIN);
  sprintf(str1, "MIN %d", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_235) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %i", 3534555);
  sprintf(str1, "Hola %i", 3534555);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_236) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %+d", 3534555);
  sprintf(str1, "Hola %+d", 3534555);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_237) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5d'", 7);
  sprintf(str1, "padding '%5d'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_238) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5d'", INT_MAX);
  sprintf(str1, "padding '%5d'", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_239) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5d'", INT_MIN);
  sprintf(str1, "padding '%5d'", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2310) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5d'", 7);
  sprintf(str1, "padding '%5d'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2311) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5d'", INT_MAX);
  sprintf(str1, "padding '%5d'", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2312) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5d'", INT_MIN);
  sprintf(str1, "padding '%5d'", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2313) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5d'", 7);
  sprintf(str1, "padding '%-5d'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2314) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5d'", INT_MAX);
  sprintf(str1, "padding '%-5d'", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2315) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5d'", INT_MIN);
  sprintf(str1, "padding '%-5d'", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2316) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5d'", 7);
  sprintf(str1, "precision '%.5d'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2317) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5d'", INT_MAX);
  sprintf(str1, "precision '%.5d'", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2318) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5d'", INT_MIN);
  sprintf(str1, "precision '%.5d'", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2319) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5d'", 7);
  sprintf(str1, "precision '%3.5d'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2320) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5d'", INT_MAX);
  sprintf(str1, "precision '%3.5d'", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2321) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5d'", INT_MIN);
  sprintf(str1, "precision '%3.5d'", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2322) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5d'", 7);
  sprintf(str1, "precision '%-3.5d'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2323) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5d'", INT_MAX);
  sprintf(str1, "precision '%-3.5d'", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2324) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5d'", INT_MIN);
  sprintf(str1, "precision '%-3.5d'", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2325) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %u", 7);
  sprintf(str1, "Hola %u", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2326) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%u:%u:%u", 7, 4, 0);
  sprintf(str1, "%u:%u:%u", 7, 4, 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2327) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MAX %u", UINT_MAX);
  sprintf(str1, "MAX %u", UINT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2328) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MIN %u", 0);
  sprintf(str1, "MIN %u", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2329) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5u'", 7);
  sprintf(str1, "padding '%5u'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2330) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5u'", UINT_MAX);
  sprintf(str1, "padding '%5u'", UINT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2331) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5u'", 0);
  sprintf(str1, "padding '%5u'", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2332) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5u'", 7);
  sprintf(str1, "padding '%-5u'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2333) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5u'", UINT_MAX);
  sprintf(str1, "padding '%-5u'", UINT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2334) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5u'", 0);
  sprintf(str1, "padding '%-5u'", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2335) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5u'", 7);
  sprintf(str1, "precision '%.5u'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2336) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5u'", UINT_MAX);
  sprintf(str1, "precision '%.5u'", UINT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2337) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5u'", 0);
  sprintf(str1, "precision '%.5u'", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2338) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5u'", 7);
  sprintf(str1, "precision '%3.5u'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2339) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5u'", UINT_MAX);
  sprintf(str1, "precision '%3.5u'", UINT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2340) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5u'", 0);
  sprintf(str1, "precision '%3.5u'", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2341) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5u'", 7);
  sprintf(str1, "precision '%-3.5u'", 7);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2342) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5u'", UINT_MAX);
  sprintf(str1, "precision '%-3.5u'", UINT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2343) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5u'", 0);
  sprintf(str1, "precision '%-3.5u'", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2344) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %ld", 3534535547l);
  sprintf(str1, "Hola %ld", 3534535547l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2345) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%ld:%ld:%ld", 7l, 34543245324l, 0l);
  sprintf(str1, "%ld:%ld:%ld", 7l, 34543245324l, 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2346) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%ld", -5435432542l);
  sprintf(str1, "%ld", -5435432542l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2347) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MAX %ld", LONG_MAX);
  sprintf(str1, "MAX %ld", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2348) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MIN %ld", LONG_MIN);
  sprintf(str1, "MIN %ld", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2349) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %li", 3534535547l);
  sprintf(str1, "Hola %li", 3534535547l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2350) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5ld'", 72342l);
  sprintf(str1, "padding '%5ld'", 72342l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2351) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5ld'", LONG_MAX);
  sprintf(str1, "padding '%5ld'", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2352) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5ld'", LONG_MIN);
  sprintf(str1, "padding '%5ld'", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2353) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5ld'", 72342l);
  sprintf(str1, "padding '%5ld'", 72342l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2354) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5ld'", LONG_MAX);
  sprintf(str1, "padding '%5ld'", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2355) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5ld'", LONG_MIN);
  sprintf(str1, "padding '%5ld'", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2356) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5ld'", 742343l);
  sprintf(str1, "padding '%-5ld'", 742343l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2357) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5ld'", LONG_MAX);
  sprintf(str1, "padding '%-5ld'", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2358) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5ld'", LONG_MIN);
  sprintf(str1, "padding '%-5ld'", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2359) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5ld'", 754354l);
  sprintf(str1, "precision '%.5ld'", 754354l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2360) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5ld'", LONG_MAX);
  sprintf(str1, "precision '%.5ld'", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2361) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5ld'", LONG_MIN);
  sprintf(str1, "precision '%.5ld'", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2362) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5ld'", 7343l);
  sprintf(str1, "precision '%3.5ld'", 7343l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2363) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5ld'", LONG_MAX);
  sprintf(str1, "precision '%3.5ld'", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2364) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5ld'", LONG_MIN);
  sprintf(str1, "precision '%3.5ld'", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2365) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5ld'", 754354l);
  sprintf(str1, "precision '%-3.5ld'", 754354l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2366) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5ld'", LONG_MAX);
  sprintf(str1, "precision '%-3.5ld'", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2367) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5ld'", LONG_MIN);
  sprintf(str1, "precision '%-3.5ld'", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2368) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "Hola %lu", 7l);
  sprintf(str1, "Hola %lu", 7l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2369) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%lu:%lu:%lu", 7l, 4l, 0l);
  sprintf(str1, "%lu:%lu:%lu", 7l, 4l, 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2370) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MAX %lu", ULONG_MAX);
  sprintf(str1, "MAX %lu", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2371) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "MIN %lu", 0l);
  sprintf(str1, "MIN %lu", 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2372) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5lu'", 7l);
  sprintf(str1, "padding '%5lu'", 7l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2373) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5lu'", ULONG_MAX);
  sprintf(str1, "padding '%5lu'", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2374) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%5lu'", 0l);
  sprintf(str1, "padding '%5lu'", 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2375) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5lu'", 7l);
  sprintf(str1, "padding '%-5lu'", 7l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2376) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5lu'", ULONG_MAX);
  sprintf(str1, "padding '%-5lu'", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2377) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "padding '%-5lu'", 0l);
  sprintf(str1, "padding '%-5lu'", 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2378) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5lu'", 7l);
  sprintf(str1, "precision '%.5lu'", 7l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2379) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5lu'", ULONG_MAX);
  sprintf(str1, "precision '%.5lu'", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2380) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%.5lu'", 0l);
  sprintf(str1, "precision '%.5lu'", 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2381) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5lu'", 7l);
  sprintf(str1, "precision '%3.5lu'", 7l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2382) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5lu'", ULONG_MAX);
  sprintf(str1, "precision '%3.5lu'", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2383) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%3.5lu'", 0l);
  sprintf(str1, "precision '%3.5lu'", 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2384) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5lu'", 7l);
  sprintf(str1, "precision '%-3.5lu'", 7l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2385) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5lu'", ULONG_MAX);
  sprintf(str1, "precision '%-3.5lu'", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2386) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%-3.5lu'", 0l);
  sprintf(str1, "precision '%-3.5lu'", 0l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2387) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.5f", 3.5);
  sprintf(str1, "%.5f", 3.5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2388) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.5f", -3.5);
  sprintf(str1, "%.5f", -3.5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2391) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.5f", 0.0);
  sprintf(str1, "%.5f", 0.0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2392) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.5f", 3.5458730589043);
  sprintf(str1, "%.5f", 3.5458730589043);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2393) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.5f", -3.5458730589043);
  sprintf(str1, "%.5f", -3.5458730589043);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2394) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.4f", 3.5458730589043);
  sprintf(str1, "%10.4f", 3.5458730589043);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2395) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.4f", -3.5458730589043);
  sprintf(str1, "%10.4f", -3.5458730589043);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2401) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.5d", INT_MIN);
  sprintf(str1, "%10.5d", INT_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2402) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.5d", INT_MAX);
  sprintf(str1, "%10.5d", INT_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2403) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.5ld", LONG_MIN);
  sprintf(str1, "%10.5ld", LONG_MIN);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2404) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.5ld", LONG_MAX);
  sprintf(str1, "%10.5ld", LONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2405) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%10.5lu", ULONG_MAX);
  sprintf(str1, "%10.5lu", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070501) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%f", 6.1);
  sprintf(str1, "%f", 6.1);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070502) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%f", 06.1);
  sprintf(str1, "%f", 06.1);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070503) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%f", 6.01);
  sprintf(str1, "%f", 6.01);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070504) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.f", 6.01);
  sprintf(str1, "%.f", 6.01);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070505) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.0f", 6.01);
  sprintf(str1, "%.0f", 6.01);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070506) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.1f", 6.01);
  sprintf(str1, "%.1f", 6.01);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070507) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%f", 1.23e+07);
  sprintf(str1, "%f", 1.23e+07);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070508) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%f", 1234561e+00);
  sprintf(str1, "%f", 1234561e+00);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070510) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%.9f", 1000000000.00);
  sprintf(str1, "%.9f", 1000000000.00);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070513) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "%3.f", 0.0);
  sprintf(str1, "%3.f", 0.0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2405x) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%h%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%h%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2406x) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%3.15h%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%3.15h%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2408) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%03.15h%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%03.15h%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2409) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#0%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#0%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2410) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#015.20%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#015.20%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2411) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#0- 15.5%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#0- 15.5%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2412) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#0-+ 3.2%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#0-+ 3.2%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2413) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#0+ 3.2%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#0+ 3.2%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2414) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#0 15.5%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#0 15.5%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2415) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#-3%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#-3%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2416) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#-15.0%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#-15.0%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2417) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#-+15.0%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#-+15.0%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2418) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#- 15.0%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#- 15.0%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2419) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#-+ 15.0%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#-+ 15.0%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2420) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#-+ 15.20%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#-+ 15.20%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2421) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#+%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#+%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2423) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%#+15%%] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%#+15%%] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2427) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%d] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%d] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2428) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "[%d]", 0);
  sprintf(str1, "[%d]", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2429) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%15.20d] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%15.20d] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2431) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%015.20d] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%015.20d] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2433) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "precision '%f'", 6.1);
  sprintf(str1, "precision '%f'", 6.1);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2434) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%f] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%f] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2436) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%%3.15f] - l.%d\n" - 2, line);
  sprintf(str1, " - %d - [%%3.15f] - l.%d\n" - 2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2708) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%d] - l.%d\n, [%d]", 0, -2, line);
  sprintf(str1, "- %d - [%%d] - l.%d\n, [%d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2709) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%d] - l.%d\n, [%d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%d] - l.%d\n, [%d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2710) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%d] - l.%d\n, [%d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%d] - l.%d\n, [%d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2711) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, line);
  sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2712) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2713) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2714) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2715) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2716) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2717) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2718) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2719) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2720) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2721) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2722) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2723) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2724) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2725) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2726) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15d] - l.%d\n, [%15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%15d] - l.%d\n, [%15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2727) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2728) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2729) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2730) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2731) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2732) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2733) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2734) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2735) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2736) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2737) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2738) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-d] - l.%d\n, [%-d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-d] - l.%d\n, [%-d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2739) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3d] - l.%d\n, [%-3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3d] - l.%d\n, [%-3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2740) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0d] - l.%d\n, [%-3.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.0d] - l.%d\n, [%-3.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2741) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2d] - l.%d\n, [%-3.2d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.2d] - l.%d\n, [%-3.2d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2742) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2743) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2744) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2745) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2746) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2747) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+d] - l.%d\n, [%+d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+d] - l.%d\n, [%+d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2748) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2749) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2750) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2751) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2752) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2753) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2754) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2755) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2756) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2757) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2758) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2759) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2760) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2761) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2762) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15d] - l.%d\n, [%+15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15d] - l.%d\n, [%+15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2763) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2764) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2765) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2766) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2767) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2768) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2769) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2770) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2771) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2772) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2773) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2774) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% d] - l.%d\n, [% d]", 0, -2, line);
  sprintf(str1, "- %d - [%% d] - l.%d\n, [% d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2775) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% d] - l.%d\n, [% d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% d] - l.%d\n, [% d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2776) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% d] - l.%d\n, [% d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% d] - l.%d\n, [% d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2777) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3d] - l.%d\n, [% 3d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3d] - l.%d\n, [% 3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2778) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2779) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2780) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", 0, -2, line);
  sprintf(str1, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2781) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MIN, -2, line);
  sprintf(str1, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2782) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MAX, -2, line);
  sprintf(str1, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2783) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2784) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2785) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2786) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2786_2) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2787) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2788) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2789) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2790) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2791) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15d] - l.%d\n, [% 15d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15d] - l.%d\n, [% 15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2792) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2793) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2794) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2795) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2796) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2797) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2798) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2799) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2800) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2801) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2802) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2803) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%hd] - l.%d\n, [%hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%hd] - l.%d\n, [%hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2804) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2805) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2806) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3hd] - l.%d\n, [%3hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%3hd] - l.%d\n, [%3hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2807) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2807_2) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2808) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2809) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2810) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2811) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2812) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2813) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2814) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2815) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2816) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2817) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2818) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2819) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2820) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15hd] - l.%d\n, [%15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%15hd] - l.%d\n, [%15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2821) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2822) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2823) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2824) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2825) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2826) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2827) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2828) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2829) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2830) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2831) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2832) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-hd] - l.%d\n, [%-hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-hd] - l.%d\n, [%-hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2833) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2834) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2835) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2836) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2837) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2838) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2839) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2840) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2841) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2842) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2843) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2844) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2845) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2846) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2847) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2848) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2849) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2850) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+hd] - l.%d\n, [%+hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+hd] - l.%d\n, [%+hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2851) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2852) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2853) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2854) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2855) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2856) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2857) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2858) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2859) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2860) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2861) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2862) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2863) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2864) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2865) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2866) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2867) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2868) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2869) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2870) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2871) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2872) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2873) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2874) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2875) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2876) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2877) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% hd] - l.%d\n, [% hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% hd] - l.%d\n, [% hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2878) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2879) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2880) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2881) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2882) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2883) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2884) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2885) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2886) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2887) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2888) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2889) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2890) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2891) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2892) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2893) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2894) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2895) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2896) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2897) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2898) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2899) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2900) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2901) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2902) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2903) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2904) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", 0, -2, line);
  sprintf(str1, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2905) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2906) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3013) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+d] - l.%d\n, [%-+d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+d] - l.%d\n, [%-+d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3014) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3015) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3016) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3017) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3018) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3019) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3020) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3021) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3021_2) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3022) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3023) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3024) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3025) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3026) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3027) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3028) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3029) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3030) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3031) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3032) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3033) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3034) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3035) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3036) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3037) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3038) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3039) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3040) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3041) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3072) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- d] - l.%d\n, [%- d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- d] - l.%d\n, [%- d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3073) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3074) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3075) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3076) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3077) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3078) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3079) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3080) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3081) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3082) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3083) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3084) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3085) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3086) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3087) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3088) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3089) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3090) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3091) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3092) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3093) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3094) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3095) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3096) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3097) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3098) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3099) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3100) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3101) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3132) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3133) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3134) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3135) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3136) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3137) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3138) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3139) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3140) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3141) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3142) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3143) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3144) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3145) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3146) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3147) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3148) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3149) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3150) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3151) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3152) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3153) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3154) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3155) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3156) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3157) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3158) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3159) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3160) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3161) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3192) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- hd] - l.%d\n, [%- hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- hd] - l.%d\n, [%- hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3193) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3194) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3195) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3196) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MIN, -2, line);
  sprintf(str1, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3197) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MAX, -2, line);
  sprintf(str1, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3198) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3199) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3200) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3201) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3202) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3203) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3204) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3205) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3206) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3207) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3208) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3209) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3210) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3211) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3212) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3213) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3214) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3215) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3216) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3217) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3218) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3219) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", 0, -2, line);
  sprintf(str1, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3220) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3221) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3373) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%s] - l.%d\n, [%s]", -2, line, str);
  sprintf(str1, "- %d - [%%s] - l.%d\n, [%s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3374) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%s] - l.%d\n, [%s]", -2, line, str);
  sprintf(str1, "- %d - [%%s] - l.%d\n, [%s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3375) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%3s] - l.%d\n, [%3s]", -2, line, str);
  sprintf(str1, "- %d - [%%3s] - l.%d\n, [%3s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3376) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%3s] - l.%d\n, [%3s]", -2, line, str);
  sprintf(str1, "- %d - [%%3s] - l.%d\n, [%3s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3377) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3378) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3379) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3380) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3381) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%3.5s] - l.%d\n, [%3.5s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.5s] - l.%d\n, [%3.5s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3382) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%3.5s] - l.%d\n, [%3.5s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.5s] - l.%d\n, [%3.5s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3383) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3384) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, line, str);
  sprintf(str1, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3385) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%25s] - l.%d\n, [%25s]", -2, line, str);
  sprintf(str1, "- %d - [%%25s] - l.%d\n, [%25s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3386) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%25s] - l.%d\n, [%25s]", -2, line, str);
  sprintf(str1, "- %d - [%%25s] - l.%d\n, [%25s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3387) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, line, str);
  sprintf(str1, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3388) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, line, str);
  sprintf(str1, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3389) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, line, str);
  sprintf(str1, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3390) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, line, str);
  sprintf(str1, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3391) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-s] - l.%d\n, [%-s]", -2, line, str);
  sprintf(str1, "- %d - [%%-s] - l.%d\n, [%-s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3392) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%-s] - l.%d\n, [%-s]", -2, line, str);
  sprintf(str1, "- %d - [%%-s] - l.%d\n, [%-s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3393) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3394) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3395) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3396) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3397) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-3.2s] - l.%d\n, [%-3.2s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.2s] - l.%d\n, [%-3.2s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3399) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-3.5s] - l.%d\n, [%-3.5s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.5s] - l.%d\n, [%-3.5s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3400) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%-3.5s] - l.%d\n, [%-3.5s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.5s] - l.%d\n, [%-3.5s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3401) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3402) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = NULL;
  s21_sprintf(str2, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, line, str);
  sprintf(str1, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, line, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3523) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%c] - l.%d\n, [%c]", -2, line, *str);
  sprintf(str1, "- %d - [%%c] - l.%d\n, [%c]", -2, line, *str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3525) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%3c] - l.%d\n, [%3c]", -2, line, *str);
  sprintf(str1, "- %d - [%%3c] - l.%d\n, [%3c]", -2, line, *str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3535) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%25c] - l.%d\n, [%25c]", -2, line, *str);
  sprintf(str1, "- %d - [%%25c] - l.%d\n, [%25c]", -2, line, *str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3554) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-c] - l.%d\n, [%-c]", -2, line, *str);
  sprintf(str1, "- %d - [%%-c] - l.%d\n, [%-c]", -2, line, *str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3555) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  char *str = "Hello World";
  s21_sprintf(str2, "- %d - [%%-3c] - l.%d\n, [%-3c]", -2, line, *str);
  sprintf(str1, "- %d - [%%-3c] - l.%d\n, [%-3c]", -2, line, *str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2708_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%i] - l.%d\n, [%i]", 0, -2, line);
  sprintf(str1, "- %d - [%%i] - l.%d\n, [%i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2709_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%i] - l.%d\n, [%i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%i] - l.%d\n, [%i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2710_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%i] - l.%d\n, [%i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%i] - l.%d\n, [%i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2711i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, line);
  sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2712i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2713i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2714i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2715i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2716i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2717i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2718i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2719i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2720i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2721i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2722i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2723i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2724i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2725i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2726i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15i] - l.%d\n, [%15i]", 0, -2, line);
  sprintf(str1, "- %d - [%%15i] - l.%d\n, [%15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2727i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2728i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2729i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2730i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2731i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2732i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2733i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2734i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2735i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2736i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2737i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2738i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-i] - l.%d\n, [%-i]", 0, -2, line);
  sprintf(str1, "- %d - [%%-i] - l.%d\n, [%-i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2739i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3i] - l.%d\n, [%-3i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3i] - l.%d\n, [%-3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2740i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0i] - l.%d\n, [%-3.0i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.0i] - l.%d\n, [%-3.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2741i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2i] - l.%d\n, [%-3.2i]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.2i] - l.%d\n, [%-3.2i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2742i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2743i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2744i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2745i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2746i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2747i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+i] - l.%d\n, [%+i]", 0, -2, line);
  sprintf(str1, "- %d - [%%+i] - l.%d\n, [%+i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2748i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2749i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2750_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2751_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2752_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2753_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2754_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2755_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2756_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2757_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2758_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2759_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2760_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2761_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2762_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15i] - l.%i\n, [%+15i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15i] - l.%i\n, [%+15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2763_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2764_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2765_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2766_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2767_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2768_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2769_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2770_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2771_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2772_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2773_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2774_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% i] - l.%i\n, [% i]", 0, -2, line);
  sprintf(str1, "- %i - [%% i] - l.%i\n, [% i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2775_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% i] - l.%i\n, [% i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% i] - l.%i\n, [% i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2776_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% i] - l.%i\n, [% i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% i] - l.%i\n, [% i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2777_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3i] - l.%i\n, [% 3i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3i] - l.%i\n, [% 3i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2778_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2779_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2780_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", 0, -2, line);
  sprintf(str1, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2781_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MIN, -2, line);
  sprintf(str1, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2782_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MAX, -2, line);
  sprintf(str1, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2783_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2784_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2785_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2786_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2786_2_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2787_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2788_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2789_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2790_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2791_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15i] - l.%i\n, [% 15i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 15i] - l.%i\n, [% 15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2792_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2793_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2794_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2795_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2796_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2800_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", 0, -2, line);
  sprintf(str1, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2802_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2803_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%hi] - l.%i\n, [%hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%hi] - l.%i\n, [%hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2804_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2805_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2806_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3hi] - l.%i\n, [%3hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%3hi] - l.%i\n, [%3hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2807_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2807_2_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2808_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2809_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2810_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2811_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2812_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2813_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2814_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2815_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2816_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2817_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2818_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2819_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2820_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15hi] - l.%i\n, [%15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%15hi] - l.%i\n, [%15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2821_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2822_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2823_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2824_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2825_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2826_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2827_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2828_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2829_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2830_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2831_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2832_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-hi] - l.%i\n, [%-hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-hi] - l.%i\n, [%-hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2833_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2834_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2835_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2836_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2837_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2838_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2839_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2840_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2841_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2842_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2843_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2844_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2845_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2846_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2847_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2848_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2849_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2850_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+hi] - l.%i\n, [%+hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+hi] - l.%i\n, [%+hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2851_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2852_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2853_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2854_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2855_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2856_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2857_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2858_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2859_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2860_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2861_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2862_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2863_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2864_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2865_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2866_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2867_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2868_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2869_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2870_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2871_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2872_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2873_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2874_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2875_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2876_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2877_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% hi] - l.%i\n, [% hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% hi] - l.%i\n, [% hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2878_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% hi] - l.%i\n, [% hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%% hi] - l.%i\n, [% hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2879_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% hi] - l.%i\n, [% hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%% hi] - l.%i\n, [% hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2880_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3hi] - l.%i\n, [% 3hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3hi] - l.%i\n, [% 3hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2881_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3hi] - l.%i\n, [% 3hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 3hi] - l.%i\n, [% 3hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2882_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3hi] - l.%i\n, [% 3hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 3hi] - l.%i\n, [% 3hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2883_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.0hi] - l.%i\n, [% 3.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.0hi] - l.%i\n, [% 3.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2884_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.0hi] - l.%i\n, [% 3.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%% 3.0hi] - l.%i\n, [% 3.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2885_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.0hi] - l.%i\n, [% 3.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 3.0hi] - l.%i\n, [% 3.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2886_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.2hi] - l.%i\n, [% 3.2hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.2hi] - l.%i\n, [% 3.2hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2887_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.2hi] - l.%i\n, [% 3.2hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%% 3.2hi] - l.%i\n, [% 3.2hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2888_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.2hi] - l.%i\n, [% 3.2hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 3.2hi] - l.%i\n, [% 3.2hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2889_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.5hi] - l.%i\n, [% 3.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.5hi] - l.%i\n, [% 3.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2890_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.5hi] - l.%i\n, [% 3.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%% 3.5hi] - l.%i\n, [% 3.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2891_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.5hi] - l.%i\n, [% 3.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 3.5hi] - l.%i\n, [% 3.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2892_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.15hi] - l.%i\n, [% 3.15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 3.15hi] - l.%i\n, [% 3.15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2893_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.15hi] - l.%i\n, [% 3.15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%% 3.15hi] - l.%i\n, [% 3.15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2894_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 3.15hi] - l.%i\n, [% 3.15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 3.15hi] - l.%i\n, [% 3.15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2895_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15hi] - l.%i\n, [% 15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 15hi] - l.%i\n, [% 15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2896_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15hi] - l.%i\n, [% 15hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%% 15hi] - l.%i\n, [% 15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2897_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15hi] - l.%i\n, [% 15hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%% 15hi] - l.%i\n, [% 15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2898_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2899_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2900_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2904_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", 0, -2, line);
  sprintf(str1, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2905_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2906_i) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3013) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+i] - l.%i\n, [%-+i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+i] - l.%i\n, [%-+i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3014) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3015) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3016) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3017) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3018) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3019) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3020) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3021) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3021_2) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3022) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3023) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3024) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3025) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3026) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3027) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3028) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3029) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3030) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3031) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3032) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3033) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3034) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3035) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3036) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3037) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3038) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3039) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3040) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3041) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3072) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- i] - l.%i\n, [%- i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- i] - l.%i\n, [%- i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3073) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3074) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3075) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3076) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3077) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3078) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3079) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3080) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3081) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3082) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3083) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3084) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3085) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3086) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3087) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3088) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3089) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3090) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3091) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3092) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3093) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3094) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3095) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3096) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3097) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3098) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3099) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3100) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3101) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3132) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3133) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3134) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3135) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3136) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3137) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3138) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3139) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3140) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3141) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3142) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3143) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3144) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3145) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3146) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3147) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3148) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3149) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3150) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3151) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3152) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3153) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.0hi] - l.%i\n, [%-+15.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15.0hi] - l.%i\n, [%-+15.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3154) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.0hi] - l.%i\n, [%-+15.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.0hi] - l.%i\n, [%-+15.0hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3155) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.0hi] - l.%i\n, [%-+15.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.0hi] - l.%i\n, [%-+15.0hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3156) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.5hi] - l.%i\n, [%-+15.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15.5hi] - l.%i\n, [%-+15.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3157) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.5hi] - l.%i\n, [%-+15.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.5hi] - l.%i\n, [%-+15.5hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3158) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.5hi] - l.%i\n, [%-+15.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.5hi] - l.%i\n, [%-+15.5hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3159) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.20hi] - l.%i\n, [%-+15.20hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%-+15.20hi] - l.%i\n, [%-+15.20hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3160) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.20hi] - l.%i\n, [%-+15.20hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.20hi] - l.%i\n, [%-+15.20hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3161) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%-+15.20hi] - l.%i\n, [%-+15.20hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%-+15.20hi] - l.%i\n, [%-+15.20hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3192) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- hi] - l.%i\n, [%- hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- hi] - l.%i\n, [%- hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3193) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- hi] - l.%i\n, [%- hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- hi] - l.%i\n, [%- hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3194) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- hi] - l.%i\n, [%- hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- hi] - l.%i\n, [%- hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3195) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3hi] - l.%i\n, [%- 3hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3hi] - l.%i\n, [%- 3hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3196) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3hi] - l.%i\n, [%- 3hi]", SHRT_MIN, -2, line);
  sprintf(str1, "- %i - [%%- 3hi] - l.%i\n, [%- 3hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3197) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3hi] - l.%i\n, [%- 3hi]", SHRT_MAX, -2, line);
  sprintf(str1, "- %i - [%%- 3hi] - l.%i\n, [%- 3hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3198) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.0hi] - l.%i\n, [%- 3.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.0hi] - l.%i\n, [%- 3.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3199) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.0hi] - l.%i\n, [%- 3.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.0hi] - l.%i\n, [%- 3.0hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3200) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.0hi] - l.%i\n, [%- 3.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.0hi] - l.%i\n, [%- 3.0hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3201) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.2hi] - l.%i\n, [%- 3.2hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.2hi] - l.%i\n, [%- 3.2hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3202) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.2hi] - l.%i\n, [%- 3.2hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.2hi] - l.%i\n, [%- 3.2hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3203) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.2hi] - l.%i\n, [%- 3.2hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.2hi] - l.%i\n, [%- 3.2hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3204) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.5hi] - l.%i\n, [%- 3.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.5hi] - l.%i\n, [%- 3.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3205) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.5hi] - l.%i\n, [%- 3.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.5hi] - l.%i\n, [%- 3.5hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3206) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.5hi] - l.%i\n, [%- 3.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.5hi] - l.%i\n, [%- 3.5hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3207) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.15hi] - l.%i\n, [%- 3.15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 3.15hi] - l.%i\n, [%- 3.15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3208) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.15hi] - l.%i\n, [%- 3.15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.15hi] - l.%i\n, [%- 3.15hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3209) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 3.15hi] - l.%i\n, [%- 3.15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 3.15hi] - l.%i\n, [%- 3.15hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3210) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15hi] - l.%i\n, [%- 15hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15hi] - l.%i\n, [%- 15hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3211) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15hi] - l.%i\n, [%- 15hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15hi] - l.%i\n, [%- 15hi]", SHRT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3212) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15hi] - l.%i\n, [%- 15hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15hi] - l.%i\n, [%- 15hi]", SHRT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3213) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.0hi] - l.%i\n, [%- 15.0hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15.0hi] - l.%i\n, [%- 15.0hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3214) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.0hi] - l.%i\n, [%- 15.0hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.0hi] - l.%i\n, [%- 15.0hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3215) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.0hi] - l.%i\n, [%- 15.0hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.0hi] - l.%i\n, [%- 15.0hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3216) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.5hi] - l.%i\n, [%- 15.5hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15.5hi] - l.%i\n, [%- 15.5hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3217) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.5hi] - l.%i\n, [%- 15.5hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.5hi] - l.%i\n, [%- 15.5hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3218) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.5hi] - l.%i\n, [%- 15.5hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.5hi] - l.%i\n, [%- 15.5hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3219) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.20hi] - l.%i\n, [%- 15.20hi]", 0, -2, line);
  sprintf(str1, "- %i - [%%- 15.20hi] - l.%i\n, [%- 15.20hi]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3220) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.20hi] - l.%i\n, [%- 15.20hi]", SHRT_MIN, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.20hi] - l.%i\n, [%- 15.20hi]", SHRT_MIN, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3221) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %i - [%%- 15.20hi] - l.%i\n, [%- 15.20hi]", SHRT_MAX, -2,
              line);
  sprintf(str1, "- %i - [%%- 15.20hi] - l.%i\n, [%- 15.20hi]", SHRT_MAX, -2,
          line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4001) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%u] - l.%d\n, [%u]", 0, -2, line);
  sprintf(str1, "- %d - [%%u] - l.%d\n, [%u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4002) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%u] - l.%d\n, [%u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%u] - l.%d\n, [%u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4004) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3u] - l.%d\n, [%3u]", 0, -2, line);
  sprintf(str1, "- %d - [%%3u] - l.%d\n, [%3u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4005) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3u] - l.%d\n, [%3u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3u] - l.%d\n, [%3u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4006) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3u] - l.%d\n, [%3u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3u] - l.%d\n, [%3u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4007) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0u] - l.%d\n, [%3.0u]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.0u] - l.%d\n, [%3.0u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4008) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0u] - l.%d\n, [%3.0u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.0u] - l.%d\n, [%3.0u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4009) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.0u] - l.%d\n, [%3.0u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.0u] - l.%d\n, [%3.0u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4010) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2u] - l.%d\n, [%3.2u]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.2u] - l.%d\n, [%3.2u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4011) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2u] - l.%d\n, [%3.2u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.2u] - l.%d\n, [%3.2u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4012) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.2u] - l.%d\n, [%3.2u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.2u] - l.%d\n, [%3.2u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4013) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5u] - l.%d\n, [%3.5u]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.5u] - l.%d\n, [%3.5u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4014) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5u] - l.%d\n, [%3.5u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.5u] - l.%d\n, [%3.5u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4015) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.5u] - l.%d\n, [%3.5u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.5u] - l.%d\n, [%3.5u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4016) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15u] - l.%d\n, [%3.15u]", 0, -2, line);
  sprintf(str1, "- %d - [%%3.15u] - l.%d\n, [%3.15u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4017) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15u] - l.%d\n, [%3.15u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%3.15u] - l.%d\n, [%3.15u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4018) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%3.15u] - l.%d\n, [%3.15u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%3.15u] - l.%d\n, [%3.15u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4019) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15u] - l.%d\n, [%15u]", 0, -2, line);
  sprintf(str1, "- %d - [%%15u] - l.%d\n, [%15u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4020) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15u] - l.%d\n, [%15u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15u] - l.%d\n, [%15u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4021) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15u] - l.%d\n, [%15u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15u] - l.%d\n, [%15u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4022) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0u] - l.%d\n, [%15.0u]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.0u] - l.%d\n, [%15.0u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4023) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.0u] - l.%d\n, [%15.0u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.0u] - l.%d\n, [%15.0u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4024) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.5u] - l.%d\n, [%15.5u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.5u] - l.%d\n, [%15.5u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4025) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20u] - l.%d\n, [%15.20u]", 0, -2, line);
  sprintf(str1, "- %d - [%%15.20u] - l.%d\n, [%15.20u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4026) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20u] - l.%d\n, [%15.20u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%15.20u] - l.%d\n, [%15.20u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4027) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%15.20u] - l.%d\n, [%15.20u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%15.20u] - l.%d\n, [%15.20u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4028) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-u] - l.%d\n, [%-u]", 0, -2, line);
  sprintf(str1, "- %d - [%%-u] - l.%d\n, [%-u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4029) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-u] - l.%d\n, [%-u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-u] - l.%d\n, [%-u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4030) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-u] - l.%d\n, [%-u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-u] - l.%d\n, [%-u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4031) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3u] - l.%d\n, [%-3u]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3u] - l.%d\n, [%-3u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4032) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3u] - l.%d\n, [%-3u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3u] - l.%d\n, [%-3u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4033) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3u] - l.%d\n, [%-3u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3u] - l.%d\n, [%-3u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4034) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0u] - l.%d\n, [%-3.0u]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.0u] - l.%d\n, [%-3.0u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4035) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0u] - l.%d\n, [%-3.0u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.0u] - l.%d\n, [%-3.0u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4036) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.0u] - l.%d\n, [%-3.0u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.0u] - l.%d\n, [%-3.0u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4037) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2u] - l.%d\n, [%-3.2u]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.2u] - l.%d\n, [%-3.2u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4038) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2u] - l.%d\n, [%-3.2u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.2u] - l.%d\n, [%-3.2u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4039) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.2u] - l.%d\n, [%-3.2u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.2u] - l.%d\n, [%-3.2u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4040) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5u] - l.%d\n, [%-3.5u]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.5u] - l.%d\n, [%-3.5u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4041) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5u] - l.%d\n, [%-3.5u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.5u] - l.%d\n, [%-3.5u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4042) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.5u] - l.%d\n, [%-3.5u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.5u] - l.%d\n, [%-3.5u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4043) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15u] - l.%d\n, [%-3.15u]", 0, -2, line);
  sprintf(str1, "- %d - [%%-3.15u] - l.%d\n, [%-3.15u]", 0, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4044) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15u] - l.%d\n, [%-3.15u]", INT_MIN, -2, line);
  sprintf(str1, "- %d - [%%-3.15u] - l.%d\n, [%-3.15u]", INT_MIN, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_4045) {
  int line = __LINE__;
  char str1[1024] = "";
  char str2[1024] = "";
  s21_sprintf(str2, "- %d - [%%-3.15u] - l.%d\n, [%-3.15u]", INT_MAX, -2, line);
  sprintf(str1, "- %d - [%%-3.15u] - l.%d\n, [%-3.15u]", INT_MAX, -2, line);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  int line = __LINE__;
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%+-25.3d%10.f|%15d", 252, 256.34, 15);
  int r2 = s21_sprintf(str2, "%+-25.3d%10.f|%15d", 252, 256.34, 15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  int line = __LINE__;
  char str1[1000];
  char str2[1000];
  int r1 =
      sprintf(str1, "str                      |%25.10s", "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "str                      |%25.10s",
                       "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  int line = __LINE__;
  char str1[1000];
  char str2[1000];
  //   void *p = (void *)43252342;
  int r1 = sprintf(str1, "%-15.20i%20u", 4567899, 43252342u);
  int r2 = s21_sprintf(str2, "%-15.20i%20u", 4567899, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);

  char str3[50];
  char str4[1000];
  int r3 = sprintf(str3, "%.0f", 25432.34345);
  int r4 = s21_sprintf(str4, "%.0f", 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
  int line = __LINE__;
  char str1[1000];
  char str2[1000];
  short h = 34;
  int r1 =
      sprintf(str1, "%-25.10d%-30.2d%10.12d%11d%d%.d%+-25.d%+10.2ld%-11.hd",
              253, 335, 1234, 34, 25, 345, 666, 456789l, h);
  int r2 =
      s21_sprintf(str2, "%-25.10d%-30.2d%10.12d%11d%d%.d%+-25.d%+10.2ld%-11.hd",
                  253, 335, 1234, 34, 25, 345, 666, 456789l, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
  int line = __LINE__;
  char str1[1000];
  char str2[1000];
  short h = 34;
  long l = 2353423523424;
  int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%12i%.i%-10.i%+10.1li%.25hi",
                   34567, 225, 5230, 125, 456, 377, l, h);
  int r2 = s21_sprintf(str2, "%+50.i%-10.20i%10.i%12i%.i%-10.i%+10.1li%.25hi",
                       34567, 225, 5230, 125, 456, 377, l, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  int line = __LINE__;
  char str1[1000];
  char str2[1000];
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 =
      sprintf(str1, "%u%15u%-20u%10u%-15.10u%20.u%.u%.10u%-20.12lu%19hu", 4321u,
              34567u, 2342u, 12346u, 234542u, 234523u, 2345u, 2432u, l, h);
  int r2 = s21_sprintf(
      str2, "%u%15u%-20u%10u%-15.10u%20.u%.u%.10u%-20.12lu%19hu", 4321u, 34567u,
      2342u, 12346u, 234542u, 234523u, 2345u, 2432u, l, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(printf_cTest) {
  int line = __LINE__;
  short length = 100;
  char *str1 = calloc(length, sizeof(char));
  char *str2 = calloc(length, sizeof(char));
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, "%c %c %c", ' ', '#', '@');
  res2 = sprintf(str2, "%c %c %c", ' ', '#', '@');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
  free(str1);
  free(str2);
}
END_TEST

START_TEST(printf_dTest) {
  int line = __LINE__;
  short length = 100;
  char *str1 = calloc(length, sizeof(char));
  char *str2 = calloc(length, sizeof(char));
  int res1 = 0, res2 = 0;
  long int n = 3;
  res1 = s21_sprintf(str1, "%ld%.5d  % d   %+d %d%-2.d", n, 3, 2, 46, -53, 9);
  res2 = sprintf(str2, "%ld%.5d  % d   %+d %d%-2.d", n, 3, 2, 46, -53, 9);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
  free(str1);
  free(str2);
}
END_TEST

START_TEST(printf_iTest) {
  int line = __LINE__;
  short length = 100;
  char *str1 = calloc(length, sizeof(char));
  char *str2 = calloc(length, sizeof(char));
  int res1 = 0, res2 = 0;
  short int n = 11;
  res1 = s21_sprintf(str1, "%hi %.5i %i", n, -46, 57);
  res2 = sprintf(str2, "%hi %.5i %i", n, -46, 57);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
  free(str1);
  free(str2);
}
END_TEST

START_TEST(printf_sTest) {
  int line = __LINE__;
  short length = 100;
  char *str1 = calloc(length, sizeof(char));
  char *str2 = calloc(length, sizeof(char));
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, "%.s %.3s %s", "Hello", " world", "!");
  res2 = sprintf(str2, "%.s %.3s %s", "Hello", " world", "!");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
  free(str1);
  free(str2);
}
END_TEST

START_TEST(printf_uTest) {
  int line = __LINE__;
  short length = 100;
  char *str1 = calloc(length, sizeof(char));
  char *str2 = calloc(length, sizeof(char));
  int res1 = 0, res2 = 0;
  unsigned short n = 2;
  unsigned long m = 33;
  res1 = s21_sprintf(str1, "%hu %lu %u", n, m, (unsigned)58432322);
  res2 = sprintf(str2, "%hu %lu %u", n, m, (unsigned)58432322);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
  free(str1);
  free(str2);
}
END_TEST

START_TEST(SPRINTF_FLOAT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_PREC) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%.5f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_H_PREC) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5.5f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_MINUS) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%-5f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_MINUS_DIGIT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%f";
  float f = -7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_SPACE) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "% f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_FLOAT_PLUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%+5f";
  float f = 7.891233;
  sprintf(result, format_str, f);
  s21_sprintf(result_s21, format_str, f);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%d";
  int d = 5;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_PREC) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5d";
  int d = 5;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_L) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%ld";
  long long d = LONG_MAX;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%hd";
  int d = INT_MAX;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_MINUS_DIGIT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%d";
  int d = -5;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_MINUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%-5d";
  int d = -5;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_PLUS_DIGIT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%+d";
  int d = 5;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_DECIMAL_SPACE) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "% d";
  int d = 5;
  sprintf(result, format_str, d);
  s21_sprintf(result_s21, format_str, d);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%u";
  unsigned int u = 5;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED_MINUS_DIGIT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%u";
  unsigned int u = -5;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED_LONG) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%lu";
  unsigned long int u = ULONG_MAX;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED_SHORT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%hu";
  unsigned long int u = USHRT_MAX;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5u";
  unsigned int u = 5;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED_MINUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%-5u";
  unsigned int u = 5;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_UNSIGNED_SPACE) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "% u";
  unsigned int u = 5;
  sprintf(result, format_str, u);
  s21_sprintf(result_s21, format_str, u);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_CHAR) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%c";
  char c = 'c';
  sprintf(result, format_str, c);
  s21_sprintf(result_s21, format_str, c);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_CHAR_DIGIT) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%c";
  int c = 48;
  sprintf(result, format_str, c);
  s21_sprintf(result_s21, format_str, c);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_CHAR_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5c";
  int c = 48;
  sprintf(result, format_str, c);
  s21_sprintf(result_s21, format_str, c);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_CHAR_MINUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%-5c";
  int c = 48;
  sprintf(result, format_str, c);
  s21_sprintf(result_s21, format_str, c);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_CHAR_SPACE) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "% c";
  int c = 48;
  sprintf(result, format_str, c);
  s21_sprintf(result_s21, format_str, c);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_STRING) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%s";
  char s[] = "ABOBA";
  sprintf(result, format_str, s);
  s21_sprintf(result_s21, format_str, s);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_STRING_SYMBOLS) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%s";
  char s[] = "A\nB\tO\vB\rA\0C";
  sprintf(result, format_str, s);
  s21_sprintf(result_s21, format_str, s);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_STRING_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5s";
  char s[] = "ABOBA";
  sprintf(result, format_str, s);
  s21_sprintf(result_s21, format_str, s);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_STRING_MINUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%-5s";
  char s[] = "ABOBA";
  sprintf(result, format_str, s);
  s21_sprintf(result_s21, format_str, s);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_STRING_SPACE) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "% s";
  char s[] = "ABOBA";
  sprintf(result, format_str, s);
  s21_sprintf(result_s21, format_str, s);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_DEC) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%i";
  int i = 5;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_OCTAL) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%i";
  int i = 05;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_HEX) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%i";
  int i = 0xF;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%5i";
  int i = 05;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_MINUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%-5i";
  int i = 05;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_PLUS) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%+i";
  int i = 05;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_PLUS_H) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "%+5i";
  int i = 05;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(SPRINTF_I_SPACE) {
  int line = __LINE__;
  char result[100] = "";
  char result_s21[100] = "";
  char format_str[100] = "% i";
  int i = 05;
  sprintf(result, format_str, i);
  s21_sprintf(result_s21, format_str, i);
  ck_assert_str_eq(result, result_s21);
}
END_TEST

START_TEST(s21_sprintf_d) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);
  int min = -2147483648;
  int max = 2147483647;

  int lib_res = sprintf(lib_test_str,
                        "|%d| |%d| |% d| |%+d| |%d| |%-5d| |%5d| |%+5d| |%5d| "
                        "|%20.15d| |%+.0d| |%5.15d|\n",
                        12, 0, 12, max, min, 12, 12, 12, -12, 12, 12, -12);
  int s21_res = s21_sprintf(s21_test_str,
                            "|%d| |%d| |% d| |%+d| |%d| |%-5d| |%5d| |%+5d| "
                            "|%5d| |%20.15d| |%+.0d| |%5.15d|\n",
                            12, 0, 12, max, min, 12, 12, 12, -12, 12, 12, -12);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_i) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  int lib_res =
      sprintf(lib_test_str, "|%i| |% i| |%+i| |%i| |%-5i| |%5i| |%+5i| |%5i|\n",
              12, 12, 12, -12, 12, 12, 12, -12);
  int s21_res = s21_sprintf(s21_test_str,
                            "|%i| |% i| |%+i| |%i| |%-5i| |%5i| |%+5i| |%5i|\n",
                            12, 12, 12, -12, 12, 12, 12, -12);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_star) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  int lib_res = sprintf(lib_test_str, "%.d\n", 5);
  int s21_res = s21_sprintf(s21_test_str, "%.d\n", 5);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_u) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);
  unsigned int u = 2147483647;
  unsigned int a = 0;
  unsigned int b = 102;
  unsigned int c = 12;
  unsigned int d = 120;
  unsigned int e = 1200;
  unsigned int f = 14895085;

  int lib_res = sprintf(
      lib_test_str,
      "|%u| |%u| |%u| |%-20u| |%u| |%7u| |%5u| |%.20u| |%-20.15u| |%u|\n", u, a,
      b, c, f, c, c, c, d, e);
  int s21_res = s21_sprintf(
      s21_test_str,
      "|%u| |%u| |%u| |%-20u| |%u| |%7u| |%5u| |%.20u| |%-20.15u| |%u|\n", u, a,
      b, c, f, c, c, c, d, e);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_f) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  int lib_res =
      sprintf(lib_test_str, "|%f| |% f| |%+f| |%f| |%-8f| |%8f| |%+8f| |%8f|\n",
              0.020, 0.020, 0.020, -0.020, 0.020, 0.020, 0.020, -0.020);
  int s21_res = s21_sprintf(
      s21_test_str, "|%f| |% f| |%+f| |%f| |%-8f| |%8f| |%+8f| |%8f|\n", 0.020,
      0.020, 0.020, -0.020, 0.020, 0.020, 0.020, -0.020);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_s) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  int lib_res = sprintf(lib_test_str, "|%20s| |%-20s| |%5.0s| |%.1s|\n", "Hi",
                        "My", "Hi", "My");
  int s21_res = s21_sprintf(s21_test_str, "|%20s| |%-20s| |%5.0s| |%.1s|\n",
                            "Hi", "My", "Hi", "My");

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_h) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  short i = 0;
  short a = 32767;
  unsigned short b = 65535;
  unsigned long c = 4294967295;
  int lib_res = sprintf(lib_test_str, "|%hi| |%hd| |%hu|", i, a, i);
  int s21_res = s21_sprintf(s21_test_str, "|%hi| |%hd| |%hu|", i, a, i);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_l) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);
  long i = LONG_MAX;
  long a = LONG_MIN;
  unsigned long b = 4294967295;
  int lib_res = sprintf(lib_test_str, "|%li| |%ld| |%lu|", i, a, b, b);
  int s21_res = s21_sprintf(s21_test_str, "|%li| |%ld| |%lu|", i, a, b);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_diu_whith_str) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  long number = 100000000;
  short number1 = 5;
  int lib_res = sprintf(
      lib_test_str, "%d Hello, %10u it's a great % hd, %-10i, %d, %+10d, %ld\n",
      0, 1, number1, 3, -4, 5, number);
  int s21_res = s21_sprintf(
      s21_test_str, "%d Hello, %10u it's a great % hd, %-10i, %d, %+10d, %ld\n",
      0, 1, number1, 3, -4, 5, number);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_cs) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 256);
  char *lib_test_str = (char *)malloc(sizeof(char) * 256);

  char *str0 = "User";
  char *str1 = "";
  int lib_res = sprintf(lib_test_str, "Hello, %-13s, i%c, %s a great day!",
                        str0, 't', str1);
  int s21_res = s21_sprintf(s21_test_str, "Hello, %-13s, i%c, %s a great day!",
                            str0, 't', str1);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_f_with_str) {
  int line = __LINE__;
  char *s21_test_str = (char *)malloc(sizeof(char) * 512);
  char *lib_test_str = (char *)malloc(sizeof(char) * 512);

  int lib_res = sprintf(lib_test_str,
                        "Hello%.10f, my %.2f, beautiful %+10.f,world %-5.3f",
                        0.2, 0.12345, 0.3, -0.23246);
  int s21_res = s21_sprintf(
      s21_test_str, "Hello%.10f, my %.2f, beautiful %+10.f,world %-5.3f", 0.2,
      0.12345, 0.3, -0.23246);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_f_star_width) {
  int line = __LINE__;
  char data[100];
  char data1[100];
  char *format = "01)SPRINTF : |%2.*f|\n";
  s21_sprintf(data, format, _i);
  sprintf(data1, format, 0);
  ck_assert_str_eq(data, data1);
}
END_TEST

void part1_tests(TCase *tc1_1) {
  int line = __LINE__;
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn22);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn23);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn24);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn25);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn26);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn27);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn28);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn30);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn31);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn32);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn33);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn34);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn37);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn38);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn39);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn40);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn41);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn42);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn43);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn44);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn45);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn47);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn48);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn49);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn50);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn51);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn52);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn53);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn54);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn55);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn56);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn57);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn58);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn59);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn60);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn61);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn62);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn63);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn64);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn65);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn66);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn67);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn68);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn69);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn70);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn71);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn72);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn73);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn74);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn88);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn89);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn90);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn91);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn92);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn93);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn94);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn95);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn96);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn97);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn98);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn99);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn100);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn101);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn102);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn103);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn104);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn105);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn106);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn107);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn108);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn109);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn110);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn111);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn112);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn113);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn114);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn116);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn155);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn156);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn157);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn158);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn159);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn160);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn161);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn162);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn163);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn164);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn165);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn166);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn167);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn168);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn169);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn170);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn172);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn173);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn174);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn175);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn176);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn177);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn183);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn184);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn185);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn186);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn187);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn189);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn190);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn191);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn192);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn193);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn194);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn195);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn196);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn198);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn199);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn200);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn201);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn202);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn203);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn204);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn205);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn206);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn207);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn208);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn209);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn210);
  tcase_add_test(tc1_1, SPRINTFTestLaslhyn211);
  tcase_add_test(tc1_1, SPRINTFTestdogletho6);
  tcase_add_test(tc1_1, SPRINTFTestdogletho54);
  tcase_add_test(tc1_1, SPRINTFTestdogletho55);
  tcase_add_test(tc1_1, SPRINTFTestdogletho68);
  tcase_add_test(tc1_1, SPRINTFTestdogletho69);
  tcase_add_test(tc1_1, SPRINTFTestdogletho127);
  tcase_add_test(tc1_1, SPRINTFTestdogletho128);
  tcase_add_test(tc1_1, SPRINTFTestdogletho129);
  tcase_add_test(tc1_1, SPRINTFTestdogletho130);
  tcase_add_test(tc1_1, SPRINTFTestdogletho131);
  tcase_add_test(tc1_1, SPRINTFTestdogletho187);
  tcase_add_test(tc1_1, SPRINTFTestdogletho190);
  tcase_add_test(tc1_1, SPRINTFTestdogletho197);
  tcase_add_test(tc1_1, SPRINTFTestdogletho198);
  tcase_add_test(tc1_1, SPRINTFTestdogletho232);
  tcase_add_test(tc1_1, SPRINTFTestdogletho233);
  tcase_add_test(tc1_1, SPRINTFTestdogletho234);
  tcase_add_test(tc1_1, SPRINTFTestdogletho235);
  tcase_add_test(tc1_1, SPRINTFTestdogletho236);
  tcase_add_test(tc1_1, SPRINTFTestdogletho237);
  tcase_add_test(tc1_1, SPRINTFTestdogletho239);
  tcase_add_test(tc1_1, SPRINTFTestdogletho259);
  tcase_add_test(tc1_1, SPRINTFTestdogletho261);
  tcase_add_test(tc1_1, SPRINTFTestdogletho282);
  tcase_add_test(tc1_1, SPRINTFTestdogletho283);
  tcase_add_test(tc1_1, SPRINTFTestRleonard1);
  tcase_add_test(tc1_1, SPRINTFTestRleonard3);
  tcase_add_test(tc1_1, SPRINTFTestRleonard6);
  tcase_add_test(tc1_1, SPRINTFTestRleonard7);
  tcase_add_test(tc1_1, SPRINTFTestRleonard9);
  tcase_add_test(tc1_1, SPRINTFTestRleonard12);
  tcase_add_test(tc1_1, SPRINTFTestRleonard13);

  tcase_add_test(tc1_1, simple_int);
  tcase_add_test(tc1_1, precise_int);
  tcase_add_test(tc1_1, width_int);
  tcase_add_test(tc1_1, minus_width_int);
  tcase_add_test(tc1_1, plus_width_int);
  tcase_add_test(tc1_1, padding_int);
  tcase_add_test(tc1_1, flags_long_int);
  tcase_add_test(tc1_1, flags_short_int);
  tcase_add_test(tc1_1, space_flag_int);
  tcase_add_test(tc1_1, unsigned_val);
  tcase_add_test(tc1_1, unsigned_val_width);
  tcase_add_test(tc1_1, unsigned_val_flags);
  tcase_add_test(tc1_1, unsigned_val_precision);
  tcase_add_test(tc1_1, unsigned_val_many_flags);
  tcase_add_test(tc1_1, unsigned_val_short);
  tcase_add_test(tc1_1, unsigned_val_long);
  tcase_add_test(tc1_1, unsigned_val_many);
  tcase_add_test(tc1_1, octal_short);
  tcase_add_test(tc1_1, unsigned_zero);
  tcase_add_test(tc1_1, one_char);
  tcase_add_test(tc1_1, one_precision);
  tcase_add_test(tc1_1, one_flags);
  tcase_add_test(tc1_1, one_width);
  tcase_add_test(tc1_1, one_many);
  tcase_add_test(tc1_1, one_many_flags);
  tcase_add_test(tc1_1, string);
  tcase_add_test(tc1_1, string_precision);
  tcase_add_test(tc1_1, string_width);
  tcase_add_test(tc1_1, string_flags);
  tcase_add_test(tc1_1, string_long);
  tcase_add_test(tc1_1, string_many);
  tcase_add_test(tc1_1, string_width_huge);
  tcase_add_test(tc1_1, float_flags);
  tcase_add_test(tc1_1, all_empty);
  tcase_add_test(tc1_1, empty_format_and_parameters);
  tcase_add_test(tc1_1, test_one_char);
  tcase_add_test(tc1_1, test_many_char);
  tcase_add_test(tc1_1, test_one_string);
  tcase_add_test(tc1_1, test_many_string);
  tcase_add_test(tc1_1, test_one_dec);
  tcase_add_test(tc1_1, test_many_dec);
  tcase_add_test(tc1_1, test_one_int);
  tcase_add_test(tc1_1, test_many_int);
  tcase_add_test(tc1_1, test_one_float);
  tcase_add_test(tc1_1, test_many_float);
  tcase_add_test(tc1_1, test_one_unsigned_dec);
  tcase_add_test(tc1_1, test_many_unsigned_dec);
  tcase_add_test(tc1_1, test_one_char_with_alignment_left);
  tcase_add_test(tc1_1, test_sprintf1);
  tcase_add_test(tc1_1, test_sprintf2);
  tcase_add_test(tc1_1, test_sprintf3);
  tcase_add_test(tc1_1, test_sprintf4);
  tcase_add_test(tc1_1, test_sprintf7);
  tcase_add_test(tc1_1, test_sprintf8);
  tcase_add_test(tc1_1, test_sprintf9);
  tcase_add_test(tc1_1, test_sprintf10);
  tcase_add_test(tc1_1, test_sprintf11);
  tcase_add_test(tc1_1, test_sprintf16);
  tcase_add_test(tc1_1, test_sprintf17);
  tcase_add_test(tc1_1, test_sprintf18);
  tcase_add_test(tc1_1, test_sprintf19);
  tcase_add_test(tc1_1, test_sprintf20);
  tcase_add_test(tc1_1, test_sprintf24);
  tcase_add_test(tc1_1, test_sprintf25);
  tcase_add_test(tc1_1, test_sprintf29);
  tcase_add_test(tc1_1, test_sprintf30);
}

void part2_tests(TCase *tc1_2) {
  int line = __LINE__;
  tcase_add_test(tc1_2, sprintf_pr_1);
  tcase_add_test(tc1_2, sprintf_pr_2);
  tcase_add_test(tc1_2, sprintf_c_1);
  tcase_add_test(tc1_2, sprintf_c_2);
  tcase_add_test(tc1_2, sprintf_c_3);
  tcase_add_test(tc1_2, sprintf_c_4);
  tcase_add_test(tc1_2, sprintf_c_5);
  tcase_add_test(tc1_2, sprintf_c_6);
  tcase_add_test(tc1_2, sprintf_c_7);
  tcase_add_test(tc1_2, sprintf_c_8);
  tcase_add_test(tc1_2, sprintf_c_9);
  tcase_add_test(tc1_2, sprintf_c_10);
  tcase_add_test(tc1_2, sprintf_d_1);
  tcase_add_test(tc1_2, sprintf_d_2);
  tcase_add_test(tc1_2, sprintf_d_3);
  tcase_add_test(tc1_2, sprintf_d_4);
  tcase_add_test(tc1_2, sprintf_d_5);
  tcase_add_test(tc1_2, sprintf_d_6);
  tcase_add_test(tc1_2, sprintf_d_7);
  tcase_add_test(tc1_2, sprintf_d_8);
  tcase_add_test(tc1_2, sprintf_d_9);
  tcase_add_test(tc1_2, sprintf_d_10);
  tcase_add_test(tc1_2, sprintf_d_11);
  tcase_add_test(tc1_2, sprintf_d_and_c_1);
  tcase_add_test(tc1_2, sprintf_1);
  tcase_add_test(tc1_2, sprintf_2);
  tcase_add_test(tc1_2, sprintf_3);
  tcase_add_test(tc1_2, sprintf_4);
  tcase_add_test(tc1_2, sprintf_5);
  tcase_add_test(tc1_2, sprintf_6);
  tcase_add_test(tc1_2, sprintf_7);
  tcase_add_test(tc1_2, sprintf_8);
  tcase_add_test(tc1_2, sprintf_9);
  tcase_add_test(tc1_2, sprintf_12);
  tcase_add_test(tc1_2, sprintf_16);
  tcase_add_test(tc1_2, sprintf_18);
  tcase_add_test(tc1_2, sprintf_19);
  tcase_add_test(tc1_2, sprintf_20);
  tcase_add_test(tc1_2, sprintf_21);
  tcase_add_test(tc1_2, sprintf_22);
  tcase_add_test(tc1_2, sprintf_23);
  tcase_add_test(tc1_2, sprintf_24);
  tcase_add_test(tc1_2, sprintf_25);
  tcase_add_test(tc1_2, sprintf_26);
  tcase_add_test(tc1_2, sprintf_27);
  tcase_add_test(tc1_2, sprintf_28);
  tcase_add_test(tc1_2, sprintf_30);
  tcase_add_test(tc1_2, sprintf_31);
  tcase_add_test(tc1_2, sprintf_32);
  tcase_add_test(tc1_2, sprintf_33);
  tcase_add_test(tc1_2, sprintf_34);
  tcase_add_test(tc1_2, sprintf_35);
  tcase_add_test(tc1_2, sprintf_36);
  tcase_add_test(tc1_2, sprintf_37);
  tcase_add_test(tc1_2, sprintf_38);
  tcase_add_test(tc1_2, sprintf_39);
  tcase_add_test(tc1_2, sprintf_40);
  tcase_add_test(tc1_2, sprintf_41);
  tcase_add_test(tc1_2, sprintf_42);
  tcase_add_test(tc1_2, sprintf_43);
  tcase_add_test(tc1_2, sprintf_44);
  tcase_add_test(tc1_2, int_sprintf_pr_1);
  tcase_add_test(tc1_2, int_sprintf_pr_2);
  tcase_add_test(tc1_2, int_sprintf_c_1);
  tcase_add_test(tc1_2, int_sprintf_c_2);
  tcase_add_test(tc1_2, int_sprintf_c_3);
  tcase_add_test(tc1_2, int_sprintf_c_4);
  tcase_add_test(tc1_2, int_sprintf_c_5);
  tcase_add_test(tc1_2, int_sprintf_c_6);
  tcase_add_test(tc1_2, int_sprintf_c_7);
  tcase_add_test(tc1_2, int_sprintf_c_8);
  tcase_add_test(tc1_2, int_sprintf_c_9);
  tcase_add_test(tc1_2, int_sprintf_c_10);
  tcase_add_test(tc1_2, int_sprintf_d_1);
  tcase_add_test(tc1_2, int_sprintf_d_2);
  tcase_add_test(tc1_2, int_sprintf_d_3);
  tcase_add_test(tc1_2, int_sprintf_d_4);
  tcase_add_test(tc1_2, int_sprintf_d_5);
  tcase_add_test(tc1_2, int_sprintf_d_6);
  tcase_add_test(tc1_2, int_sprintf_d_7);
  tcase_add_test(tc1_2, int_sprintf_d_8);
  tcase_add_test(tc1_2, int_sprintf_d_9);
  tcase_add_test(tc1_2, int_sprintf_d_10);
  tcase_add_test(tc1_2, int_sprintf_d_11);
  tcase_add_test(tc1_2, int_sprintf_d_and_c_1);
  tcase_add_test(tc1_2, int_sprintf_1);
  tcase_add_test(tc1_2, int_sprintf_2);
  tcase_add_test(tc1_2, int_sprintf_3);
  tcase_add_test(tc1_2, int_sprintf_4);
  tcase_add_test(tc1_2, int_sprintf_5);
  tcase_add_test(tc1_2, int_sprintf_6);
  tcase_add_test(tc1_2, int_sprintf_7);
  tcase_add_test(tc1_2, int_sprintf_8);
  tcase_add_test(tc1_2, int_sprintf_9);
  tcase_add_test(tc1_2, int_sprintf_11);
  tcase_add_test(tc1_2, int_sprintf_12);
  tcase_add_test(tc1_2, int_sprintf_13);
  tcase_add_test(tc1_2, int_sprintf_14);
  tcase_add_test(tc1_2, int_sprintf_15);
  tcase_add_test(tc1_2, int_sprintf_16);
  tcase_add_test(tc1_2, int_sprintf_17);
  tcase_add_test(tc1_2, int_sprintf_18);
  tcase_add_test(tc1_2, int_sprintf_19);
  tcase_add_test(tc1_2, int_sprintf_20);
  tcase_add_test(tc1_2, int_sprintf_21);
  tcase_add_test(tc1_2, int_sprintf_22);
  tcase_add_test(tc1_2, sprintf_221);
  tcase_add_test(tc1_2, sprintf_222);
  tcase_add_test(tc1_2, ssprintf_223);
  tcase_add_test(tc1_2, sprintf_224);
  tcase_add_test(tc1_2, sprintf_225);
  tcase_add_test(tc1_2, ssprintf_226);
  tcase_add_test(tc1_2, ssprintf_227);
  tcase_add_test(tc1_2, ssprintf_228);
  tcase_add_test(tc1_2, ssprintf_229);
  tcase_add_test(tc1_2, ssprintf_2210);
  tcase_add_test(tc1_2, ssprintf_2211);
  tcase_add_test(tc1_2, ssprintf_2212);
  tcase_add_test(tc1_2, ssprintf_2213);
  tcase_add_test(tc1_2, ssprintf_2214);
  tcase_add_test(tc1_2, sprintf_231);
  tcase_add_test(tc1_2, sprintf_232);
  tcase_add_test(tc1_2, sprintf_233);
  tcase_add_test(tc1_2, sprintf_234);
  tcase_add_test(tc1_2, sprintf_235);
  tcase_add_test(tc1_2, sprintf_236);
  tcase_add_test(tc1_2, sprintf_237);
  tcase_add_test(tc1_2, sprintf_238);
  tcase_add_test(tc1_2, sprintf_239);
  tcase_add_test(tc1_2, sprintf_2310);
  tcase_add_test(tc1_2, sprintf_2311);
  tcase_add_test(tc1_2, sprintf_2312);
  tcase_add_test(tc1_2, sprintf_2313);
  tcase_add_test(tc1_2, sprintf_2314);
  tcase_add_test(tc1_2, sprintf_2315);
  tcase_add_test(tc1_2, sprintf_2316);
  tcase_add_test(tc1_2, sprintf_2317);
  tcase_add_test(tc1_2, sprintf_2318);
  tcase_add_test(tc1_2, sprintf_2319);
  tcase_add_test(tc1_2, sprintf_2320);
  tcase_add_test(tc1_2, sprintf_2321);
  tcase_add_test(tc1_2, sprintf_2322);
  tcase_add_test(tc1_2, sprintf_2323);
  tcase_add_test(tc1_2, sprintf_2324);
  tcase_add_test(tc1_2, sprintf_2325);
  tcase_add_test(tc1_2, sprintf_2326);
  tcase_add_test(tc1_2, sprintf_2327);
  tcase_add_test(tc1_2, sprintf_2328);
  tcase_add_test(tc1_2, sprintf_2329);
  tcase_add_test(tc1_2, sprintf_2330);
  tcase_add_test(tc1_2, sprintf_2331);
  tcase_add_test(tc1_2, sprintf_2332);
  tcase_add_test(tc1_2, sprintf_2333);
  tcase_add_test(tc1_2, sprintf_2334);
  tcase_add_test(tc1_2, sprintf_2335);
  tcase_add_test(tc1_2, sprintf_2336);
  tcase_add_test(tc1_2, sprintf_2337);
  tcase_add_test(tc1_2, sprintf_2338);
  tcase_add_test(tc1_2, sprintf_2339);
  tcase_add_test(tc1_2, sprintf_2340);
  tcase_add_test(tc1_2, sprintf_2341);
  tcase_add_test(tc1_2, sprintf_2342);
  tcase_add_test(tc1_2, sprintf_2343);
  tcase_add_test(tc1_2, sprintf_2344);
  tcase_add_test(tc1_2, sprintf_2345);
  tcase_add_test(tc1_2, sprintf_2346);
  tcase_add_test(tc1_2, sprintf_2347);
  tcase_add_test(tc1_2, sprintf_2348);
  tcase_add_test(tc1_2, sprintf_2349);
  tcase_add_test(tc1_2, sprintf_2350);
  tcase_add_test(tc1_2, sprintf_2351);
  tcase_add_test(tc1_2, sprintf_2352);
  tcase_add_test(tc1_2, sprintf_2353);
  tcase_add_test(tc1_2, sprintf_2354);
  tcase_add_test(tc1_2, sprintf_2355);
  tcase_add_test(tc1_2, sprintf_2356);
  tcase_add_test(tc1_2, sprintf_2357);
  tcase_add_test(tc1_2, sprintf_2358);
  tcase_add_test(tc1_2, sprintf_2359);
  tcase_add_test(tc1_2, sprintf_2360);
  tcase_add_test(tc1_2, sprintf_2361);
  tcase_add_test(tc1_2, sprintf_2362);
  tcase_add_test(tc1_2, sprintf_2363);
  tcase_add_test(tc1_2, sprintf_2364);
  tcase_add_test(tc1_2, sprintf_2365);
  tcase_add_test(tc1_2, sprintf_2366);
  tcase_add_test(tc1_2, sprintf_2367);
  tcase_add_test(tc1_2, sprintf_2368);
  tcase_add_test(tc1_2, sprintf_2369);
  tcase_add_test(tc1_2, sprintf_2370);
  tcase_add_test(tc1_2, sprintf_2371);
  tcase_add_test(tc1_2, sprintf_2372);
  tcase_add_test(tc1_2, sprintf_2373);
  tcase_add_test(tc1_2, sprintf_2374);
  tcase_add_test(tc1_2, sprintf_2375);
  tcase_add_test(tc1_2, sprintf_2376);
  tcase_add_test(tc1_2, sprintf_2377);
  tcase_add_test(tc1_2, sprintf_2378);
  tcase_add_test(tc1_2, sprintf_2379);
  tcase_add_test(tc1_2, sprintf_2380);
  tcase_add_test(tc1_2, sprintf_2381);
  tcase_add_test(tc1_2, sprintf_2382);
  tcase_add_test(tc1_2, sprintf_2383);
  tcase_add_test(tc1_2, sprintf_2384);
  tcase_add_test(tc1_2, sprintf_2385);
  tcase_add_test(tc1_2, sprintf_2386);
  tcase_add_test(tc1_2, sprintf_2387);
  tcase_add_test(tc1_2, sprintf_2388);
  tcase_add_test(tc1_2, sprintf_2391);
  tcase_add_test(tc1_2, sprintf_2392);
  tcase_add_test(tc1_2, sprintf_2393);
  tcase_add_test(tc1_2, sprintf_2394);
  tcase_add_test(tc1_2, sprintf_2395);
  tcase_add_test(tc1_2, sprintf_2401);
  tcase_add_test(tc1_2, sprintf_2402);
  tcase_add_test(tc1_2, sprintf_2403);
  tcase_add_test(tc1_2, sprintf_2404);
  tcase_add_test(tc1_2, sprintf_2405);
  tcase_add_test(tc1_2, sprintf_070501);
  tcase_add_test(tc1_2, sprintf_070502);
  tcase_add_test(tc1_2, sprintf_070503);
  tcase_add_test(tc1_2, sprintf_070504);
  tcase_add_test(tc1_2, sprintf_070505);
  tcase_add_test(tc1_2, sprintf_070506);
  tcase_add_test(tc1_2, sprintf_070507);
  tcase_add_test(tc1_2, sprintf_070508);
  tcase_add_test(tc1_2, sprintf_070510);
  tcase_add_test(tc1_2, sprintf_070513);
  tcase_add_test(tc1_2, sprintf_2405x);
  tcase_add_test(tc1_2, sprintf_2408);
  tcase_add_test(tc1_2, sprintf_2409);
  tcase_add_test(tc1_2, sprintf_2410);
  tcase_add_test(tc1_2, sprintf_2411);
  tcase_add_test(tc1_2, sprintf_2412);
  tcase_add_test(tc1_2, sprintf_2413);
  tcase_add_test(tc1_2, sprintf_2414);
  tcase_add_test(tc1_2, sprintf_2415);
  tcase_add_test(tc1_2, sprintf_2416);
  tcase_add_test(tc1_2, sprintf_2417);
  tcase_add_test(tc1_2, sprintf_2418);
  tcase_add_test(tc1_2, sprintf_2419);
  tcase_add_test(tc1_2, sprintf_2420);
  tcase_add_test(tc1_2, sprintf_2421);
  tcase_add_test(tc1_2, sprintf_2423);
  tcase_add_test(tc1_2, sprintf_2427);
  tcase_add_test(tc1_2, sprintf_2428);
  tcase_add_test(tc1_2, sprintf_2429);
  tcase_add_test(tc1_2, sprintf_2431);
  tcase_add_test(tc1_2, sprintf_2433);
  tcase_add_test(tc1_2, sprintf_2434);
  tcase_add_test(tc1_2, sprintf_2436);
  tcase_add_test(tc1_2, sprintf_2708);
  tcase_add_test(tc1_2, sprintf_2709);
  tcase_add_test(tc1_2, sprintf_2710);
  tcase_add_test(tc1_2, sprintf_2711);
  tcase_add_test(tc1_2, sprintf_2712);
  tcase_add_test(tc1_2, sprintf_2713);
  tcase_add_test(tc1_2, sprintf_2714);
  tcase_add_test(tc1_2, sprintf_2715);
  tcase_add_test(tc1_2, sprintf_2716);
  tcase_add_test(tc1_2, sprintf_2717);
  tcase_add_test(tc1_2, sprintf_2718);
  tcase_add_test(tc1_2, sprintf_2719);
  tcase_add_test(tc1_2, sprintf_2720);
  tcase_add_test(tc1_2, sprintf_2721);
  tcase_add_test(tc1_2, sprintf_2722);
  tcase_add_test(tc1_2, sprintf_2723);
  tcase_add_test(tc1_2, sprintf_2724);
  tcase_add_test(tc1_2, sprintf_2725);
  tcase_add_test(tc1_2, sprintf_2726);
  tcase_add_test(tc1_2, sprintf_2727);
  tcase_add_test(tc1_2, sprintf_2728);
  tcase_add_test(tc1_2, sprintf_2729);
  tcase_add_test(tc1_2, sprintf_2730);
  tcase_add_test(tc1_2, sprintf_2731);
  tcase_add_test(tc1_2, sprintf_2732);
  tcase_add_test(tc1_2, sprintf_2733);
  tcase_add_test(tc1_2, sprintf_2734);
  tcase_add_test(tc1_2, sprintf_2735);
  tcase_add_test(tc1_2, sprintf_2736);
  tcase_add_test(tc1_2, sprintf_2737);
  tcase_add_test(tc1_2, sprintf_2738);
  tcase_add_test(tc1_2, sprintf_2739);
  tcase_add_test(tc1_2, sprintf_2740);
  tcase_add_test(tc1_2, sprintf_2741);
  tcase_add_test(tc1_2, sprintf_2742);
  tcase_add_test(tc1_2, sprintf_2743);
  tcase_add_test(tc1_2, sprintf_2744);
  tcase_add_test(tc1_2, sprintf_2745);
  tcase_add_test(tc1_2, sprintf_2746);
  tcase_add_test(tc1_2, sprintf_2747);
  tcase_add_test(tc1_2, sprintf_2748);
  tcase_add_test(tc1_2, sprintf_2749);
  tcase_add_test(tc1_2, sprintf_2750);
  tcase_add_test(tc1_2, sprintf_2751);
  tcase_add_test(tc1_2, sprintf_2752);
  tcase_add_test(tc1_2, sprintf_2753);
  tcase_add_test(tc1_2, sprintf_2754);
  tcase_add_test(tc1_2, sprintf_2755);
  tcase_add_test(tc1_2, sprintf_2756);
  tcase_add_test(tc1_2, sprintf_2757);
  tcase_add_test(tc1_2, sprintf_2758);
  tcase_add_test(tc1_2, sprintf_2759);
  tcase_add_test(tc1_2, sprintf_2760);
  tcase_add_test(tc1_2, sprintf_2761);
  tcase_add_test(tc1_2, sprintf_2762);
  tcase_add_test(tc1_2, sprintf_2763);
  tcase_add_test(tc1_2, sprintf_2764);
  tcase_add_test(tc1_2, sprintf_2765);
  tcase_add_test(tc1_2, sprintf_2766);
  tcase_add_test(tc1_2, sprintf_2767);
}

void part3_tests(TCase *tc1_3) {
  int line = __LINE__;
  tcase_add_test(tc1_3, SPRINTF_FLOAT);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_PREC);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_H);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_H_PREC);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_MINUS);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_MINUS_DIGIT);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_SPACE);
  tcase_add_test(tc1_3, SPRINTF_FLOAT_PLUS_H);

  tcase_add_test(tc1_3, SPRINTF_DECIMAL);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_PREC);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_L);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_H);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_MINUS_DIGIT);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_PLUS_DIGIT);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_MINUS_H);
  tcase_add_test(tc1_3, SPRINTF_DECIMAL_SPACE);

  tcase_add_test(tc1_3, SPRINTF_UNSIGNED);
  tcase_add_test(tc1_3, SPRINTF_UNSIGNED_MINUS_DIGIT);
  tcase_add_test(tc1_3, SPRINTF_UNSIGNED_LONG);
  tcase_add_test(tc1_3, SPRINTF_UNSIGNED_SHORT);
  tcase_add_test(tc1_3, SPRINTF_UNSIGNED_MINUS_H);
  tcase_add_test(tc1_3, SPRINTF_UNSIGNED_H);
  tcase_add_test(tc1_3, SPRINTF_UNSIGNED_SPACE);

  tcase_add_test(tc1_3, SPRINTF_CHAR);
  tcase_add_test(tc1_3, SPRINTF_CHAR_DIGIT);
  tcase_add_test(tc1_3, SPRINTF_CHAR_H);
  tcase_add_test(tc1_3, SPRINTF_CHAR_MINUS_H);
  tcase_add_test(tc1_3, SPRINTF_CHAR_SPACE);

  tcase_add_test(tc1_3, SPRINTF_STRING);
  tcase_add_test(tc1_3, SPRINTF_STRING_SYMBOLS);
  tcase_add_test(tc1_3, SPRINTF_STRING_MINUS_H);
  tcase_add_test(tc1_3, SPRINTF_STRING_H);
  tcase_add_test(tc1_3, SPRINTF_STRING_SPACE);

  tcase_add_test(tc1_3, SPRINTF_I_DEC);
  tcase_add_test(tc1_3, SPRINTF_I_OCTAL);
  tcase_add_test(tc1_3, SPRINTF_I_HEX);
  tcase_add_test(tc1_3, SPRINTF_I_H);
  tcase_add_test(tc1_3, SPRINTF_I_MINUS_H);
  tcase_add_test(tc1_3, SPRINTF_I_PLUS);
  tcase_add_test(tc1_3, SPRINTF_I_PLUS_H);
  tcase_add_test(tc1_3, SPRINTF_I_SPACE);

  tcase_add_test(tc1_3, s21_sprintf_d);
  tcase_add_test(tc1_3, s21_sprintf_u);
  tcase_add_test(tc1_3, s21_sprintf_cs);
  tcase_add_test(tc1_3, s21_sprintf_f);
  tcase_add_test(tc1_3, s21_sprintf_i);
  tcase_add_test(tc1_3, s21_sprintf_s);
  tcase_add_test(tc1_3, s21_sprintf_h);
  tcase_add_test(tc1_3, s21_sprintf_l);
  tcase_add_test(tc1_3, s21_sprintf_star);
  tcase_add_test(tc1_3, s21_sprintf_diu_whith_str);
  tcase_add_test(tc1_3, s21_sprintf_f_with_str);

  tcase_add_test(tc1_3, s21_memchr_test);
  tcase_add_test(tc1_3, s21_memcmp_test);
  tcase_add_test(tc1_3, s21_memcpy_test);
  tcase_add_test(tc1_3, s21_memmove_test);
  tcase_add_test(tc1_3, s21_memset_test);
  tcase_add_test(tc1_3, s21_strcat_test);
  tcase_add_test(tc1_3, s21_strncat_test);
  tcase_add_test(tc1_3, s21_strchr_test);
  tcase_add_test(tc1_3, s21_strcmp_test);
  tcase_add_test(tc1_3, s21_strncmp_test);
  tcase_add_test(tc1_3, s21_strcpy_test);
  tcase_add_test(tc1_3, s21_strncpy_test);
  tcase_add_test(tc1_3, s21_strcspn_test);
  tcase_add_test(tc1_3, s21_strerror_test);
  tcase_add_test(tc1_3, s21_strlen_test);
  tcase_add_test(tc1_3, s21_strpbrk_test);
  tcase_add_test(tc1_3, s21_strrchr_test);
  tcase_add_test(tc1_3, s21_strspn_test);
  tcase_add_test(tc1_3, s21_strstr_test);
  tcase_add_test(tc1_3, s21_strtok_test);
  tcase_add_test(tc1_3, s21_to_upper_test);
  tcase_add_test(tc1_3, s21_to_lower_test);
  tcase_add_test(tc1_3, s21_trim_test);
  tcase_add_test(tc1_3, s21_insert_test);
}

void part4_tests(TCase *tc1_4) {
  int line = __LINE__;
  tcase_add_test(tc1_4, sprintf_2768);
  tcase_add_test(tc1_4, sprintf_2769);
  tcase_add_test(tc1_4, sprintf_2770);
  tcase_add_test(tc1_4, sprintf_2771);
  tcase_add_test(tc1_4, sprintf_2772);
  tcase_add_test(tc1_4, sprintf_2773);
  tcase_add_test(tc1_4, sprintf_2774);
  tcase_add_test(tc1_4, sprintf_2775);
  tcase_add_test(tc1_4, sprintf_2776);
  tcase_add_test(tc1_4, sprintf_2777);
  tcase_add_test(tc1_4, sprintf_2778);
  tcase_add_test(tc1_4, sprintf_2779);
  tcase_add_test(tc1_4, sprintf_2780);
  tcase_add_test(tc1_4, sprintf_2781);
  tcase_add_test(tc1_4, sprintf_2782);
  tcase_add_test(tc1_4, sprintf_2783);
  tcase_add_test(tc1_4, sprintf_2784);
  tcase_add_test(tc1_4, sprintf_2785);
  tcase_add_test(tc1_4, sprintf_2786);
  tcase_add_test(tc1_4, sprintf_2786_2);
  tcase_add_test(tc1_4, sprintf_2787);
  tcase_add_test(tc1_4, sprintf_2788);
  tcase_add_test(tc1_4, sprintf_2789);
  tcase_add_test(tc1_4, sprintf_2790);
  tcase_add_test(tc1_4, sprintf_2791);
  tcase_add_test(tc1_4, sprintf_2792);
  tcase_add_test(tc1_4, sprintf_2793);
  tcase_add_test(tc1_4, sprintf_2794);
  tcase_add_test(tc1_4, sprintf_2795);
  tcase_add_test(tc1_4, sprintf_2796);
  tcase_add_test(tc1_4, sprintf_2797);
  tcase_add_test(tc1_4, sprintf_2798);
  tcase_add_test(tc1_4, sprintf_2799);
  tcase_add_test(tc1_4, sprintf_2800);
  tcase_add_test(tc1_4, sprintf_2801);
  tcase_add_test(tc1_4, sprintf_2802);
  tcase_add_test(tc1_4, sprintf_2803);
  tcase_add_test(tc1_4, sprintf_2804);
  tcase_add_test(tc1_4, sprintf_2805);
  tcase_add_test(tc1_4, sprintf_2806);
  tcase_add_test(tc1_4, sprintf_2807);
  tcase_add_test(tc1_4, sprintf_2807_2);
  tcase_add_test(tc1_4, sprintf_2808);
  tcase_add_test(tc1_4, sprintf_2809);
  tcase_add_test(tc1_4, sprintf_2810);
  tcase_add_test(tc1_4, sprintf_2811);
  tcase_add_test(tc1_4, sprintf_2812);
  tcase_add_test(tc1_4, sprintf_2813);
  tcase_add_test(tc1_4, sprintf_2814);
  tcase_add_test(tc1_4, sprintf_2815);
  tcase_add_test(tc1_4, sprintf_2816);
  tcase_add_test(tc1_4, sprintf_2817);
  tcase_add_test(tc1_4, sprintf_2818);
  tcase_add_test(tc1_4, sprintf_2819);
  tcase_add_test(tc1_4, sprintf_2820);
  tcase_add_test(tc1_4, sprintf_2821);
  tcase_add_test(tc1_4, sprintf_2822);
  tcase_add_test(tc1_4, sprintf_2823);
  tcase_add_test(tc1_4, sprintf_2824);
  tcase_add_test(tc1_4, sprintf_2825);
  tcase_add_test(tc1_4, sprintf_2826);
  tcase_add_test(tc1_4, sprintf_2827);
  tcase_add_test(tc1_4, sprintf_2828);
  tcase_add_test(tc1_4, sprintf_2829);
  tcase_add_test(tc1_4, sprintf_2830);
  tcase_add_test(tc1_4, sprintf_2831);
  tcase_add_test(tc1_4, sprintf_2832);
  tcase_add_test(tc1_4, sprintf_2833);
  tcase_add_test(tc1_4, sprintf_2834);
  tcase_add_test(tc1_4, sprintf_2835);
  tcase_add_test(tc1_4, sprintf_2836);
  tcase_add_test(tc1_4, sprintf_2837);
  tcase_add_test(tc1_4, sprintf_2838);
  tcase_add_test(tc1_4, sprintf_2839);
  tcase_add_test(tc1_4, sprintf_2840);
  tcase_add_test(tc1_4, sprintf_2841);
  tcase_add_test(tc1_4, sprintf_2842);
  tcase_add_test(tc1_4, sprintf_2843);
  tcase_add_test(tc1_4, sprintf_2844);
  tcase_add_test(tc1_4, sprintf_2845);
  tcase_add_test(tc1_4, sprintf_2846);
  tcase_add_test(tc1_4, sprintf_2847);
  tcase_add_test(tc1_4, sprintf_2848);
  tcase_add_test(tc1_4, sprintf_2849);
  tcase_add_test(tc1_4, sprintf_2850);
  tcase_add_test(tc1_4, sprintf_2851);
  tcase_add_test(tc1_4, sprintf_2852);
  tcase_add_test(tc1_4, sprintf_2853);
  tcase_add_test(tc1_4, sprintf_2854);
  tcase_add_test(tc1_4, sprintf_2855);
  tcase_add_test(tc1_4, sprintf_2856);
  tcase_add_test(tc1_4, sprintf_2857);
  tcase_add_test(tc1_4, sprintf_2858);
  tcase_add_test(tc1_4, sprintf_2859);
  tcase_add_test(tc1_4, sprintf_2860);
  tcase_add_test(tc1_4, sprintf_2861);
  tcase_add_test(tc1_4, sprintf_2862);
  tcase_add_test(tc1_4, sprintf_2863);
  tcase_add_test(tc1_4, sprintf_2864);
  tcase_add_test(tc1_4, sprintf_2865);
  tcase_add_test(tc1_4, sprintf_2866);
  tcase_add_test(tc1_4, sprintf_2867);
  tcase_add_test(tc1_4, sprintf_2868);
  tcase_add_test(tc1_4, sprintf_2869);
  tcase_add_test(tc1_4, sprintf_2870);
  tcase_add_test(tc1_4, sprintf_2871);
  tcase_add_test(tc1_4, sprintf_2872);
  tcase_add_test(tc1_4, sprintf_2873);
  tcase_add_test(tc1_4, sprintf_2874);
  tcase_add_test(tc1_4, sprintf_2875);
  tcase_add_test(tc1_4, sprintf_2876);
  tcase_add_test(tc1_4, sprintf_2877);
  tcase_add_test(tc1_4, sprintf_2878);
  tcase_add_test(tc1_4, sprintf_2879);
  tcase_add_test(tc1_4, sprintf_2880);
  tcase_add_test(tc1_4, sprintf_2881);
  tcase_add_test(tc1_4, sprintf_2882);
  tcase_add_test(tc1_4, sprintf_2883);
  tcase_add_test(tc1_4, sprintf_2884);
  tcase_add_test(tc1_4, sprintf_2885);
  tcase_add_test(tc1_4, sprintf_2886);
  tcase_add_test(tc1_4, sprintf_2887);
  tcase_add_test(tc1_4, sprintf_2888);
  tcase_add_test(tc1_4, sprintf_2889);
  tcase_add_test(tc1_4, sprintf_2890);
  tcase_add_test(tc1_4, sprintf_2891);
  tcase_add_test(tc1_4, sprintf_2892);
  tcase_add_test(tc1_4, sprintf_2893);
  tcase_add_test(tc1_4, sprintf_2894);
  tcase_add_test(tc1_4, sprintf_2895);
  tcase_add_test(tc1_4, sprintf_2896);
  tcase_add_test(tc1_4, sprintf_2897);
  tcase_add_test(tc1_4, sprintf_2898);
  tcase_add_test(tc1_4, sprintf_2899);
  tcase_add_test(tc1_4, sprintf_2900);
  tcase_add_test(tc1_4, sprintf_2901);
  tcase_add_test(tc1_4, sprintf_2902);
  tcase_add_test(tc1_4, sprintf_2903);
  tcase_add_test(tc1_4, sprintf_2904);
  tcase_add_test(tc1_4, sprintf_2905);
  tcase_add_test(tc1_4, sprintf_2906);
  tcase_add_test(tc1_4, sprintf_3013);
  tcase_add_test(tc1_4, sprintf_3014);
  tcase_add_test(tc1_4, sprintf_3015);
  tcase_add_test(tc1_4, sprintf_3016);
  tcase_add_test(tc1_4, sprintf_3017);
  tcase_add_test(tc1_4, sprintf_3018);
  tcase_add_test(tc1_4, sprintf_3019);
  tcase_add_test(tc1_4, sprintf_3020);
  tcase_add_test(tc1_4, sprintf_3021);
  tcase_add_test(tc1_4, sprintf_3021_2);
  tcase_add_test(tc1_4, sprintf_3022);
  tcase_add_test(tc1_4, sprintf_3023);
  tcase_add_test(tc1_4, sprintf_3024);
  tcase_add_test(tc1_4, sprintf_3025);
  tcase_add_test(tc1_4, sprintf_3026);
  tcase_add_test(tc1_4, sprintf_3027);
  tcase_add_test(tc1_4, sprintf_3028);
  tcase_add_test(tc1_4, sprintf_3029);
  tcase_add_test(tc1_4, sprintf_3030);
  tcase_add_test(tc1_4, sprintf_3031);
  tcase_add_test(tc1_4, sprintf_3032);
  tcase_add_test(tc1_4, sprintf_3033);
  tcase_add_test(tc1_4, sprintf_3034);
  tcase_add_test(tc1_4, sprintf_3035);
  tcase_add_test(tc1_4, sprintf_3036);
  tcase_add_test(tc1_4, sprintf_3037);
  tcase_add_test(tc1_4, sprintf_3038);
  tcase_add_test(tc1_4, sprintf_3039);
  tcase_add_test(tc1_4, sprintf_3040);
  tcase_add_test(tc1_4, sprintf_3041);
  tcase_add_test(tc1_4, sprintf_3072);
  tcase_add_test(tc1_4, sprintf_3073);
  tcase_add_test(tc1_4, sprintf_3074);
  tcase_add_test(tc1_4, sprintf_3075);
  tcase_add_test(tc1_4, sprintf_3076);
  tcase_add_test(tc1_4, sprintf_3077);
  tcase_add_test(tc1_4, sprintf_3078);
  tcase_add_test(tc1_4, sprintf_3079);
  tcase_add_test(tc1_4, sprintf_3080);
  tcase_add_test(tc1_4, sprintf_3081);
  tcase_add_test(tc1_4, sprintf_3082);
  tcase_add_test(tc1_4, sprintf_3083);
  tcase_add_test(tc1_4, sprintf_3084);
  tcase_add_test(tc1_4, sprintf_3085);
  tcase_add_test(tc1_4, sprintf_3086);
  tcase_add_test(tc1_4, sprintf_3087);
  tcase_add_test(tc1_4, sprintf_3088);
  tcase_add_test(tc1_4, sprintf_3089);
  tcase_add_test(tc1_4, sprintf_3090);
  tcase_add_test(tc1_4, sprintf_3091);
  tcase_add_test(tc1_4, sprintf_3092);
  tcase_add_test(tc1_4, sprintf_3093);
  tcase_add_test(tc1_4, sprintf_3094);
  tcase_add_test(tc1_4, sprintf_3095);
  tcase_add_test(tc1_4, sprintf_3096);
  tcase_add_test(tc1_4, sprintf_3097);
  tcase_add_test(tc1_4, sprintf_3098);
  tcase_add_test(tc1_4, sprintf_3099);
  tcase_add_test(tc1_4, sprintf_3100);
  tcase_add_test(tc1_4, sprintf_3101);
  tcase_add_test(tc1_4, sprintf_3132);
  tcase_add_test(tc1_4, sprintf_3133);
  tcase_add_test(tc1_4, sprintf_3134);
  tcase_add_test(tc1_4, sprintf_3135);
  tcase_add_test(tc1_4, sprintf_3136);
  tcase_add_test(tc1_4, sprintf_3137);
  tcase_add_test(tc1_4, sprintf_3138);
  tcase_add_test(tc1_4, sprintf_3139);
  tcase_add_test(tc1_4, sprintf_3140);
  tcase_add_test(tc1_4, sprintf_3141);
  tcase_add_test(tc1_4, sprintf_3142);
  tcase_add_test(tc1_4, sprintf_3143);
  tcase_add_test(tc1_4, sprintf_3144);
  tcase_add_test(tc1_4, sprintf_3145);
  tcase_add_test(tc1_4, sprintf_3146);
  tcase_add_test(tc1_4, sprintf_3147);
  tcase_add_test(tc1_4, sprintf_3148);
  tcase_add_test(tc1_4, sprintf_3149);
  tcase_add_test(tc1_4, sprintf_3150);
  tcase_add_test(tc1_4, sprintf_3151);
  tcase_add_test(tc1_4, sprintf_3152);
  tcase_add_test(tc1_4, sprintf_3153);
  tcase_add_test(tc1_4, sprintf_3154);
  tcase_add_test(tc1_4, sprintf_3155);
  tcase_add_test(tc1_4, sprintf_3156);
  tcase_add_test(tc1_4, sprintf_3157);
  tcase_add_test(tc1_4, sprintf_3158);
  tcase_add_test(tc1_4, sprintf_3159);
  tcase_add_test(tc1_4, sprintf_3160);
  tcase_add_test(tc1_4, sprintf_3161);
  tcase_add_test(tc1_4, sprintf_3192);
  tcase_add_test(tc1_4, sprintf_3193);
  tcase_add_test(tc1_4, sprintf_3194);
  tcase_add_test(tc1_4, sprintf_3195);
  tcase_add_test(tc1_4, sprintf_3196);
  tcase_add_test(tc1_4, sprintf_3197);
  tcase_add_test(tc1_4, sprintf_3198);
  tcase_add_test(tc1_4, sprintf_3199);
  tcase_add_test(tc1_4, sprintf_3200);
  tcase_add_test(tc1_4, sprintf_3201);
  tcase_add_test(tc1_4, sprintf_3202);
  tcase_add_test(tc1_4, sprintf_3203);
  tcase_add_test(tc1_4, sprintf_3204);
  tcase_add_test(tc1_4, sprintf_3205);
  tcase_add_test(tc1_4, sprintf_3206);
  tcase_add_test(tc1_4, sprintf_3207);
  tcase_add_test(tc1_4, sprintf_3208);
  tcase_add_test(tc1_4, sprintf_3209);
  tcase_add_test(tc1_4, sprintf_3210);
  tcase_add_test(tc1_4, sprintf_3211);
  tcase_add_test(tc1_4, sprintf_3212);
  tcase_add_test(tc1_4, sprintf_3213);
  tcase_add_test(tc1_4, sprintf_3214);
  tcase_add_test(tc1_4, sprintf_3215);
  tcase_add_test(tc1_4, sprintf_3216);
  tcase_add_test(tc1_4, sprintf_3217);
  tcase_add_test(tc1_4, sprintf_3218);
  tcase_add_test(tc1_4, sprintf_3219);
  tcase_add_test(tc1_4, sprintf_3220);
  tcase_add_test(tc1_4, sprintf_3221);
  tcase_add_test(tc1_4, sprintf_3373);
  tcase_add_test(tc1_4, sprintf_3374);
  tcase_add_test(tc1_4, sprintf_3375);
  tcase_add_test(tc1_4, sprintf_3376);
  tcase_add_test(tc1_4, sprintf_3377);
  tcase_add_test(tc1_4, sprintf_3378);
  tcase_add_test(tc1_4, sprintf_3379);
  tcase_add_test(tc1_4, sprintf_3380);
  tcase_add_test(tc1_4, sprintf_3381);
  tcase_add_test(tc1_4, sprintf_3382);
  tcase_add_test(tc1_4, sprintf_3383);
  tcase_add_test(tc1_4, sprintf_3384);
  tcase_add_test(tc1_4, sprintf_3385);
  tcase_add_test(tc1_4, sprintf_3386);
  tcase_add_test(tc1_4, sprintf_3387);
  tcase_add_test(tc1_4, sprintf_3388);
  tcase_add_test(tc1_4, sprintf_3389);
  tcase_add_test(tc1_4, sprintf_3390);
  tcase_add_test(tc1_4, sprintf_3391);
  tcase_add_test(tc1_4, sprintf_3392);
  tcase_add_test(tc1_4, sprintf_3393);
  tcase_add_test(tc1_4, sprintf_3394);
  tcase_add_test(tc1_4, sprintf_3395);
  tcase_add_test(tc1_4, sprintf_3396);
  tcase_add_test(tc1_4, sprintf_3397);
  tcase_add_test(tc1_4, sprintf_3399);
  tcase_add_test(tc1_4, sprintf_3400);
  tcase_add_test(tc1_4, sprintf_3401);
  tcase_add_test(tc1_4, sprintf_3402);
  tcase_add_test(tc1_4, sprintf_3523);
  tcase_add_test(tc1_4, sprintf_3525);
  tcase_add_test(tc1_4, sprintf_3535);
  tcase_add_test(tc1_4, sprintf_3554);
  tcase_add_test(tc1_4, sprintf_3555);
  tcase_add_test(tc1_4, sprintf_2708_i);
  tcase_add_test(tc1_4, sprintf_2709_i);
  tcase_add_test(tc1_4, sprintf_2710_i);
  tcase_add_test(tc1_4, sprintf_2711i);
  tcase_add_test(tc1_4, sprintf_2712i);
  tcase_add_test(tc1_4, sprintf_2713i);
  tcase_add_test(tc1_4, sprintf_2714i);
  tcase_add_test(tc1_4, sprintf_2715i);
  tcase_add_test(tc1_4, sprintf_2716i);
  tcase_add_test(tc1_4, sprintf_2717i);
  tcase_add_test(tc1_4, sprintf_2718i);
  tcase_add_test(tc1_4, sprintf_2719i);
  tcase_add_test(tc1_4, sprintf_2720i);
  tcase_add_test(tc1_4, sprintf_2721i);
  tcase_add_test(tc1_4, sprintf_2722i);
  tcase_add_test(tc1_4, sprintf_2723i);
  tcase_add_test(tc1_4, sprintf_2724i);
  tcase_add_test(tc1_4, sprintf_2725i);
  tcase_add_test(tc1_4, sprintf_2726i);
  tcase_add_test(tc1_4, sprintf_2727i);
  tcase_add_test(tc1_4, sprintf_2728i);
  tcase_add_test(tc1_4, sprintf_2729i);
  tcase_add_test(tc1_4, sprintf_2730i);
  tcase_add_test(tc1_4, sprintf_2731i);
  tcase_add_test(tc1_4, sprintf_2732i);
  tcase_add_test(tc1_4, sprintf_2733i);
  tcase_add_test(tc1_4, sprintf_2734i);
  tcase_add_test(tc1_4, sprintf_2735i);
  tcase_add_test(tc1_4, sprintf_2736i);
  tcase_add_test(tc1_4, sprintf_2737i);
  tcase_add_test(tc1_4, sprintf_2738i);
  tcase_add_test(tc1_4, sprintf_2739i);
  tcase_add_test(tc1_4, sprintf_2740i);
  tcase_add_test(tc1_4, sprintf_2741i);
  tcase_add_test(tc1_4, sprintf_2742i);
  tcase_add_test(tc1_4, sprintf_2743i);
  tcase_add_test(tc1_4, sprintf_2744i);
  tcase_add_test(tc1_4, sprintf_2745i);
  tcase_add_test(tc1_4, sprintf_2746i);
  tcase_add_test(tc1_4, sprintf_2747i);
  tcase_add_test(tc1_4, sprintf_2748i);
  tcase_add_test(tc1_4, sprintf_2749i);
  tcase_add_test(tc1_4, sprintf_i_2750_i);
  tcase_add_test(tc1_4, sprintf_i_2751_i);
  tcase_add_test(tc1_4, sprintf_i_2752_i);
  tcase_add_test(tc1_4, sprintf_i_2753_i);
  tcase_add_test(tc1_4, sprintf_i_2754_i);
  tcase_add_test(tc1_4, sprintf_i_2755_i);
  tcase_add_test(tc1_4, sprintf_i_2756_i);
  tcase_add_test(tc1_4, sprintf_i_2757_i);
  tcase_add_test(tc1_4, sprintf_i_2758_i);
  tcase_add_test(tc1_4, sprintf_i_2759_i);
  tcase_add_test(tc1_4, sprintf_i_2760_i);
  tcase_add_test(tc1_4, sprintf_i_2761_i);
  tcase_add_test(tc1_4, sprintf_i_2762_i);
  tcase_add_test(tc1_4, sprintf_i_2763_i);
  tcase_add_test(tc1_4, sprintf_i_2764_i);
  tcase_add_test(tc1_4, sprintf_i_2765_i);
  tcase_add_test(tc1_4, sprintf_i_2766_i);
  tcase_add_test(tc1_4, sprintf_i_2767_i);
  tcase_add_test(tc1_4, sprintf_i_2768_i);
  tcase_add_test(tc1_4, sprintf_i_2769_i);
  tcase_add_test(tc1_4, sprintf_i_2770_i);
  tcase_add_test(tc1_4, sprintf_i_2771_i);
  tcase_add_test(tc1_4, sprintf_i_2772_i);
  tcase_add_test(tc1_4, sprintf_i_2773_i);
  tcase_add_test(tc1_4, sprintf_i_2774_i);
  tcase_add_test(tc1_4, sprintf_i_2775_i);
  tcase_add_test(tc1_4, sprintf_i_2776_i);
  tcase_add_test(tc1_4, sprintf_i_2777_i);
  tcase_add_test(tc1_4, sprintf_i_2778_i);
  tcase_add_test(tc1_4, sprintf_i_2779_i);
  tcase_add_test(tc1_4, sprintf_i_2780_i);
  tcase_add_test(tc1_4, sprintf_i_2781_i);
  tcase_add_test(tc1_4, sprintf_i_2782_i);
  tcase_add_test(tc1_4, sprintf_i_2783_i);
  tcase_add_test(tc1_4, sprintf_i_2784_i);
  tcase_add_test(tc1_4, sprintf_i_2785_i);
}

void part5_tests(TCase *tc1_5) {
  int line = __LINE__;
  tcase_add_test(tc1_5, sprintf_i_2786_i);
  tcase_add_test(tc1_5, sprintf_i_2786_2_i);
  tcase_add_test(tc1_5, sprintf_i_2787_i);
  tcase_add_test(tc1_5, sprintf_i_2788_i);
  tcase_add_test(tc1_5, sprintf_i_2789_i);
  tcase_add_test(tc1_5, sprintf_i_2790_i);
  tcase_add_test(tc1_5, sprintf_i_2791_i);
  tcase_add_test(tc1_5, sprintf_i_2792_i);
  tcase_add_test(tc1_5, sprintf_i_2793_i);
  tcase_add_test(tc1_5, sprintf_i_2794_i);
  tcase_add_test(tc1_5, sprintf_i_2795_i);
  tcase_add_test(tc1_5, sprintf_i_2796_i);
  tcase_add_test(tc1_5, sprintf_i_2800_i);
  tcase_add_test(tc1_5, sprintf_i_2802_i);
  tcase_add_test(tc1_5, sprintf_i_2803_i);
  tcase_add_test(tc1_5, sprintf_i_2804_i);
  tcase_add_test(tc1_5, sprintf_i_2805_i);
  tcase_add_test(tc1_5, sprintf_i_2806_i);
  tcase_add_test(tc1_5, sprintf_i_2807_i);
  tcase_add_test(tc1_5, sprintf_i_2807_2_i);
  tcase_add_test(tc1_5, sprintf_i_2808_i);
  tcase_add_test(tc1_5, sprintf_i_2809_i);
  tcase_add_test(tc1_5, sprintf_i_2810_i);
  tcase_add_test(tc1_5, sprintf_i_2811_i);
  tcase_add_test(tc1_5, sprintf_i_2812_i);
  tcase_add_test(tc1_5, sprintf_i_2813_i);
  tcase_add_test(tc1_5, sprintf_i_2814_i);
  tcase_add_test(tc1_5, sprintf_i_2815_i);
  tcase_add_test(tc1_5, sprintf_i_2816_i);
  tcase_add_test(tc1_5, sprintf_i_2817_i);
  tcase_add_test(tc1_5, sprintf_i_2818_i);
  tcase_add_test(tc1_5, sprintf_i_2819_i);
  tcase_add_test(tc1_5, sprintf_i_2820_i);
  tcase_add_test(tc1_5, sprintf_i_2821_i);
  tcase_add_test(tc1_5, sprintf_i_2822_i);
  tcase_add_test(tc1_5, sprintf_i_2823_i);
  tcase_add_test(tc1_5, sprintf_i_2824_i);
  tcase_add_test(tc1_5, sprintf_i_2825_i);
  tcase_add_test(tc1_5, sprintf_i_2826_i);
  tcase_add_test(tc1_5, sprintf_i_2827_i);
  tcase_add_test(tc1_5, sprintf_i_2828_i);
  tcase_add_test(tc1_5, sprintf_i_2829_i);
  tcase_add_test(tc1_5, sprintf_i_2830_i);
  tcase_add_test(tc1_5, sprintf_i_2831_i);
  tcase_add_test(tc1_5, sprintf_i_2832_i);
  tcase_add_test(tc1_5, sprintf_i_2833_i);
  tcase_add_test(tc1_5, sprintf_i_2834_i);
  tcase_add_test(tc1_5, sprintf_i_2835_i);
  tcase_add_test(tc1_5, sprintf_i_2836_i);
  tcase_add_test(tc1_5, sprintf_i_2837_i);
  tcase_add_test(tc1_5, sprintf_i_2838_i);
  tcase_add_test(tc1_5, sprintf_i_2839_i);
  tcase_add_test(tc1_5, sprintf_i_2840_i);
  tcase_add_test(tc1_5, sprintf_i_2841_i);
  tcase_add_test(tc1_5, sprintf_i_2842_i);
  tcase_add_test(tc1_5, sprintf_i_2843_i);
  tcase_add_test(tc1_5, sprintf_i_2844_i);
  tcase_add_test(tc1_5, sprintf_i_2845_i);
  tcase_add_test(tc1_5, sprintf_i_2846_i);
  tcase_add_test(tc1_5, sprintf_i_2847_i);
  tcase_add_test(tc1_5, sprintf_i_2848_i);
  tcase_add_test(tc1_5, sprintf_i_2849_i);
  tcase_add_test(tc1_5, sprintf_i_2850_i);
  tcase_add_test(tc1_5, sprintf_i_2851_i);
  tcase_add_test(tc1_5, sprintf_i_2852_i);
  tcase_add_test(tc1_5, sprintf_i_2853_i);
  tcase_add_test(tc1_5, sprintf_i_2854_i);
  tcase_add_test(tc1_5, sprintf_i_2855_i);
  tcase_add_test(tc1_5, sprintf_i_2856_i);
  tcase_add_test(tc1_5, sprintf_i_2857_i);
  tcase_add_test(tc1_5, sprintf_i_2858_i);
  tcase_add_test(tc1_5, sprintf_i_2859_i);
  tcase_add_test(tc1_5, sprintf_i_2860_i);
  tcase_add_test(tc1_5, sprintf_i_2861_i);
  tcase_add_test(tc1_5, sprintf_i_2862_i);
  tcase_add_test(tc1_5, sprintf_i_2863_i);
  tcase_add_test(tc1_5, sprintf_i_2864_i);
  tcase_add_test(tc1_5, sprintf_i_2865_i);
  tcase_add_test(tc1_5, sprintf_i_2866_i);
  tcase_add_test(tc1_5, sprintf_i_2867_i);
  tcase_add_test(tc1_5, sprintf_i_2868_i);
  tcase_add_test(tc1_5, sprintf_i_2869_i);
  tcase_add_test(tc1_5, sprintf_i_2870_i);
  tcase_add_test(tc1_5, sprintf_i_2871_i);
  tcase_add_test(tc1_5, sprintf_i_2872_i);
  tcase_add_test(tc1_5, sprintf_i_2873_i);
  tcase_add_test(tc1_5, sprintf_i_2874_i);
  tcase_add_test(tc1_5, sprintf_i_2875_i);
  tcase_add_test(tc1_5, sprintf_i_2876_i);
  tcase_add_test(tc1_5, sprintf_i_2877_i);
  tcase_add_test(tc1_5, sprintf_i_2878_i);
  tcase_add_test(tc1_5, sprintf_i_2879_i);
  tcase_add_test(tc1_5, sprintf_i_2880_i);
  tcase_add_test(tc1_5, sprintf_i_2881_i);
  tcase_add_test(tc1_5, sprintf_i_2882_i);
  tcase_add_test(tc1_5, sprintf_i_2883_i);
  tcase_add_test(tc1_5, sprintf_i_2884_i);
  tcase_add_test(tc1_5, sprintf_i_2885_i);
  tcase_add_test(tc1_5, sprintf_i_2886_i);
  tcase_add_test(tc1_5, sprintf_i_2887_i);
  tcase_add_test(tc1_5, sprintf_i_2888_i);
  tcase_add_test(tc1_5, sprintf_i_2889_i);
  tcase_add_test(tc1_5, sprintf_i_2890_i);
  tcase_add_test(tc1_5, sprintf_i_2891_i);
  tcase_add_test(tc1_5, sprintf_i_2892_i);
  tcase_add_test(tc1_5, sprintf_i_2893_i);
  tcase_add_test(tc1_5, sprintf_i_2894_i);
  tcase_add_test(tc1_5, sprintf_i_2895_i);
  tcase_add_test(tc1_5, sprintf_i_2896_i);
  tcase_add_test(tc1_5, sprintf_i_2897_i);
  tcase_add_test(tc1_5, sprintf_i_2898_i);
  tcase_add_test(tc1_5, sprintf_i_2899_i);
  tcase_add_test(tc1_5, sprintf_i_2900_i);
  tcase_add_test(tc1_5, sprintf_i_2904_i);
  tcase_add_test(tc1_5, sprintf_i_2905_i);
  tcase_add_test(tc1_5, sprintf_i_2906_i);
  tcase_add_test(tc1_5, sprintf_i_3013);
  tcase_add_test(tc1_5, sprintf_i_3014);
  tcase_add_test(tc1_5, sprintf_i_3015);
  tcase_add_test(tc1_5, sprintf_i_3016);
  tcase_add_test(tc1_5, sprintf_i_3017);
  tcase_add_test(tc1_5, sprintf_i_3018);
  tcase_add_test(tc1_5, sprintf_i_3019);
  tcase_add_test(tc1_5, sprintf_i_3020);
  tcase_add_test(tc1_5, sprintf_i_3021);
  tcase_add_test(tc1_5, sprintf_i_3021_2);
  tcase_add_test(tc1_5, sprintf_i_3022);
  tcase_add_test(tc1_5, sprintf_i_3023);
  tcase_add_test(tc1_5, sprintf_i_3024);
  tcase_add_test(tc1_5, sprintf_i_3025);
  tcase_add_test(tc1_5, sprintf_i_3026);
  tcase_add_test(tc1_5, sprintf_i_3027);
  tcase_add_test(tc1_5, sprintf_i_3028);
  tcase_add_test(tc1_5, sprintf_i_3029);
  tcase_add_test(tc1_5, sprintf_i_3030);
  tcase_add_test(tc1_5, sprintf_i_3031);
  tcase_add_test(tc1_5, sprintf_i_3032);
  tcase_add_test(tc1_5, sprintf_i_3033);
  tcase_add_test(tc1_5, sprintf_i_3034);
  tcase_add_test(tc1_5, sprintf_i_3035);
  tcase_add_test(tc1_5, sprintf_i_3036);
  tcase_add_test(tc1_5, sprintf_i_3037);
  tcase_add_test(tc1_5, sprintf_i_3038);
  tcase_add_test(tc1_5, sprintf_i_3039);
  tcase_add_test(tc1_5, sprintf_i_3040);
  tcase_add_test(tc1_5, sprintf_i_3041);
  tcase_add_test(tc1_5, sprintf_i_3072);
  tcase_add_test(tc1_5, sprintf_i_3073);
  tcase_add_test(tc1_5, sprintf_i_3074);
  tcase_add_test(tc1_5, sprintf_i_3075);
  tcase_add_test(tc1_5, sprintf_i_3076);
  tcase_add_test(tc1_5, sprintf_i_3077);
  tcase_add_test(tc1_5, sprintf_i_3078);
  tcase_add_test(tc1_5, sprintf_i_3079);
  tcase_add_test(tc1_5, sprintf_i_3080);
  tcase_add_test(tc1_5, sprintf_i_3081);
  tcase_add_test(tc1_5, sprintf_i_3082);
  tcase_add_test(tc1_5, sprintf_i_3083);
  tcase_add_test(tc1_5, sprintf_i_3084);
  tcase_add_test(tc1_5, sprintf_i_3085);
  tcase_add_test(tc1_5, sprintf_i_3086);
  tcase_add_test(tc1_5, sprintf_i_3087);
  tcase_add_test(tc1_5, sprintf_i_3088);
  tcase_add_test(tc1_5, sprintf_i_3089);
  tcase_add_test(tc1_5, sprintf_i_3090);
  tcase_add_test(tc1_5, sprintf_i_3091);
  tcase_add_test(tc1_5, sprintf_i_3092);
  tcase_add_test(tc1_5, sprintf_i_3093);
  tcase_add_test(tc1_5, sprintf_i_3094);
  tcase_add_test(tc1_5, sprintf_i_3095);
  tcase_add_test(tc1_5, sprintf_i_3096);
  tcase_add_test(tc1_5, sprintf_i_3097);
  tcase_add_test(tc1_5, sprintf_i_3098);
  tcase_add_test(tc1_5, sprintf_i_3099);
  tcase_add_test(tc1_5, sprintf_i_3100);
  tcase_add_test(tc1_5, sprintf_i_3101);
  tcase_add_test(tc1_5, sprintf_i_3132);
  tcase_add_test(tc1_5, sprintf_i_3133);
  tcase_add_test(tc1_5, sprintf_i_3134);
  tcase_add_test(tc1_5, sprintf_i_3135);
  tcase_add_test(tc1_5, sprintf_i_3136);
  tcase_add_test(tc1_5, sprintf_i_3137);
  tcase_add_test(tc1_5, sprintf_i_3138);
  tcase_add_test(tc1_5, sprintf_i_3139);
  tcase_add_test(tc1_5, sprintf_i_3140);
  tcase_add_test(tc1_5, sprintf_i_3141);
  tcase_add_test(tc1_5, sprintf_i_3142);
  tcase_add_test(tc1_5, sprintf_i_3143);
  tcase_add_test(tc1_5, sprintf_i_3144);
  tcase_add_test(tc1_5, sprintf_i_3145);
  tcase_add_test(tc1_5, sprintf_i_3146);
  tcase_add_test(tc1_5, sprintf_i_3147);
  tcase_add_test(tc1_5, sprintf_i_3148);
  tcase_add_test(tc1_5, sprintf_i_3149);
  tcase_add_test(tc1_5, sprintf_i_3150);
  tcase_add_test(tc1_5, sprintf_i_3151);
  tcase_add_test(tc1_5, sprintf_i_3152);
  tcase_add_test(tc1_5, sprintf_i_3153);
  tcase_add_test(tc1_5, sprintf_i_3154);
  tcase_add_test(tc1_5, sprintf_i_3155);
  tcase_add_test(tc1_5, sprintf_i_3156);
  tcase_add_test(tc1_5, sprintf_i_3157);
  tcase_add_test(tc1_5, sprintf_i_3158);
  tcase_add_test(tc1_5, sprintf_i_3159);
  tcase_add_test(tc1_5, sprintf_i_3160);
  tcase_add_test(tc1_5, sprintf_i_3161);
  tcase_add_test(tc1_5, sprintf_i_3192);
  tcase_add_test(tc1_5, sprintf_i_3193);
  tcase_add_test(tc1_5, sprintf_i_3194);
  tcase_add_test(tc1_5, sprintf_i_3195);
  tcase_add_test(tc1_5, sprintf_i_3196);
  tcase_add_test(tc1_5, sprintf_i_3197);
  tcase_add_test(tc1_5, sprintf_i_3198);
  tcase_add_test(tc1_5, sprintf_i_3199);
  tcase_add_test(tc1_5, sprintf_i_3200);
  tcase_add_test(tc1_5, sprintf_i_3201);
  tcase_add_test(tc1_5, sprintf_i_3202);
  tcase_add_test(tc1_5, sprintf_i_3203);
  tcase_add_test(tc1_5, sprintf_i_3204);
  tcase_add_test(tc1_5, sprintf_i_3205);
  tcase_add_test(tc1_5, sprintf_i_3206);
  tcase_add_test(tc1_5, sprintf_i_3207);
  tcase_add_test(tc1_5, sprintf_i_3208);
  tcase_add_test(tc1_5, sprintf_i_3209);
  tcase_add_test(tc1_5, sprintf_i_3210);
  tcase_add_test(tc1_5, sprintf_i_3211);
  tcase_add_test(tc1_5, sprintf_i_3212);
  tcase_add_test(tc1_5, sprintf_i_3213);
  tcase_add_test(tc1_5, sprintf_i_3214);
  tcase_add_test(tc1_5, sprintf_i_3215);
  tcase_add_test(tc1_5, sprintf_i_3216);
  tcase_add_test(tc1_5, sprintf_i_3217);
  tcase_add_test(tc1_5, sprintf_i_3218);
  tcase_add_test(tc1_5, sprintf_i_3219);
  tcase_add_test(tc1_5, sprintf_i_3220);
  tcase_add_test(tc1_5, sprintf_i_3221);
  tcase_add_test(tc1_5, sprintf_i_4001);
  tcase_add_test(tc1_5, sprintf_i_4002);
  tcase_add_test(tc1_5, sprintf_i_4004);
  tcase_add_test(tc1_5, sprintf_i_4005);
  tcase_add_test(tc1_5, sprintf_i_4006);
  tcase_add_test(tc1_5, sprintf_i_4007);
  tcase_add_test(tc1_5, sprintf_i_4008);
  tcase_add_test(tc1_5, sprintf_i_4009);
  tcase_add_test(tc1_5, sprintf_i_4010);
  tcase_add_test(tc1_5, sprintf_i_4011);
  tcase_add_test(tc1_5, sprintf_i_4012);
  tcase_add_test(tc1_5, sprintf_i_4013);
  tcase_add_test(tc1_5, sprintf_i_4014);
  tcase_add_test(tc1_5, sprintf_i_4015);
  tcase_add_test(tc1_5, sprintf_i_4016);
  tcase_add_test(tc1_5, sprintf_i_4017);
  tcase_add_test(tc1_5, sprintf_i_4018);
  tcase_add_test(tc1_5, sprintf_i_4019);
  tcase_add_test(tc1_5, sprintf_i_4020);
  tcase_add_test(tc1_5, sprintf_i_4021);
  tcase_add_test(tc1_5, sprintf_i_4022);
  tcase_add_test(tc1_5, sprintf_i_4023);
  tcase_add_test(tc1_5, sprintf_i_4024);
  tcase_add_test(tc1_5, sprintf_i_4025);
  tcase_add_test(tc1_5, sprintf_i_4026);
  tcase_add_test(tc1_5, sprintf_i_4027);
  tcase_add_test(tc1_5, sprintf_i_4028);
  tcase_add_test(tc1_5, sprintf_i_4029);
  tcase_add_test(tc1_5, sprintf_i_4030);
  tcase_add_test(tc1_5, sprintf_i_4031);
  tcase_add_test(tc1_5, sprintf_i_4032);
  tcase_add_test(tc1_5, sprintf_i_4033);
  tcase_add_test(tc1_5, sprintf_i_4034);
  tcase_add_test(tc1_5, sprintf_i_4035);
  tcase_add_test(tc1_5, sprintf_i_4036);
  tcase_add_test(tc1_5, sprintf_i_4037);
  tcase_add_test(tc1_5, sprintf_i_4038);
  tcase_add_test(tc1_5, sprintf_i_4039);
  tcase_add_test(tc1_5, sprintf_i_4040);
  tcase_add_test(tc1_5, sprintf_i_4041);
  tcase_add_test(tc1_5, sprintf_i_4042);
  tcase_add_test(tc1_5, sprintf_i_4043);
  tcase_add_test(tc1_5, sprintf_i_4044);
  tcase_add_test(tc1_5, sprintf_i_4045);
  tcase_add_test(tc1_5, s21_sprintf_test2);
  tcase_add_test(tc1_5, s21_sprintf_test3);
  tcase_add_test(tc1_5, s21_sprintf_test4);
  tcase_add_test(tc1_5, s21_sprintf_test_d);
  tcase_add_test(tc1_5, s21_sprintf_test_i);
  tcase_add_test(tc1_5, s21_sprintf_test_u);
  tcase_add_test(tc1_5, printf_cTest);
  tcase_add_test(tc1_5, printf_dTest);
  tcase_add_test(tc1_5, printf_iTest);
  tcase_add_test(tc1_5, printf_sTest);
  tcase_add_test(tc1_5, printf_uTest);
}

void part_6_tests(TCase *tc1_6) {
  fill_double_array(512, 0.00025, -10);
  tcase_add_loop_test(tc1_6, s21_sprintf_f_star_width, 0, 512);
}

// fill_long_double_array
int main(void) {
  int line = __LINE__;
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  TCase *tc1_2 = tcase_create("Core");
  TCase *tc1_3 = tcase_create("Core");
  TCase *tc1_4 = tcase_create("Core");
  TCase *tc1_5 = tcase_create("Core");
  TCase *tc1_6 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);
  part1_tests(tc1_1);
  part2_tests(tc1_2);
  part3_tests(tc1_3);
  part2_tests(tc1_4);
  part2_tests(tc1_5);
  part2_tests(tc1_6);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
