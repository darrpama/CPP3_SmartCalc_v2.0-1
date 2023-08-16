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
    void PolishParser();
    void Calculator();

    void PrintParsedExpression() const;
    void PrintPolishStack() const;
    bool IsDigit(char) const;
    double StringToDouble(const string_type&) const;
    bool IsDigit(const token&) const;
    bool IsExpression(const token&) const;
    bool IsFunction(const token&) const;
    bool IsOpenBracket(const token&) const;
    bool IsCloseBracket(const token&) const;
    void Reset();
    double GetAnswer() const;
    list_type GetParsedExpression() const;
    list_type GetPolishStack() const;
    void SetAnswer(token);
    token DoOper(token, token, token);
    token DoFunc(token, token);

  private:
    list_type parsedExpression;
    list_type polishStack;
    double answer{};
    token addToken = {0.0, addSub, addition, "+"};
    token subToken = {0.0, addSub, substraction, "-"};
    token mulToken = {0.0, mulDivMod, multiplication, "*"};
    token divToken = {0.0, mulDivMod, division, "/"};
    token modToken = {0.0, mulDivMod, modulo, "mod"};
    token powToken = {0.0, degree, power, "^"};
    token clbrToken = {0.0, bracket, closeBracket, ")"};
    token opbrToken = {0.0, bracket, openBracket, "(",};
    token sinToken = {0.0, function, sinus, "sin"};
    token cosToken = {0.0, function, cosinus, "cos"};
    token tanToken = {0.0, function, tangens, "tan"};
    token logToken = {0.0, function, decimalLogarithm, "log"};
    token lnToken = {0.0, function, naturalLogarithm, "ln"};
    token asinToken = {0.0, function, arcsin, "asin"};
    token acosToken = {0.0, function, arccos, "acos"};
    token atanToken = {0.0, function, arctan, "atan"};
    token sqrtToken = {0.0, function, squareRoot, "sqrt"};
    token xToken = {0.0, numberOrX, xValue, "x"};
    token zeroToken = {0.0, numberOrX, zero, "0.0"};
};

}  // namespace s21 

#endif
