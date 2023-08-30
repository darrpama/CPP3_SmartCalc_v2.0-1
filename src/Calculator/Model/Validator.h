#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <set>
#include <regex>

namespace s21 {

#define EPS 1e-7

class Validator {

  public:
    Validator();
    bool IsCorrect(const std::string&);
    bool EmptyCheck(const std::string&);
    bool NumCheck(const std::string&);
    bool BracketCheck(const std::string&);
    bool BinaryOpCheck(const std::string&);
    bool TwiseOpCheck(const std::string&);
    bool FooCheck(const std::string&);
    bool PlusMinusCheck(const std::string&);

    bool IsDigitOrPm(char ch);
    bool BinaryLeft(char ch);
  
  private:
    std::set<std::string> unary { "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt" };
    std::set<std::string> binary { "*", "/", "mod", "^", "+", "-"};

};

}  // namespace s21

#endif  // VALIDATOR_H
