#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include "arithmetic.h"

#include <math.h>

#include <iostream>
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
    void parser(const std::string&);
    void processOperator(char);
    void processOtherOperators(char, size_t&, string_type);
    stack_type polishParser(list_type);
    void calculator(stack_type);

    void printParsedExpression();
    bool isDigit(char);
    double stringToDouble(const std::string&);
    bool isDigit(token&);
    bool isExpression(token&);
    bool isFunction(token&);
    bool isOpenBracket(token&);
    bool isCloseBracket(token&);
    void reset();
    double getData();

  private:
    list_type parsed_expression;
    stack_type polish_stack;
    double answer{};
    token add_token = {NAN, add_sub, "+"};
    token sub_token = {NAN, add_sub, "-"};
    token mul_token = {NAN, mul_div_mod, "*"};
    token div_token = {NAN, mul_div_mod, "/"};
    token mod_token = {NAN, mul_div_mod, "mod"};
    token pow_token = {NAN, degree, "^"};
    token clbr_token = {NAN, bracket, ")"};
    token opbr_token = {NAN, bracket, "(",};
    token sin_token = {NAN, function, "sin"};
    token cos_token = {NAN, function, "cos"};
    token tan_token = {NAN, function, "tan"};
    token log_token = {NAN, function, "log"};
    token ln_token = {NAN, function, "ln"};
    token asin_token = {NAN, function, "asin"};
    token acos_token = {NAN, function, "acos"};
    token atan_token = {NAN, function, "atan"};
    token sqrt_token = {NAN, function, "sqrt"};
    token x_token = {NAN, number_or_x, "x"};
    token zero_token = {0, number_or_x, "0.0"};
};

}  // namespace s21 

#endif
