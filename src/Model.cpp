#include "Model.h"

namespace s21 {

// Function to check if a character is a digit
bool CalculationModel::isDigit(char ch) {
  return std::isdigit(ch);
}

// Function to convert a string to a double
double CalculationModel::stringToDouble(const std::string& str) {
  return std::stod(str);
}

// Function to parse the input string and return the parsed expression
void CalculationModel::parser(const std::string& input_string) {
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
      token number_token = {number, number_or_x, number_str};
      parsed_expression.push_back(number_token);
      i = j - 1;
    }
    else {
      processOperator(ch);
      processOtherOperators(ch, i, input_string);
    }
  }
}

// Function to process operators and push them into the parsed expression
void CalculationModel::processOperator(char ch) {
  if (ch == '+') {
    if (parsed_expression.empty() || parsed_expression.back().str_value == "(") {
      parsed_expression.push_back(zero_token);
    }
    parsed_expression.push_back(add_token);
  }
  else if (ch == '-') {
    if (parsed_expression.empty() || parsed_expression.back().str_value == "(") {
      parsed_expression.push_back(zero_token);
    }
    parsed_expression.push_back(add_token);
  }
  else if (ch == '*') {
    parsed_expression.push_back(mul_token);
  }
  else if (ch == '/') {
    parsed_expression.push_back(div_token);
  }
  else if (ch == '^') {
    parsed_expression.push_back(pow_token);
  }
  else if (ch == '(') {
    if (!parsed_expression.empty() && parsed_expression.back().str_value == ")") {
      parsed_expression.push_back(mul_token);
    }
    parsed_expression.push_back(opbr_token);
  }
  else if (ch == ')') {
    parsed_expression.push_back(clbr_token);
  }
}

// Function to process other operators and push them into the parsed expression
void CalculationModel::processOtherOperators(char ch, size_t& i, string_type input_string) {
  std::string str = input_string.substr(i);
  if (str.compare(0, 3, "mod") == 0) {
    parsed_expression.push_back(mod_token);
  }
  else if (str.compare(0, 4, "asin") == 0) {
    parsed_expression.push_back(asin_token);
    i += 3;
  }
  else if (str.compare(0, 4, "acos") == 0) {
    parsed_expression.push_back(acos_token);
    i += 3;
  }
  else if (str.compare(0, 4, "atan") == 0) {
    parsed_expression.push_back(atan_token);
    i += 3;
  }
  else if (str.compare(0, 3, "sin") == 0) {
    parsed_expression.push_back(sin_token);
  }
  else if (str.compare(0, 3, "cos") == 0) {
    parsed_expression.push_back(cos_token);
  }
  else if (str.compare(0, 3, "tan") == 0) {
    parsed_expression.push_back(tan_token);
  }
  else if (str.compare(0, 3, "log") == 0) {
    parsed_expression.push_back(log_token);
  }
  else if (str.compare(0, 2, "ln") == 0) {
    parsed_expression.push_back(ln_token);
  }
  else if (str.compare(0, 4, "sqrt") == 0) {
    parsed_expression.push_back(sqrt_token);
  }
  else if (ch == 'x' || ch == 'X') {
    parsed_expression.push_back(x_token);
  }
}

CalculationModel::stack_type CalculationModel::polishParser(list_type input_list) {
  stack_type polish_stack;
  list_type tmp(input_list);

  return polish_stack;
}

void CalculationModel::calculator(stack_type polish_stack) {
  stack_type tmp(polish_stack);
}

bool CalculationModel::isExpression() {
  return true;
}

bool CalculationModel::isFunc() {
  return true;
}

bool CalculationModel::isOpenBracket() {
  return true;
}

bool CalculationModel::isCloseBracket() {
  return true;
}

void CalculationModel::reset()
{
}

double CalculationModel::getData()
{
  return answer;
}

void CalculationModel::printParsedExpression()
{
  for (auto it = parsed_expression.begin(); it != parsed_expression.end(); ++it) {
    std::cout << it->str_value;
  }
  std::cout << std::endl;
}

}
