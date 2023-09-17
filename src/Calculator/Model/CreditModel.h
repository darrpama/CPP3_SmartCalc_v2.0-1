#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <vector>
#include <math.h>
#include <iostream>

namespace s21 {

struct credit_data
{
  double total_sum;
  std::vector<double> monthly_pay;
  double overpay;
};

enum class credit_time_type {
  credit_month,
  credit_quartal,
  credit_year
};

enum credit_type {
  differential,
  annuitet
};


class CreditModel
{
 public:
  credit_data CalculateCredit(double, double, double, credit_time_type, credit_type);
};

}  // namespace s21

#endif // CREDITMODEL_H
