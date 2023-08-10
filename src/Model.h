#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include "arithmetic.h"

#include <math.h>

#include <stack>
#include <string>
#include <list>

namespace s21 {

const token add_token = {NAN, add_sub, "+"};
const token sub_token = {NAN, add_sub, "-"};
const token mul_token = {NAN, mul_div_mod, "*"};
const token div_token = {NAN, mul_div_mod, "/"};
const token mod_token = {NAN, mul_div_mod, "mod"};
const token pow_token = {NAN, degree, "^"};
const token clbr_token = {NAN, bracket, ")"};
const token opbr_token = {NAN, bracket, "(",};
const token sin_token = {NAN, function, "sin"};
const token cos_token = {NAN, function, "cos"};
const token tan_token = {NAN, function, "tan"};
const token log_token = {NAN, function, "log"};
const token ln_token = {NAN, function, "ln"};
const token asin_token = {NAN, function, "asin"};
const token acos_token = {NAN, function, "acos"};
const token atan_token = {NAN, function, "atan"};
const token sqrt_token = {NAN, function, "sqrt"};
const token x_token = {NAN, number_or_x, "x"};
const token zero_token = {0, number_or_x, ""};

class CalculationModel {
  using stack_type = std::stack<token>;
  using string_type = std::string;
  using list_type = std::list<token>;

  public:
    CalculationModel() : answer(0){};
    list_type parser(string_type input_string);
    stack_type polishParser(list_type input_list);
    void calculator(stack_type polish_stack);

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
