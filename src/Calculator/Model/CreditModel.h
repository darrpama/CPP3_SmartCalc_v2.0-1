#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <list>
#include <math.h>

namespace s21 {

typedef struct credit_data
{
  double total_sum;
  std::list<double> monthly_pay;
  double overpay;
} credit_data;

enum time_type {
  month,
  year
};

enum credit_type {
  differential,
  annuitet
};


class CreditModel
{
public:
    CreditModel();
    credit_data GetAnswer();
    void CalculateCredit(double, double, double, time_type, credit_type);
    void ResetModel();

private:
    credit_data answer;
};

}  // namespace s21

#endif // CREDITMODEL_H
