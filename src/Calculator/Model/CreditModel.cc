#include "CreditModel.h"

namespace s21
{

CreditModel::CreditModel()
{
}

void CreditModel::CalculateCredit(double sum, double time, double percent, time_type timeType, credit_type creditType)
{
  if (timeType == year)
  {
    time *= 12;
  }
  if (creditType == annuitet)
  {
    double monthlyPercent = (percent / 12) / 100;
    double K = monthlyPercent + (monthlyPercent / (pow((1 + monthlyPercent), time) - 1));

    for (int i = 0; i < (int)time; i++) {
      answer.monthly_pay.push_back(floor(K * sum * 100) / 100);
      answer.total_sum += answer.monthly_pay.back();
    }
    answer.overpay = answer.total_sum - sum;
  }
  else if (creditType == differential)
  {
    double monthlyPercent = (percent / 12) / 100;
    double tmpSum = sum;
    double body = sum / time;
    for (int i = 0; i < (int)time; i++) {
      double p = (tmpSum * monthlyPercent);
      tmpSum -= body;
      answer.overpay += p;
      answer.monthly_pay.push_back(body + p);
    }
    answer.overpay = floor(answer.overpay * 100) / 100;
    answer.total_sum = floor((sum + answer.overpay) * 100) / 100;
  }
}

credit_data CreditModel::GetAnswer()
{
  return answer;
}

void CreditModel::ResetModel()
{
  answer.overpay = 0.0;
  answer.total_sum = 0.0;
  answer.monthly_pay.clear();
}

}