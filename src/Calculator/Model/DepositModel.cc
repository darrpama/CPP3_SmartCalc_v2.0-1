#include "DepositModel.h"

namespace s21 {

deposit_data DepositModel::CalculateDeposit(
    double sum, double time, double percent, deposit_time_type timeType,
    capitalization capitalization, deposit_time_type capitalization_period) {
  deposit_data data{};

  if (timeType == deposit_time_type::deposit_year) {
    time *= 12;
  }

  double monthly_percent = (percent / 12) / 100;

  if (capitalization == capitalization::without_capitalization) {
    double monthly_profit = sum * monthly_percent;
    data.profit = monthly_profit * time;
    data.total_sum = sum + data.profit;

    for (int i = 0; i < (int)time; i++) {
      data.monthly_profit.push_back(monthly_profit);
    }
  } else {
    double percentable_sum = sum;
    switch (capitalization_period) {
      case (deposit_time_type::deposit_month):
        data.total_sum = sum;
        for (int i = 0; i < (int)time; i++) {
          double monthly_profit = monthly_percent * percentable_sum;
          data.monthly_profit.push_back(monthly_profit);
          data.profit += monthly_profit;
          percentable_sum = data.total_sum;
          data.total_sum += monthly_profit;
        }
        break;
      case (deposit_time_type::deposit_quartal):
        data.total_sum = sum;
        for (int i = 1; i <= (int)time; i++) {
          double monthly_profit = monthly_percent * percentable_sum;
          data.monthly_profit.push_back(monthly_profit);
          data.profit += monthly_profit;
          if (i % 4 == 0) {
            percentable_sum = data.total_sum;
          }
          data.total_sum += monthly_profit;
        }
        break;
      case (deposit_time_type::deposit_year):
        data.total_sum = sum;
        for (int i = 1; i <= (int)time; i++) {
          double monthly_profit = monthly_percent * percentable_sum;
          data.monthly_profit.push_back(monthly_profit);
          data.profit += monthly_profit;
          if (i % 12 == 0) {
            percentable_sum = data.total_sum;
          }
          data.total_sum += monthly_profit;
        }
        break;
    }
  }
  return data;
}
}  // namespace s21
