#ifndef DEPOSITMODEL_H
#define DEPOSITMODEL_H


class DepositModel
{
public:
    DepositModel();
    typedef struct deposit_data {
      double total_sum;
      double *monthly_pay;
      double overpay;
    } deposit_data;
};

#endif // DEPOSITMODEL_H
