#include "Model.h"
#include "SmartCalculator/s21_calculator.h"

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

      const double numberValue = StringToDouble(numberStr);
      const token numberToken = {numberValue, numberOrX, numberType, numberStr};
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

void CalculationModel::PolishParser() {
  stack_type tempStack;
  for (auto it = parsedExpression.begin(); it != parsedExpression.end(); it++) {
    if (IsDigit(*it)) {
      polishStack.push_back(*it);
    }
    else if (IsOpenBracket(*it)) {
      tempStack.push(*it);
    }
    else if (IsCloseBracket(*it)) {
      if (!tempStack.empty()) {
        while (!IsOpenBracket(tempStack.top())) {
          if (!tempStack.empty()) {
            polishStack.push_back(tempStack.top());
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
          polishStack.push_back(tempStack.top());
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
        polishStack.push_back(tempStack.top());
        tempStack.pop();
      }
    }
  }
}

void CalculationModel::Calculator() {
  token answer;
  list_type temp;
  while (!polishStack.empty()) {
    token data = polishStack.front();
    if (IsDigit(data)) {
      temp.push_back(data);
      polishStack.pop_front();
    }
    else if (IsExpression(data)) {
      token operand1 = temp.back();
      temp.pop_back();
      token operand2 = temp.back();
      temp.pop_back();
      token answer = DoOper(operand1, operand2, data);
      temp.push_back(answer);
    }
    else if (IsFunction(data)) {
      token operand = temp.back();
      temp.pop_back();
      token answer = DoFunc(operand, data);
      temp.push_back(answer);
    }
  }
  SetAnswer(answer);
}

bool CalculationModel::IsDigit(const token& token) const {
  return token.type == numberType;
}

bool CalculationModel::IsExpression(const token& token) const {
  return (token.type == addition ||
          token.type == substraction ||
          token.type == multiplication ||
          token.type == division ||
          token.type == power ||
          token.type == modulo);
}

bool CalculationModel::IsFunction(const token& token) const {
  const std::string str = token.strValue;
  return (token.type == naturalLogarithm ||
          token.type == sinus ||
          token.type == cosinus ||
          token.type == tangens ||
          token.type == decimalLogarithm ||
          token.type == arcsin ||
          token.type == arccos ||
          token.type == arctan ||
          token.type == squareRoot);
}

bool CalculationModel::IsOpenBracket(const token& token) const {
  return (token.type == openBracket);
}

bool CalculationModel::IsCloseBracket(const token& token) const {
  return (token.type == closeBracket);
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

CalculationModel::list_type CalculationModel::GetPolishStack() const {
  return polishStack;
}

void CalculationModel::SetAnswer(token answer) {
  this->answer = answer.value;
}

void CalculationModel::PrintParsedExpression() const {
  for (auto it = parsedExpression.begin(); it != parsedExpression.end(); ++it) {
    std::cout << it->strValue;
  }
  std::cout << std::endl;
}

void CalculationModel::PrintPolishStack() const {
  for (auto it = polishStack.begin(); it != polishStack.end(); ++it) {
    std::cout << it->strValue;
    std::cout << std::endl;
  }
}

token CalculationModel::DoOper(token op1, token op2, token expr) {
  double answer = 0;
  token danswer;
  if (IsExpression(expr)) {
    if (expr.type == addition) {
      answer = op1.value + op2.value;
    } else if (expr.type == substraction) {
      answer = op1.value - op2.value;
    } else if (expr.type == multiplication) {
      answer = op1.value * op2.value;
    } else if (expr.type == division) {
      if (op2.value == 0) {
        throw std::invalid_argument("Division by zero");
      } else {
        answer = op1.value / op2.value;
      }
    } else if (expr.type == power) {
      answer = pow(op1.value, op2.value);
    } else if (expr.type == modulo) {
      if (op2.value == 0) {
        throw std::invalid_argument("Division by zero");
      } else {
        answer = fmod(op1.value, op2.value);
      }
    }
  }
  danswer.value = answer;
  return danswer;
}

token CalculationModel::DoFunc(token operand, token function) {
  double answer = 0;
  token danswer;
  if (IsFunction(function)) {
    if (function.type == sinus) {
      answer = sin(operand.value);
    } else if (function.type == cosinus) {
      answer = cos(operand.value);
    } else if (function.type == tangens) {
      answer = tan(operand.value);
    } else if (function.type == decimalLogarithm) {
      answer = log(operand.value);
    } else if (function.type == naturalLogarithm) {
      answer = log(operand.value);
    } else if (function.type == arcsin) {
      answer = asin(operand.value);
    } else if (function.type == arccos) {
      answer = acos(operand.value);
    } else if (function.type == arctan) {
      answer = atan(operand.value);
    } else if (function.type == squareRoot) {
      answer = sqrt(operand.value);
    }
  }
  danswer.value = answer;
  return danswer;
}

}
