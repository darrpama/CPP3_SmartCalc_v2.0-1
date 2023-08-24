#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <set>

namespace s21 {

#define EPS 1e-7

class Validator {

  public:
    using string_type = std::string;

    Validator();
    bool IsCorrect(const string_type&);
    bool EmptyCheck(const string_type&);
    bool NumCheck(const string_type&);
    bool BracketCheck(const string_type&);
    bool BinaryOpCheck(const string_type&);
    bool TwiseOpCheck(const string_type&);
    bool FooCheck(const string_type&);
    bool PlusMinusCheck(const string_type&);

    bool IsDigitOrPm(char ch);
    bool BinaryLeft(char ch);
  
  private:
    std::set<std::string> unary { "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt" };
    std::set<std::string> binary { "*", "/", "mod", "^", "+", "-"};

};

}  // namespace s21

#endif  // VALIDATOR_H
