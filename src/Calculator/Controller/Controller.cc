#include "Controller.h"

namespace s21 {

std::string Controller::Calculate(const std::string& expression)
{
  return model->CalculateExpression(expression);
}

credit_data Controller::CalculateCredit(double sum, double time, double percent, time_type timeType, credit_type creditType)
{
  return creditModel->CalculateCredit(sum, time, percent, timeType, creditType);
}

std::pair<std::vector<double>, std::vector<double>> Controller::GetGraph(std::string expression, double xMin, double xMax)
{
  return model->GetGraph(expression, xMin, xMax);
}

void Controller::ResetCalculatorModel()
{
  model->Reset();
}

void Controller::ResetCreditModel()
{
  // creditModel->Reset();
}

bool Controller::GetError()
{
  return model->GetError();
}

}	// namespace s21
