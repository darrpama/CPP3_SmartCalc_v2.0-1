#include "Validator.h"

namespace s21 {

Validator::Validator() {}

bool Validator::IsCorrect(const std::string& inputString) {
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

bool Validator::EmptyCheck(const std::string& inputString) {
  return inputString.empty();
}

bool Validator::BracketCheck(const std::string& inputString) {
  int count = 0;
  int bracketOpened = 0;
  for (size_t i = 0; i < inputString.size(); i++) {
    const char ch = inputString[i];
    if (ch == '(')
    {
      count++;
      bracketOpened++;
    }

    if (ch == ')')
    {
      count--;
      bracketOpened--;
      if (bracketOpened < 0)
      {
        return true;
      }
    }
  }
  return count != 0;
}

bool Validator::PlusMinusCheck(const std::string& inputString) {
  static const std::string ex_str = "1234567890(x.+-";
  static const std::string ex_str2 = "1234567890()x+-";
  for (size_t i = 0; i < inputString.size(); i++) {
    if (inputString[i] == '+' || inputString[i] == '-') {
      if (i + 1 >= inputString.size()) {
        return true;
      } else if (ex_str.find(inputString[i + 1]) == std::string::npos) {
        return true;
      } else if (i != 0 && ex_str2.find(inputString[i - 1]) == std::string::npos) {
        return true;
      }
    }
  }
  return false;
}

bool Validator::NumCheck(const std::string& inputString) {
  bool inFloat = false;
  bool dotFound = false;
  for (size_t i = 0; i < inputString.size(); i++) {
    if (std::isdigit(inputString[i]) && !inFloat) {
      inFloat = true;
      dotFound = false;
    }
    if (inputString[i] == '.') {
      if (dotFound || !inFloat) {
        return true;
      }
      dotFound = true;
    }
  }
  return false;
}

bool Validator::TwiseOpCheck(const std::string& inputString) {
  size_t size = inputString.size();
  for (size_t i = 0; i < size - 1; i++) {
    char ch = inputString[i];
    char nextch = inputString[i + 1];
    switch (ch) {
      case '*':
      case '/':
      case '^':
        if (nextch == ch || nextch == 'm') {
          return true;
        }
        break;
      case 'm':
        if (nextch == 'o' && i + 2 < size && inputString[i + 2] == 'd') {
          if (i + 3 >= size || (inputString[i + 3] != '(' && (inputString[i + 4] == '*' || inputString[i + 4] == '/' || inputString[i + 4] == '^'))) {
            return true;
          }
        }
        break;
    }
  }
  return false;
}

bool Validator::BinaryOpCheck(const std::string& inputString) {
  for (size_t i = 0; i < inputString.size(); i++) {
    char ch = inputString[i];
    char prevch = inputString[i - 1];
    if (ch == '*' || ch == '/' || ch == '^') {
      if (i == 0 || i == inputString.size() - 1) {
        return true;
      }
      if (!BinaryLeft(prevch)) {
        return true;
      }
    } else if (ch == 'm' && inputString[i + 2] == 'o' && i + 2 < inputString.size() && inputString[i + 2] == 'd') {
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

bool Validator::FooCheck(const std::string& inputString) {
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