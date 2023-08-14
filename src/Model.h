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
    double GetData() const;
    list_type GetParsedExpression() const;
    list_type GetPolishStack() const;
    void SetAnswer(token);
    token DoOper(token, token, token);
    token DoFunc(token, token);

  private:
    list_type parsedExpression;
    list_type polishStack;
    double answer{};
    token addToken = {NAN, addSub, addition, "+"};
    token subToken = {NAN, addSub, substraction, "-"};
    token mulToken = {NAN, mulDivMod, multiplication, "*"};
    token divToken = {NAN, mulDivMod, division, "/"};
    token modToken = {NAN, mulDivMod, modulo, "mod"};
    token powToken = {NAN, degree, power, "^"};
    token clbrToken = {NAN, bracket, closeBracket, ")"};
    token opbrToken = {NAN, bracket, openBracket, "(",};
    token sinToken = {NAN, function, sinus, "sin"};
    token cosToken = {NAN, function, cosinus, "cos"};
    token tanToken = {NAN, function, tangens, "tan"};
    token logToken = {NAN, function, decimalLogarithm, "log"};
    token lnToken = {NAN, function, naturalLogarithm, "ln"};
    token asinToken = {NAN, function, arcsin, "asin"};
    token acosToken = {NAN, function, arccos, "acos"};
    token atanToken = {NAN, function, arctan, "atan"};
    token sqrtToken = {NAN, function, squareRoot, "sqrt"};
    token xToken = {NAN, numberOrX, xValue, "x"};
    token zeroToken = {0, numberOrX, zero, "0.0"};
};

}  // namespace s21 

#endif
