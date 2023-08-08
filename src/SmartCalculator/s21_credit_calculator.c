/* ************************************************************************** */
/*                                                                            */
/*   s21_credit_calculator */
/*   By: darrpama <darrpama@student.21-school.ru>                             */
/*                                                                            */
/* ************************************************************************** */

#include "s21_credit_calculator.h"
credit_data credit_calculator_differ(double sum, double time, double percent,
                                     int time_type) {
  credit_data data = {0, NULL, 0};
  if (time_type == 1) {
    time *= 12;
  }
  double tmp_sum = sum;
  double monthly_percent = (percent / 12) / 100;
  data.monthly_pay = (double *)malloc(sizeof(double) * (int)time);
  double body = sum / time;
  for (int i = 0; i < (int)time; i++) {
    data.monthly_pay[i] = body + tmp_sum * monthly_percent;
    tmp_sum -= body;
    data.total_sum += data.monthly_pay[i];
  }
  data.overpay = data.total_sum - sum;
  return data;
}

credit_data credit_calculator_anuitet(double sum, double time, double percent,
                                      int time_type) {
  credit_data data = {0, NULL, 0};
  if (time_type == 1) {
    time *= 12;
  }
  double monthly_percent = (percent / 12) / 100;
  data.monthly_pay = (double *)malloc(sizeof(double) * (int)time);
  double koeff = monthly_percent * pow(1 + monthly_percent, time) /
                 (pow(1 + monthly_percent, time) - 1);
  for (int i = 0; i < (int)time; i++) {
    data.monthly_pay[i] = sum * koeff;
  }
  data.total_sum = data.monthly_pay[0] * time;
  data.overpay = data.total_sum - sum;
  return data;
}
