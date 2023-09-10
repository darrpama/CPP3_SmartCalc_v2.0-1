#ifndef CREDITMODEL_H
#define CREDITMODEL_H


class CreditModel
{
public:
    CreditModel();
    typedef struct credit_data {
      double total_sum;
      double *monthly_pay;
      double overpay;
    } credit_data;

    credit_data credit_calculator_differ(double sum, double time, double percent,
                                         int time_type);
    credit_data credit_calculator_anuitet(double sum, double time, double percent,
                                          int time_type);

};

#endif // CREDITMODEL_H
