#include "validator.h"

namespace s21 {

Validator::Validator() {}

bool Validator::IsCorrect(const string_type& inputString) {
  bool err = false;
  bool e_check = EmptyCheck(inputString);

  if (!e_check) {
    bool br_check = BracketCheck(inputString);
    bool n_check = NumCheck(inputString);
    bool pl_min = PlusMinusCheck(inputString);
    bool t_check = TwiseOpCheck(inputString);
    bool f_check = FooCheck(inputString);
    bool b_op_check = BinaryOpCheck(inputString);
    err = br_check || pl_min || n_check || t_check || f_check || b_op_check;
  }
  return err;
}

bool Validator::EmptyCheck(const string_type& inputString) {
  return inputString.empty();
}

bool Validator::BracketCheck(const string_type& inputString) {
  int count = 0;
  for (size_t i = 0; i < inputString.size(); i++) {
    const char ch = inputString[i];
    if (ch == '(') {
      count++;
    }
    if (ch == ')') {
      count--;
    }
  }
  return count != 0;
}

bool Validator::PlusMinusCheck(const string_type& inputString) {
  static const string_type ex_str = "1234567890(x.+-";
  static const string_type ex_str2 = "1234567890()x+-";
  for (size_t i = 0; i < inputString.size(); i++) {
    if (inputString[i] == '+' || inputString[i] == '-') {
      if (i + 1 >= inputString.size()) {
        return true;
      } else if (ex_str.find(inputString[i + 1]) == string_type::npos) {
        return true;
      } else if (i != 0 && ex_str2.find(inputString[i - 1]) == string_type::npos) {
        return true;
      }
    }
  }
  return false;
}

bool Validator::NumCheck(const string_type& inputString) {
  for (size_t i = 0; i < inputString.size(); i++) {
    if (isdigit(inputString[i]) && i != 0) {
      if ((i + 1 < inputString.size() && isdigit(inputString[i + 1])) &&
          (isdigit(inputString[i - 1]))) {
        continue;
      } else {
        return true;
      }
    } else if (inputString[i] == '.' && i == 0) {
      return true;
    }
  }
  return false;
}

bool Validator::TwiseOpCheck(const string_type& inputString) {
  for (size_t i = 0; i < inputString.size() - 1; i++) {
    char ch = inputString[i];
    char nextch = inputString[i + 1];
    if (ch == '*' || ch == '/' || ch == '^') {
      if (nextch == ch || nextch == 'm') {
        return true;
      }
    } else if (ch == 'm' && nextch == 'o' && i + 2 < inputString.size() && inputString[i + 2] == 'd') {
      if (i + 3 >= inputString.size() || (inputString[i + 3] != '(' && (inputString[i + 4] == '*' || inputString[i + 4] == '/' || inputString[i + 4] == '^'))) {
        return true;
      }
    }
  }
  return false;
}

bool Validator::BinaryOpCheck(const string_type& inputString) {
  for (size_t i = 0; i < inputString.size() - 1; i++) {
    char ch = inputString[i];
    char nextch = inputString[i + 1];
    if (ch == '*' || ch == '/' || ch == '^') {
      if (i == 0) {
        return true;
      }
      char prevch = inputString[i - 1];
      if (!IsDigitOrPm(nextch) || !BinaryLeft(prevch)) {
        return true;
      }
      if (ch == '/' && nextch == '0') {
        return true;
      }
    } else if (ch == 'm' && nextch == 'o' && i + 2 < inputString.size() && inputString[i + 2] == 'd') {
      if (i == 0) {
        return true;
      }
      char prevch = inputString[i - 1];
      if (!IsDigitOrPm(inputString[i + 3]) || !BinaryLeft(prevch)) {
        return true;
      }
    }
  }
  return false;
}

bool Validator::FooCheck(const string_type& inputString) {
  for (size_t i = 0; i < inputString.size(); i++) {
    if (inputString[i] == 'a' && (inputString[i + 1] == 's' || inputString[i + 1] == 'c') &&
        (inputString[i + 2] != 'i' || inputString[i + 3] != 'n' || inputString[i + 4] != '(' || !IsDigitOrPm(inputString[i + 5]))) {
      return true;
    } else if (inputString[i] == 'a' && inputString[i + 1] == 't' &&
               (inputString[i + 2] != 'a' || inputString[i + 3] != 'n' || inputString[i + 4] != '(' || !IsDigitOrPm(inputString[i + 5]))) {
      return true;
    } else if (inputString[i] == 's' && inputString[i + 1] == 'q' &&
               (inputString[i + 2] != 'r' || inputString[i + 3] != 't' || inputString[i + 4] != '(' || !IsDigitOrPm(inputString[i + 5]))) {
      return true;
    } else if (inputString[i] == 's' && inputString[i + 1] == 'i' &&
               (inputString[i + 2] != 'n' || inputString[i + 3] != '(' || !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 'c' &&
               (inputString[i + 1] != 'o' || inputString[i + 2] != 's' || inputString[i + 3] != '(' || !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 't' && inputString[i + 1] == 'a' &&
               (inputString[i + 2] != 'n' || inputString[i + 3] != '(' || !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 'l' && inputString[i + 1] == 'o' &&
               (inputString[i + 2] != 'g' || inputString[i + 3] != '(' || !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 'l' && inputString[i + 1] == 'n' && inputString[i + 2] != '(' && !IsDigitOrPm(inputString[i + 3])) {
      return true;
    }
  }
  return false;
}

bool Validator::IsDigitOrPm(char ch) {
  return (ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == 's' ||
      ch == 'c' || ch == 'a' || ch == 't' || ch == 'l' || ch == '(';
}

bool Validator::BinaryLeft(char ch) {
  return (ch >= '0' && ch <= '9') || ch == ')';
}

}  // namespace s21
