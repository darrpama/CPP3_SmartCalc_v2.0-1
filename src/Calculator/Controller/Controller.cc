#include "Controller.h"

namespace s21 {

std::string Controller::Calculate(const std::string& expression)
{
  return model_->CalculateExpression(expression);
}

credit_data Controller::CalculateCredit(double sum, double time, double percent, credit_time_type timeType, credit_type creditType)
{
  return creditModel_->CalculateCredit(sum, time, percent, timeType, creditType);
}

deposit_data Controller::CalculateDeposit(double sum, double time, double percent,
                    deposit_time_type timeType, capitalization capitalization,
                    deposit_time_type capitalization_period)
{
  return depositModel_->CalculateDeposit(sum, time, percent, timeType, capitalization, capitalization_period);
}

std::pair<std::vector<double>, std::vector<double>> Controller::GetGraph(std::string expression, double xMin, double xMax)
{
  return model_->GetGraph(expression, xMin, xMax);
}

void Controller::ResetCalculatorModel()
{
  model_->Reset();
}

bool Controller::GetError()
{
  return model_->GetError();
}

}  // namespace s21
