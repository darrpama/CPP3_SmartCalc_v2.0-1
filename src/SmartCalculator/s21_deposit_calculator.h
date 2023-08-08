#ifndef S21_DEPOSIT_CALCULATOR_H
#define S21_DEPOSIT_CALCULATOR_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct deposit_data {
  double total_sum;
  double *montly_pay;
  double profit;
} deposit_data;

deposit_data deposit_calculator_mounth(double sum, double time, double percent,
                                       int time_type, int kap);
deposit_data deposit_calculator_quartal(double sum, double time, double percent,
                                        int time_type, int kap);

#endif  // S21_DEPOSIT_CALCULATOR_H
