#include <check.h>

#include "SmartCalculator/s21_calculator.h"
#include "SmartCalculator/s21_credit_calculator.h"
#include "SmartCalculator/s21_deposit_calculator.h"

START_TEST(test_1) {
  Data result = {0};
  char test_str[] = "6-5^3+8*3/5+4";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, -110.2);
}
END_TEST

START_TEST(test_01) {
  Data result = {0};
  char test_str[] = ")(";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_02) {
  Data result = {0};
  char test_str[] = "sin()";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_03) {
  int result = 0;
  char test_str[] = "(.)";
  Node test_node;
  Init(&test_node);

  result = Parcer(test_str, &test_node);
  Destroy(&test_node);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_04) {
  Data result = {0};
  char test_str[] = "()";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_05) {
  Data result = {0};
  char test_str[] = "(..)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_06) {
  Data result = {0};
  char test_str[] = "1234134.000000+1234";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
}
END_TEST

START_TEST(test_07) {
  Data result = {0};
  char test_str[] = "1234134.0000001*1234";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
}
END_TEST

START_TEST(test_08) {
  Data result = {0};
  char test_str[] = "*";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_09) {
  Data result = {0};
  char test_str[] = "/";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_010) {
  Data result = {0};
  char test_str[] = "+";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_011) {
  Data result = {0};
  char test_str[] = "mod";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_012) {
  Data result = {0};
  char test_str[] = "-";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_013) {
  Data result = {0};
  char test_str[] = "*1";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_014) {
  Data result = {0};
  char test_str[] = "/1";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_015) {
  Data result = {0};
  char test_str[] = "1+";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_016) {
  Data result = {0};
  char test_str[] = "1mod";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_017) {
  Data result = {0};
  char test_str[] = "1-";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST
START_TEST(test_2) {
  Data result = {0};
  char test_str[] = "2^(2^(2^2))";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 65536);
}
END_TEST

START_TEST(test_3) {
  Data result = {0};
  char test_str[] = "5+5*5-5";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 25);
}
END_TEST

START_TEST(test_4) {
  Data result = {0};
  char test_str[] = "(16.343+3.53)*2";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 39.746);
}
END_TEST

START_TEST(test_5) {
  Data result = {0};
  char test_str[] = "1*2+3^4-5/6";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 82.16666666666667);
}
END_TEST

START_TEST(test_6) {
  Data result = {0};
  char test_str[] = "15-5-15+(-5)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, -10);
}
END_TEST

START_TEST(test_7) {
  Data result = {0};
  char test_str[] = "log(1)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 0);
}
END_TEST

START_TEST(test_8) {
  Data result = {0};
  char test_str[] = "sqrt(21)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 4.58257569495584);
}
END_TEST

START_TEST(test_9) {
  Data result = {0};
  char test_str[] = "cos(cos(50))";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 0.569444802225201);
}
END_TEST

START_TEST(test_10) {
  Data result = {0};
  char test_str[] = "10mod9";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 1);
}
END_TEST

START_TEST(test_11) {
  Data result = {0};
  char test_str[] = "5...5+*/1";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 2);
}
END_TEST

START_TEST(test_12) {
  Data result = {0};
  char test_str[] = "sin(360)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 0.9589157234143065);
}
END_TEST

START_TEST(test_13) {
  Data result = {0};
  char test_str[] = "ln(10)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 2.302585092994046);
}
END_TEST

START_TEST(test_14) {
  Data result = {0};
  char test_str[] = "tan(3.1415/2)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 21585.8;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_15) {
  Data result = {0};
  char test_str[] = "tan(3.1415926)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 0;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_16) {
  Data result = {0};
  char test_str[] = "sin(3.1415926/2)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 1;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_17) {
  Data result = {0};
  char test_str[] = "1+1";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  ck_assert_double_eq(result.value, 2);
}
END_TEST

START_TEST(test_18) {
  Data result = {0};
  char test_str[] = "((sin(3.1415926/2)*123)/123)/(14*12)*(14*12)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 1;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_19) {
  Data result = {0};
  char test_str[] = "asin(0)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 0;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_20) {
  Data result = {0};
  char test_str[] = "acos(1)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 0;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_21) {
  Data result = {0};
  char test_str[] = "atan(1)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 0);
  double err = result.value - 0.7853981630;
  ck_assert_int_eq(1, (err < 1e-6));
}
END_TEST

START_TEST(test_22) {
  Data result = {0};
  char test_str[] = "atan(.)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_022) {
  Data result = {0};
  char test_str[] = "atan(.0)";

  result = Begin(test_str);
  ck_assert_int_eq(result.err, 1);
}
END_TEST

