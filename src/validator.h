#ifndef VALIDATOR_H
#define VALIDATOR_H

namespace s21 {

#define EPS 1e-7

class Validator {

  public:
    using string_type = std::string;
    using array_type = std::array<string_type>;

    int is_correct(string_type);
    // void filler(char **unary, char **binary);
    int null_check(char *str);
    int empty_check(char *str);
    int num_check(char *str);
    int bracket_check(char *str);
    int binary_op_check(char *str);
    int twise_op_check(char *str);
    int foo_check(char *str);
    int plus_minus_check(char *str);

    int is_digit_or_pm(char ch);
    int binary_left(char ch);
  
  private:

};

}  // namespace s21

#endif  // VALIDATOR_H