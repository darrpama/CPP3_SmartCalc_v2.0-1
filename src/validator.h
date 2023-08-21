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
    int IsCorrect(string_type);
    // void filler(char **unary, char **binary);
    int NullCheck(string_type);
    int EmptyCheck(string_type);
    int NumCheck(string_type);
    int BracketCheck(string_type);
    int BinaryOpCheck(string_type);
    int TwiseOpCheck(string_type);
    int FooCheck(string_type);
    int PlusMinusCheck(string_type);

    int IsDigitOrPm(char ch);
    int BinaryLeft(char ch);
  
  private:
    std::set<std::string> unary { "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt" };
    std::set<std::string> binary { "*", "/", "mod", "^", "+", "-"};

};

}  // namespace s21

#endif  // VALIDATOR_H