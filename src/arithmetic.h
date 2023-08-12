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

struct token {
  double value;
  priority_type priority;
  std::string strValue;

  bool operator==(const token& other) const {
    return (value == other.value &&
            priority == other.priority &&
            strValue.compare(other.strValue) == 0);
  }
};


}  // namespace s21

#endif  // SRC_S21_ARITHMETIC_H_
