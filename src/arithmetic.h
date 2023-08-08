#ifndef SRC_S21_ARITHMETIC_H_
#include <string>

namespace s21 {

enum priority_type {
  bracket,
  number_or_x,
  add_sub,
  mul_div_mod,
  function,
  degree,
  unaric
};

struct token {
  double value;
  priority_type priority;
  std::string str_value;
};


}  // namespace s21

#endif  // SRC_S21_ARITHMETIC_H_
