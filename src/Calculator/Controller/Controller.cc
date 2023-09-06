#include "Controller.h"

namespace s21 {

std::string Controller::Calculate(const std::string& expression)
{
  return model->CaclulateExpression(expression);
}

std::pair<std::vector<double>, std::vector<double>> Controller::GetGraph(std::string expression, double xMin, double xMax)
{
  return model->GetGraph(expression, xMin, xMax);
}

void Controller::Reset()
{
  model->Reset();
}  // namespace s21

bool Controller::GetError()
{
  return model->GetError();
}

}	// namespace s21
