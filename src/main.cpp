// int main() {
//     ExampleModel model;
//     ExampleController controller(&model);
//     ConsoleView view(&controller);
//     view.startEventLoop();
//     return 1;
// }

#include "Model.h"

int main() {
  s21::CalculationModel model;
  std::string test_string_1 = "sin(123.321 + asin(0.3))";
  model.Parser(test_string_1);
  model.PrintParsedExpression();
  model.Reset();
  std::string test_string_2 = "(123.321 + 2mod3*(0.3))";
  model.Parser(test_string_2);
  model.PrintParsedExpression();
  model.Reset();
  std::string test_string_3 = "123.321 + 0.3";
  model.Parser(test_string_3);
  model.PrintParsedExpression();
  model.Reset();
  std::string test_string_4 = "((123.21312)*sin(123.321) + asin(0.3))";
  model.Parser(test_string_4);
  model.PrintParsedExpression();
  model.Reset();
  std::string test_string_5 = "sin(123.321 + asin(0.3))";
  model.Parser(test_string_5);
  model.PrintParsedExpression();
  model.Reset();
}