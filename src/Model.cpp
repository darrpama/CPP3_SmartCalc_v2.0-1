#include "Model.h"

namespace s21 {

// Function to check if a character is a digit
bool isDigit(char ch) {
  return std::isdigit(ch);
}

// Function to convert a string to a double
double stringToDouble(const std::string& str) {
  return std::stod(str);
}

// Function to parse the input string and return the parsed expression
CalculationModel::list_type CalculationModel::parser(const std::string& input_string) {
  list_type parsed_expression;
  for (size_t i = 0; i < input_string.length(); i++) {
    char ch = input_string[i];

    if (isDigit(ch) || ch == '.') {
      std::string number_str;
      size_t j = i;

      while (isDigit(input_string[j]) || input_string[j] == '.') {
        number_str += input_string[j];
        j++;
      }

      double number = stringToDouble(number_str);
      token number_token = {number, number_or_x, ""};
      parsed_expression.push_back(number_token);
      i = j - 1;
    }
    else {
      processOperator(ch);
    }
  }

  return parsed_expression;
}

// Function to process operators and push them into the parsed expression
void CalculationModel::processOperator(char ch) {
  if (ch == '+') {
    if (normal_str.empty() || normal_str.back() == '(') {
      Push(normal_str, zero);
    }
    Push(normal_str, add);
  }
  else if (ch == '-') {
    if (normal_str.empty() || normal_str.back() == '(') {
      Push(normal_str, zero);
    }
    Push(normal_str, sub);
  }
  else if (ch == '*') {
    Push(normal_str, mul);
  }
  else if (ch == '/') {
    Push(normal_str, divi);
  }
  else if (ch == '^') {
    Push(normal_str, degr);
  }
  else if (ch == '(') {
    if (!normal_str.empty() && normal_str.back() == ')') {
      Push(normal_str, mul);
    }
    Push(normal_str, opbr);
  }
  else if (ch == ')') {
    Push(normal_str, clbr);
  }
  else {
    processOtherOperators(ch);
  }
}

// Function to process other operators and push them into the parsed expression
void CalculationModel::processOtherOperators(char ch) {
  std::string str = input_string.substr(i);
  if (str.compare(0, 3, "mod") == 0) {
    Push(normal_str, mod);
  }
  else if (str.compare(0, 3, "sin") == 0 && str[3] != 'a') {
    Push(normal_str, sinu);
  }
  else if (str.compare(0, 3, "cos") == 0 && str[3] != 'a') {
    Push(normal_str, cosi);
  }
  else if (str.compare(0, 3, "tan") == 0 && str[3] != 'a') {
    Push(normal_str, tang);
  }
  else if (str.compare(0, 3, "log") == 0) {
    Push(normal_str, loga);
  }
  else if (str.compare(0, 2, "ln") == 0) {
    Push(normal_str, lna);
  }
  else if (str.compare(0, 4, "asin") == 0) {
    Push(normal_str, asinu);
  }
  else if (str.compare(0, 4, "acos") == 0) {
    Push(normal_str, acosn);
  }
  else if (str.compare(0, 4, "atan") == 0) {
    Push(normal_str, atang);
  }
  else if (str.compare(0, 4, "sqrt") == 0) {
    Push(normal_str, squarert);
  }
  else if (ch == 'x' || ch == 'X') {
    Push(normal_str, x);
  }
}

CalculationModel::stack_type CalculationModel::polishParser(list_type input_list) {
    stack_type polish_stack;

    return polish_stack;
}

void CalculationModel::calculator(stack_type polish_stack) {

}

bool CalculationModel::isDigit() {

}

bool CalculationModel::isExpression() {

}

bool CalculationModel::isFunc() {

}

bool CalculationModel::isOpenBracket() {

}

bool CalculationModel::isCloseBracket() {

}

void CalculationModel::reset()
{
}

double CalculationModel::getData()
{
    return answer;
}

}
