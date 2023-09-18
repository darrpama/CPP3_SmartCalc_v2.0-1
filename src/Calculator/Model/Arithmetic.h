#ifndef SRC_S21_ARITHMETIC_H_
#define SRC_S21_ARITHMETIC_H_

#include <string>

namespace s21 {

enum priority_type {
  bracket,
  numberOrX,
  addSub,
  mulDivMod,
  function,
  degree,
  unaric
};

enum token_type {
  openBracket,
  closeBracket,
  numberType,
  addition,
  subtraction,
  multiplication,
  division,
  modulo,
  sinus,
  cosinus,
  tangens,
  arcsin,
  arccos,
  arctan,
  power,
  decimalLogarithm,
  naturalLogarithm,
  unaricMinus,
  unaricPlus,
  squareRoot,
  xValue,
};

struct token {
  double value;
  priority_type priority;
  token_type type;
  std::string strValue;

  bool operator==(const token& other) const {
    return (priority == other.priority && type == other.type &&
            value == other.value);
  }
};

static token addToken = {0.0, addSub, addition, "+"};
static token subToken = {0.0, addSub, subtraction, "-"};
static token mulToken = {0.0, mulDivMod, multiplication, "*"};
static token divToken = {0.0, mulDivMod, division, "/"};
static token modToken = {0.0, mulDivMod, modulo, "mod"};
static token powToken = {0.0, degree, power, "^"};
static token clbrToken = {0.0, bracket, closeBracket, ")"};
static token opbrToken = {0.0, bracket, openBracket, "("};
static token sinToken = {0.0, function, sinus, "sin"};
static token cosToken = {0.0, function, cosinus, "cos"};
static token tanToken = {0.0, function, tangens, "tan"};
static token logToken = {0.0, function, decimalLogarithm, "log"};
static token lnToken = {0.0, function, naturalLogarithm, "ln"};
static token asinToken = {0.0, function, arcsin, "asin"};
static token acosToken = {0.0, function, arccos, "acos"};
static token atanToken = {0.0, function, arctan, "atan"};
static token sqrtToken = {0.0, function, squareRoot, "sqrt"};
static token xToken = {0.0, numberOrX, xValue, "x"};
static token zeroToken = {0.0, numberOrX, numberType, "0.0"};

}  // namespace s21

#endif  // SRC_S21_ARITHMETIC_H_
