#include "Controller.h"

namespace s21 {

std::string Controller::Calculate(const std::string& expression)
{
  return model->CaclulateExpression(expression);
}

std::vector<std::pair<double, double>> Controller::GetGraph(std::string expression, double xMin, double xMax)
{
  std::vector<std::pair<double, double>> answer = {{0.0, 1.0}, {1.1, 2.2}};

  return answer;

}

void Controller::Reset(){
  model->Reset();
}  // namespace s21

bool Controller::GetError()
{
  return model->GetError();
}

}	// namespace s21
