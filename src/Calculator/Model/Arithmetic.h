#ifndef SRC_S21_ARITHMETIC_H_
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
    return (priority == other.priority &&
            type == other.type &&
            strValue.compare(other.strValue) == 0);
  }
};


}  // namespace s21

#endif  // SRC_S21_ARITHMETIC_H_