START_TEST(test_23) {
  credit_data result = {0};
  result = credit_calculator_anuitet(1000, 1, 10, 1);
  double err1 = result.total_sum - 1100;
  double err2 = result.overpay - 100;
  ck_assert_int_eq(1, (err1 <= 1));
  ck_assert_int_eq(1, (err2 <= 1));
}
END_TEST

START_TEST(test_24) {
  credit_data result = {0};
  result = credit_calculator_differ(1000, 1, 10, 1);
  double err1 = result.total_sum - 1100;
  double err2 = result.overpay - 100;
  ck_assert_int_eq(1, (err1 <= 1));
  ck_assert_int_eq(1, (err2 <= 1));
}
END_TEST

START_TEST(test_25) {
  deposit_data result = {0};
  result = deposit_calculator_mounth(1000, 1, 10, 1, 0);
  double err1 = result.total_sum - 1100;
  double err2 = result.profit - 100;
  ck_assert_int_eq(1, (err1 <= 1));
  ck_assert_int_eq(1, (err2 <= 1));
}
END_TEST

START_TEST(test_26) {
  deposit_data result = {0};
  result = deposit_calculator_mounth(1000, 1, 10, 1, 1);
  double err1 = result.total_sum - 1105;
  double err2 = result.profit - 105;
  ck_assert_int_eq(1, (err1 <= 1));
  ck_assert_int_eq(1, (err2 <= 1));
}
END_TEST

START_TEST(test_27) {
  deposit_data result = {0};
  result = deposit_calculator_quartal(1000, 1, 10, 1, 0);
  double err1 = result.total_sum - 1100;
  double err2 = result.profit - 100;
  ck_assert_int_eq(1, (err1 <= 1));
  ck_assert_int_eq(1, (err2 <= 1));
}
END_TEST

START_TEST(test_28) {
  deposit_data result = {0};
  result = deposit_calculator_quartal(1000, 1, 10, 1, 1);
  double err1 = result.total_sum - 1104;
  double err2 = result.profit - 104;
  ck_assert_int_eq(1, (err1 <= 1));
  ck_assert_int_eq(1, (err2 <= 1));
}
END_TEST

START_TEST(test_29) {
  int answer = is_correct("1+1*2-3-3-(-3)");
  ck_assert_int_eq(0, answer);
}
END_TEST

START_TEST(test_30) {
  int answer = is_correct("sin(1.0)+1*2-3-3-(-3)");
  ck_assert_int_eq(0, answer);
}
END_TEST

START_TEST(test_31) {
  int answer = is_correct("sin(1.0)+1*2-3-3-(-3)");
  ck_assert_int_eq(0, answer);
}
END_TEST

START_TEST(test_32) {
  int answer = is_correct("sin(2.2)");
  ck_assert_int_eq(0, answer);
}
END_TEST

START_TEST(test_33) {
  int answer = is_correct("sin(2)");
  ck_assert_int_eq(0, answer);
}
END_TEST

START_TEST(test_34) {
  Node stack;
  Init(&stack);
  char test_str[] = "acos(1)";
  Parcer(test_str, &stack);
  Print(&stack);
  Destroy(&stack);
}
END_TEST
char *str = "";

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_7);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);

  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_20);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);

  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);
  tcase_add_test(tc1_1, test_26);
  tcase_add_test(tc1_1, test_27);
  tcase_add_test(tc1_1, test_28);

  tcase_add_test(tc1_1, test_29);
  tcase_add_test(tc1_1, test_30);
  tcase_add_test(tc1_1, test_31);
  tcase_add_test(tc1_1, test_32);
  tcase_add_test(tc1_1, test_33);
  tcase_add_test(tc1_1, test_34);

  tcase_add_test(tc1_1, test_01);
  tcase_add_test(tc1_1, test_02);
  tcase_add_test(tc1_1, test_03);
  tcase_add_test(tc1_1, test_04);
  tcase_add_test(tc1_1, test_05);
  tcase_add_test(tc1_1, test_06);
  tcase_add_test(tc1_1, test_07);
  tcase_add_test(tc1_1, test_08);
  tcase_add_test(tc1_1, test_09);
  tcase_add_test(tc1_1, test_010);
  tcase_add_test(tc1_1, test_011);
  tcase_add_test(tc1_1, test_012);
  tcase_add_test(tc1_1, test_013);
  tcase_add_test(tc1_1, test_014);
  tcase_add_test(tc1_1, test_015);
  tcase_add_test(tc1_1, test_016);
  tcase_add_test(tc1_1, test_017);
  tcase_add_test(tc1_1, test_022);

  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);
  return 0;
}
