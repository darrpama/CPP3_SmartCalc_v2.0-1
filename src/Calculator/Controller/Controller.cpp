#include "Controller.h"

namespace s21 {

std::string Controller::Calculate(std::string expression)
{
    model->Parser(expression);
    return std::to_string(model->GetAnswer());
}

void Controller::Reset(){
    model->reset();

}  // namespace s21

}
