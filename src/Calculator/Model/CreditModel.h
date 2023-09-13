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


};

#endif // CREDITMODEL_H
