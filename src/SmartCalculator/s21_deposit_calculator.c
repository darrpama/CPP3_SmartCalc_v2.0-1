/* ************************************************************************** */
/*                                                                            */
/*   s21_deposit_calculator */
/*   By: darrpama <darrpama@student.21-school.ru>                             */
/*                                                                            */
/* ************************************************************************** */

#include "s21_deposit_calculator.h"
deposit_data deposit_calculator_mounth(double sum, double time, double percent,
                                       int time_type, int kap) {
  deposit_data data = {0, NULL, 0};
  if (time_type == 1) {
    time *= 12;
  }
  double monthly_percent = (percent / 12) / 100;
  data.montly_pay = (double *)malloc(sizeof(double) * (int)time);
  if (kap == 0) {
    double monthly_profit = monthly_percent * sum;
    data.profit = monthly_profit * time;
    data.total_sum = sum + monthly_profit * time;

    for (int i = 0; i < (int)time; i++) {
      data.montly_pay[i] = monthly_profit;
    }
  } else {
    for (int i = 0; i < (int)time; i++) {
      double monthly_profit = monthly_percent * sum;
      data.montly_pay[i] = monthly_profit;
      data.profit += monthly_profit;
      sum += monthly_profit;
    }
    data.total_sum = sum;
  }
  return data;
}

deposit_data deposit_calculator_quartal(double sum, double time, double percent,
                                        int time_type, int kap) {
  deposit_data data = {0, NULL, 0};
  if (time_type == 1) {
    time *= 12;
  }
  double percentable_sum = sum;
  double monthly_percent = (percent / 12) / 100;
  data.montly_pay = (double *)malloc(sizeof(double) * (int)time);
  if (kap == 0) {
    double monthly_profit = monthly_percent * sum;
    data.profit = monthly_profit * time;
    data.total_sum = sum + monthly_profit * time;
    for (int i = 0; i < (int)time; i++) {
      data.montly_pay[i] = monthly_profit;
    }
  } else {
    for (int i = 0; i < (int)time; i++) {
      double monthly_profit = monthly_percent * percentable_sum;
      int month = i + 1;
      data.montly_pay[i] = monthly_profit;
      data.profit += monthly_profit;
      if (month % 4 == 0) percentable_sum = sum;
      sum += monthly_profit;
    }
    data.total_sum = sum;
  }
  return data;
}
