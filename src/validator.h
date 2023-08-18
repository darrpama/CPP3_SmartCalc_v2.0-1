#ifndef VALIDATOR_H
#define VALIDATOR_H

namespace s21 {

#define EPS 1e-7

class Validator {

  public:
    using string_type = std::string;
    using array_type = std::array<string_type>;

    int IsCorrect(string_type);
    // void filler(char **unary, char **binary);
    int NullCheck(char *str);
    int EmptyCheck(char *str);
    int NumCheck(char *str);
    int BracketCheck(char *str);
    int BinaryOpCheck(char *str);
    int TwiseOpCheck(char *str);
    int FooCheck(char *str);
    int PlusMinusCheck(char *str);

    int IsDigitOrPm(char ch);
    int BinaryLeft(char ch);
  
  private:
    std::set<std::string> unary { "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt" };
    std::set<std::string> binary { "*", "/", "mod", "^", "+", "-"};

};

}  // namespace s21

#endif  // VALIDATOR_H