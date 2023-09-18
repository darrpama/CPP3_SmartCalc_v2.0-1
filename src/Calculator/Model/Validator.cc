#include "Validator.h"

namespace s21 {

Validator::Validator() {}

void Validator::IsNotCorrect(const std::string &inputString) {
  bool err = false;
  bool e_check = IsEmpty(inputString);

  if (!e_check) {
    bool brCheck = IsBracketNotCorrect(inputString);
    bool nCheck = IsNumNotCorrect(inputString);
    bool plMin = IsPlusMinusNotCorrect(inputString);
    bool tCheck = IsTwiseOpNotCorrect(inputString);
    bool fCheck = IsFooNotCorrect(inputString);
    bool bOpCheck = IsBinaryOpNotCorrect(inputString);

    err = brCheck || plMin || nCheck || tCheck || fCheck || bOpCheck;
    // std::cout << brCheck << plMin << nCheck << tCheck << fCheck << bOpCheck
    // << std::endl;
  }

  if (err) {
    throw std::invalid_argument("Validation error");
  }
}

bool Validator::IsEmpty(const std::string &inputString) {
  return inputString.empty();
}

bool Validator::IsBracketNotCorrect(const std::string &inputString) {
  int bracketOpened = 0;

  for (size_t i = 0; i < inputString.size(); i++) {
    const char ch = inputString[i];

    if (ch == '(') {
      if (i > 0 && (inputString[i - 1] == ')' || inputString[i + 1] == ')')) {
        return true;
      }

      if (i > 0 &&
          Contains(not_allowed_for_open_parenthesis_, inputString[i - 1])) {
        return true;
      }

      bracketOpened++;
    }

    if (ch == ')') {
      if (i > 0 && (inputString[i - 1] == '(')) {
        return true;
      }

      if (i > 0 &&
          Contains(not_allowed_for_close_parenthesis_, inputString[i - 1])) {
        return true;
      }

      bracketOpened--;

      if (bracketOpened < 0) {
        return true;
      }
    }
  }

  return bracketOpened != 0;
}

bool Validator::IsPlusMinusNotCorrect(const std::string &inputString) {
  static const std::string ex_str = "1234567890(x.+-scatl";

  for (size_t i = 0; i < inputString.size(); i++) {
    if (inputString[i] == '+' || inputString[i] == '-') {
      if (i + 1 >= inputString.size() ||
          NotContains(ex_str, inputString[i + 1])) {
        return true;
      } else if (i != 0 &&
                 NotContains(allowed_before_plus_minus_, inputString[i - 1])) {
        return true;
      } else if (i == inputString.size()) {
        return true;
      }
    }
  }

  return false;
}

bool Validator::IsNumNotCorrect(const std::string &inputString) {
  bool inFloat{};
  bool dotFound = false;
  bool expFound = false;

  for (size_t i = 0; i < inputString.size(); i++) {
    if ((std::isdigit(inputString[i]) || inputString[i] == 'e' ||
         inputString[i] == '.')) {
      inFloat = true;
    } else {
      inFloat = false;
      dotFound = false;
    }

    if (inputString[i] == '.') {
      if (dotFound || !inFloat) {
        return true;
      }

      if (i > 0 && inputString[i - 1] == 'e') {
        return true;
      }

      dotFound = true;
    }

    if (inputString[i] == 'e') {
      if (expFound || !inFloat) {
        return true;
      }

      if (inputString[i] == 'e' && i > 0 &&
          NotContains(allowed_for_exponent_, inputString[i - 1])) {
        return true;
      }

      expFound = true;
    }
  }

  return false;
}

bool Validator::IsTwiseOpNotCorrect(const std::string &inputString) {
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
          if (i + 3 >= size ||
              (inputString[i + 3] != '(' &&
               (inputString[i + 4] == '*' || inputString[i + 4] == '/' ||
                inputString[i + 4] == '^'))) {
            return true;
          }
        }
        break;
    }
  }

  return false;
}

bool Validator::IsBinaryOpNotCorrect(const std::string &inputString) {
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
    } else if (ch == 'm' && inputString[i + 1] == 'o' &&
               i + 2 < inputString.size() && inputString[i + 2] == 'd') {
      if (i == 0) {
        return true;
      }

      if (!IsDigitOrPm(inputString[i + 3]) || !BinaryLeft(prevch)) {
        return true;
      }
    }
  }

  return false;
}

bool Validator::IsFooNotCorrect(const std::string &inputString) {
  for (size_t i = 0; i < inputString.size(); i++) {
    if (inputString[i] == 'a' &&
        (inputString[i + 1] == 's' || inputString[i + 1] == 'c') &&
        ((inputString[i + 2] != 'i' && inputString[i + 2] != 'o') ||
         (inputString[i + 3] != 'n' && inputString[i + 3] != 's') ||
         inputString[i + 4] != '(' || !IsDigitOrPm(inputString[i + 5]))) {
      return true;
    } else if (inputString[i] == 'a' && inputString[i + 1] == 't' &&
               (inputString[i + 2] != 'a' || inputString[i + 3] != 'n' ||
                inputString[i + 4] != '(' ||
                !IsDigitOrPm(inputString[i + 5]))) {
      return true;
    } else if (inputString[i] == 's' && inputString[i + 1] == 'q' &&
               (inputString[i + 2] != 'r' || inputString[i + 3] != 't' ||
                inputString[i + 4] != '(' ||
                !IsDigitOrPm(inputString[i + 5]))) {
      return true;
    } else if (inputString[i] == 's' && inputString[i + 1] == 'i' &&
               (inputString[i + 2] != 'n' || inputString[i + 3] != '(' ||
                !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 'c' &&
               (inputString[i + 1] != 'o' || inputString[i + 2] != 's' ||
                inputString[i + 3] != '(' ||
                !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 't' && inputString[i + 1] == 'a' &&
               (inputString[i + 2] != 'n' || inputString[i + 3] != '(' ||
                !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 'l' && inputString[i + 1] == 'o' &&
               (inputString[i + 2] != 'g' || inputString[i + 3] != '(' ||
                !IsDigitOrPm(inputString[i + 4]))) {
      return true;
    } else if (inputString[i] == 'l' && inputString[i + 1] == 'n' &&
               inputString[i + 2] != '(' && !IsDigitOrPm(inputString[i + 3])) {
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
  return (ch >= '0' && ch <= '9') || ch == ')' || ch == 'x' || ch == 'e';
}

bool Validator::NotContains(const std::string &string, const char ch) {
  return string.find(ch) == std::string::npos;
}

bool Validator::Contains(const std::string &string, const char ch) {
  return string.find(ch) != std::string::npos;
}

}  // namespace s21
