#include "Model.h"

namespace s21 {

// Function to check if a character is a digit
bool CalculationModel::IsDigit(char ch) const {
  return std::isdigit(ch);
}

// Function to convert a string to a double
double CalculationModel::StringToDouble(const string_type& str) const {
  return std::stod(str);
}

// Function to parse the input string and return the parsed expression
void CalculationModel::Parser(const string_type& inputString) {
  for (size_t i = 0; i < inputString.length(); i++) {
    const char ch = inputString[i];

    if (IsDigit(ch) || ch == '.') {
      std::string numberStr;
      size_t j = i;

      while (IsDigit(inputString[j]) || inputString[j] == '.') {
        numberStr += inputString[j];
        j++;
      }

      const double number = StringToDouble(numberStr);
      const token numberToken = {number, numberOrX, numberStr};
      parsedExpression.push_back(numberToken);
      i = j - 1;
    }
    else {
      ProcessOperator(ch);
      ProcessOtherOperators(ch, i, inputString);
    }
  }
}

// Function to process operators and push them into the parsed expression
void CalculationModel::ProcessOperator(const char ch) {
  if (ch == '+') {
    if (parsedExpression.empty() || parsedExpression.back().strValue == "(") {
      parsedExpression.push_back(zeroToken);
    }
    parsedExpression.push_back(addToken);
  }
  else if (ch == '-') {
    if (parsedExpression.empty() || parsedExpression.back().strValue == "(") {
      parsedExpression.push_back(zeroToken);
    }
    parsedExpression.push_back(subToken);
  }
  else if (ch == '*') {
    parsedExpression.push_back(mulToken);
  }
  else if (ch == '/') {
    parsedExpression.push_back(divToken);
  }
  else if (ch == '^') {
    parsedExpression.push_back(powToken);
  }
  else if (ch == '(') {
    if (!parsedExpression.empty() && parsedExpression.back().strValue == ")") {
      parsedExpression.push_back(mulToken);
    }
    parsedExpression.push_back(opbrToken);
  }
  else if (ch == ')') {
    parsedExpression.push_back(clbrToken);
  }
}

// Function to process other operators and push them into the parsed expression
void CalculationModel::ProcessOtherOperators(const char ch, size_t& i, const string_type& inputString) {
  const std::string str = inputString.substr(i);
  if (str.compare(0, 3, "mod") == 0) {
    parsedExpression.push_back(modToken);
  }
  else if (str.compare(0, 4, "asin") == 0) {
    parsedExpression.push_back(asinToken);
    i += 3;
  }
  else if (str.compare(0, 4, "acos") == 0) {
    parsedExpression.push_back(acosToken);
    i += 3;
  }
  else if (str.compare(0, 4, "atan") == 0) {
    parsedExpression.push_back(atanToken);
    i += 3;
  }
  else if (str.compare(0, 3, "sin") == 0) {
    parsedExpression.push_back(sinToken);
  }
  else if (str.compare(0, 3, "cos") == 0) {
    parsedExpression.push_back(cosToken);
  }
  else if (str.compare(0, 3, "tan") == 0) {
    parsedExpression.push_back(tanToken);
  }
  else if (str.compare(0, 3, "log") == 0) {
    parsedExpression.push_back(logToken);
  }
  else if (str.compare(0, 2, "ln") == 0) {
    parsedExpression.push_back(lnToken);
  }
  else if (str.compare(0, 4, "sqrt") == 0) {
    parsedExpression.push_back(sqrtToken);
  }
  else if (ch == 'x' || ch == 'X') {
    parsedExpression.push_back(xToken);
  }
}

CalculationModel::stack_type CalculationModel::PolishParser(const list_type& inputList) const {
  stack_type polishStack;
  stack_type tempStack;
  for (auto it = inputList.begin(); it != inputList.end(); it++) {
    if (IsDigit(*it)) {
      polishStack.push(*it);
    }
    else if (IsOpenBracket(*it)) {
      tempStack.push(*it);
    }
    else if (IsCloseBracket(*it)) {
      if (!tempStack.empty()) {
        while (!IsOpenBracket(tempStack.top())) {
          if (!tempStack.empty()) {
            polishStack.push(tempStack.top());
            tempStack.pop();
          }
          else {
            throw std::invalid_argument("Received pair of brackets");
            break;
          }
        }
      }
      else {
        throw std::invalid_argument("Received pair of brackets");
        break;
      }
      tempStack.pop();
    }
    else if (IsExpression(*it) || IsFunction(*it)) {
      while (!tempStack.empty()) {
        if (it->priority <= tempStack.top().priority) {
          polishStack.push(tempStack.top());
          tempStack.pop();
        } else {
          break;
        }
      }
      tempStack.push(*it);
    }
  }
  if (!tempStack.empty()) {
    if (IsOpenBracket(tempStack.top()) || IsCloseBracket(tempStack.top())) {
      throw std::invalid_argument("There is extra bracket in expression");
    } else {
      while (!tempStack.empty()) {
        polishStack.push(tempStack.top());
        tempStack.pop();
      }
    }
  }
  return polishStack;
}

void CalculationModel::Calculator(const stack_type& polishStack) const {
  stack_type tmp(polishStack);
}

bool CalculationModel::IsDigit(const token& token) const {
  return !std::isnan(token.value);
}

bool CalculationModel::IsExpression(const token& token) const {
  const std::string str = token.strValue;
  return (str.compare(0, 1, "+") == 0 ||
          str.compare(0, 1, "-") == 0 ||
          str.compare(0, 1, "*") == 0 ||
          str.compare(0, 1, "/") == 0 ||
          str.compare(0, 1, "^") == 0 ||
          str.compare(0, 3, "mod") == 0);
}

bool CalculationModel::IsFunction(const token& token) const {
  const std::string str = token.strValue;
  return (str.compare(0, 2, "ln") == 0 ||
          str.compare(0, 3, "sin") == 0 ||
          str.compare(0, 3, "cos") == 0 ||
          str.compare(0, 3, "tan") == 0 ||
          str.compare(0, 3, "log") == 0 ||
          str.compare(0, 4, "asin") == 0 ||
          str.compare(0, 4, "acos") == 0 ||
          str.compare(0, 4, "atan") == 0 ||
          str.compare(0, 4, "sqrt") == 0);
}

bool CalculationModel::IsOpenBracket(const token& token) const {
  const std::string str = token.strValue;
  return (str.compare(0, 1, "(") == 0);
}

bool CalculationModel::IsCloseBracket(const token& token) const {
  const std::string str = token.strValue;
  return (str.compare(0, 1, ")") == 0);
}

void CalculationModel::Reset() {
  parsedExpression.clear();
  polishStack = {};
  answer = {};
}

double CalculationModel::GetData() const {
  return answer;
}

CalculationModel::list_type CalculationModel::GetParsedExpression() const {
  return parsedExpression;
}

void CalculationModel::PrintParsedExpression() const {
  for (auto it = parsedExpression.begin(); it != parsedExpression.end(); ++it) {
    std::cout << it->strValue;
  }
  std::cout << std::endl;
}

}