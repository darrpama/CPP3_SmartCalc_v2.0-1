#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include "Arithmetic.h"
#include "Validator.h"

#include <math.h>

#include <iostream>
#include <stack>
#include <string>
#include <list>

namespace s21 {
// TODO изменить название класса на Model
class CalculationModel {

  public:
    using stack_type = std::stack<token>;
    using list_type = std::list<token>;

    CalculationModel() : answer(0){};
    void Parser(const std::string&);
    void ProcessOperator(const char);
    void ProcessOtherOperators(const char, size_t&, const std::string&);
    void PolishParser();
    void Calculator();

    std::string CalculateExpression(const std::string&);
    void PrintParsedExpression() const;
    void PrintPolishStack() const;
    bool IsDigit(char) const;
    double StringToDouble(const std::string&) const;
    bool IsNumber(const token&) const;
    bool IsExpression(const token&) const;
    bool IsFunction(const token&) const;
    bool IsOpenBracket(const token&) const;
    bool IsCloseBracket(const token&) const;
    token DoExpression(token, token, token);
    token DoFunction(token, token);

    double GetDoubleAnswer() const;
    std::string GetStringAnswer() const;
    std::pair<std::vector<double>, std::vector<double>> GetGraph(std::string, double, double);
    void SetAnswer(token);
    void SetStrAnswer(const double);
    void SetStrAnswer(const std::string&);
    void SetStrAnswer(const std::exception&);
    list_type GetParsedExpression() const;
    list_type GetPolishStack() const;

    bool GetError();
    void SetError(bool);
    void Reset();

    token addToken = {0.0, addSub, addition, "+"};
    token subToken = {0.0, addSub, subtraction, "-"};
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
    token zeroToken = {0.0, numberOrX, numberType, "0.0"};

  private:
    Validator validator;
    list_type parsedExpression;
    list_type polishStack;
    double answer{};
    std::string stringAnswer = "";
    bool error;
};

}  // namespace s21 

#endif
