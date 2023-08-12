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

  public:
    using stack_type = std::stack<token>;
    using string_type = std::string;
    using list_type = std::list<token>;

    CalculationModel() : answer(0){};
    void Parser(const string_type&);
    void ProcessOperator(const char);
    void ProcessOtherOperators(const char, size_t&, const string_type&);
    stack_type PolishParser(const list_type&) const;
    void Calculator(const stack_type&) const;

    void PrintParsedExpression() const;
    bool IsDigit(char) const;
    double StringToDouble(const string_type&) const;
    bool IsDigit(const token&) const;
    bool IsExpression(const token&) const;
    bool IsFunction(const token&) const;
    bool IsOpenBracket(const token&) const;
    bool IsCloseBracket(const token&) const;
    void Reset();
    double GetData() const;
    list_type GetParsedExpression() const;

  private:
    list_type parsedExpression;
    stack_type polishStack;
    double answer{};
    token addToken = {NAN, addSub, "+"};
    token subToken = {NAN, addSub, "-"};
    token mulToken = {NAN, mulDivMod, "*"};
    token divToken = {NAN, mulDivMod, "/"};
    token modToken = {NAN, mulDivMod, "mod"};
    token powToken = {NAN, degree, "^"};
    token clbrToken = {NAN, bracket, ")"};
    token opbrToken = {NAN, bracket, "(",};
    token sinToken = {NAN, function, "sin"};
    token cosToken = {NAN, function, "cos"};
    token tanToken = {NAN, function, "tan"};
    token logToken = {NAN, function, "log"};
    token lnToken = {NAN, function, "ln"};
    token asinToken = {NAN, function, "asin"};
    token acosToken = {NAN, function, "acos"};
    token atanToken = {NAN, function, "atan"};
    token sqrtToken = {NAN, function, "sqrt"};
    token xToken = {NAN, numberOrX, "x"};
    token zeroToken = {0, numberOrX, "0.0"};
};

}  // namespace s21 

#endif
