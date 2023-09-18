#ifndef DEPOSITMODEL_H
#define DEPOSITMODEL_H

#include <math.h>

#include <iostream>
#include <vector>

namespace s21 {

struct deposit_data {
  double total_sum;
  std::vector<double> monthly_profit;
  double profit;
};

enum class deposit_time_type { deposit_month, deposit_quartal, deposit_year };

enum capitalization { with_capitalization, without_capitalization };

class DepositModel {
 public:
  deposit_data CalculateDeposit(double, double, double, deposit_time_type,
                                capitalization, deposit_time_type);
};

}  // namespace s21

#endif  // DEPOSITMODEL_H
