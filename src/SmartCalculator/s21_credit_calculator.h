#ifndef S21_CREDIT_CALCULATOR_H
#define S21_CREDIT_CALCULATOR_H

#include <math.h>
#include <stdlib.h>

typedef struct credit_data {
  double total_sum;
  double *monthly_pay;
  double overpay;
} credit_data;

credit_data credit_calculator_differ(double sum, double time, double percent,
                                     int time_type);
credit_data credit_calculator_anuitet(double sum, double time, double percent,
                                      int time_type);
// void double_to_char(double number, char *out_string);

#endif  // S21_CREDIT_CALCULATOR_H
