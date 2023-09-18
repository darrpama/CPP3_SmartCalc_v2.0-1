#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <regex>
#include <set>
#include <string>

namespace s21 {

#define EPS 1e-7

class Validator {
 public:
  Validator();
  void IsNotCorrect(const std::string&);
  bool IsEmpty(const std::string&);
  bool IsNumNotCorrect(const std::string&);
  bool IsBracketNotCorrect(const std::string&);
  bool IsBinaryOpNotCorrect(const std::string&);
  bool IsTwiseOpNotCorrect(const std::string&);
  bool IsFooNotCorrect(const std::string&);
  bool IsPlusMinusNotCorrect(const std::string&);

  bool IsDigitOrPm(char);
  bool BinaryLeft(char);

 private:
  bool NotContains(const std::string&, const char);
  bool Contains(const std::string&, const char);

  const std::string not_allowed_for_digits_ = ")xe";
  const std::string not_allowed_for_x_ = ")x.0123456789e";
  const std::string operators_ = "-+md*/^";
  const std::string not_unary_ = "m*/^";
  const std::string unary_ = "+-";
  const std::string not_allowed_for_not_unary_ = ".+-*/^de(";
  const std::string not_allowed_for_unary_ = ".+-*/^d";
  const std::string function_first_chars_ = "cstal";
  const std::string not_allowed_for_function_chars_ = ")0123456789.xe";
  const std::string allowed_first_chars_ = "0123456789x-+acstl(";
  const std::string not_allowed_first_chars_ = "e.*/m)";
  const std::string not_allowed_for_open_parenthesis_ = "e.0123456789x)";
  const std::string not_allowed_for_close_parenthesis_ = "e.(dnst^+-/*";
  const std::string allowed_for_exponent_ = "x0123456789)";
  const std::string allowed_before_plus_minus_ = "0123456789()xe";
};

}  // namespace s21

#endif  // VALIDATOR_H
