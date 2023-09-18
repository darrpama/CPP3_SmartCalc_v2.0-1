#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <math.h>

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "Arithmetic.h"
#include "Validator.h"

namespace s21 {

class Model {
 public:
  using stack_type = std::stack<token>;
  using list_type = std::list<token>;

  Model() : answer_(0){};

  void Parser(const std::string&);
  void ProcessOperator(const char);
  void ProcessOtherOperators(const char, size_t&, const std::string&);
  void PolishParser();
  void Calculator();
  std::string CalculateExpression(const std::string&);
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
  std::pair<std::vector<double>, std::vector<double>> GetGraph(
      const std::string&, double, double);
  void SetAnswer(token);
  void SetStrAnswer(const double);
  void SetStrAnswer(const std::exception&);
  list_type GetParsedExpression() const;
  list_type GetPolishStack() const;
  bool GetError() const;
  void SetError(bool);
  void Reset();

 private:
  Validator validator_;
  list_type parsedExpression_;
  list_type polishStack_;
  double answer_{};
  std::string stringAnswer_ = "";
  bool error_{};
};

}  // namespace s21

#endif
