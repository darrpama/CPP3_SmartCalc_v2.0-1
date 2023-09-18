#include "CreditModel.h"

namespace s21 {

credit_data CreditModel::CalculateCredit(double sum, double time,
                                         double percent,
                                         credit_time_type timeType,
                                         credit_type creditType) {
  credit_data answer_{};

  if (timeType == credit_time_type::credit_year) {
    time *= 12;
  }
  if (creditType == annuitet) {
    double monthlyPercent = (percent / 12) / 100;
    double K = monthlyPercent +
               (monthlyPercent / (pow((1 + monthlyPercent), time) - 1));

    for (int i = 0; i < (int)time; i++) {
      answer_.monthly_pay.push_back(floor(K * sum * 100) / 100);
      answer_.total_sum += answer_.monthly_pay.back();
    }
    answer_.overpay = answer_.total_sum - sum;
  } else if (creditType == differential) {
    double monthlyPercent = (percent / 12) / 100;
    double tmpSum = sum;
    double body = sum / time;
    for (int i = 0; i < (int)time; i++) {
      double p = (tmpSum * monthlyPercent);
      tmpSum -= body;
      answer_.overpay += p;
      answer_.monthly_pay.push_back(body + p);
    }
    answer_.overpay = floor(answer_.overpay * 100) / 100;
    answer_.total_sum = floor((sum + answer_.overpay) * 100) / 100;
  }

  return answer_;
}

}  // namespace s21
