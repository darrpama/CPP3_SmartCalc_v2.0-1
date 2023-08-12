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
    std::string test_string = "sin(123.321 + asin(0.3))";
    model.parser(test_string);
    model.printParsedExpression();
}