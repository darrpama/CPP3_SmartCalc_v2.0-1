#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include "arithmetic.h"

#include <math.h>

#include <stack>
#include <string>
#include <list>

namespace s21 {
class CalculationModel {
  using stack_type = std::stack<token>;
  using string_type = std::string;
  using list_type = std::list<token>;

  public:
    CalculationModel() : answer(0){};
    list_type parser(string_type input_string);
    stack_type polishParser(list_type input_list);
    double calculator(stack_type input_stack);

    bool isDigit();
    bool isExpression();
    bool isFunc();
    bool isOpenBracket();
    bool isCloseBracket();
    void reset();
    double getData();

  private:
    stack_type polish_stack;
    list_type list;
    double answer{};
};

}  // namespace s21 

#endif
