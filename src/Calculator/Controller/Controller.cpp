#include "Controller.h"

namespace s21 {

std::string Controller::Calculate(std::string expression)
{
  model->Parser(expression);
  return model->GetStringAnswer();
}

std::pair<std::array<double>, std::array<double>> Controller::DrawGraph()
{

}

void Controller::Reset(){
  model->reset();
}  // namespace s21

}
