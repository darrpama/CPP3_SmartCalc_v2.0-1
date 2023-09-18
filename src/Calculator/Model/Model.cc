#include "Model.h"

namespace s21 {

bool Model::IsDigit(char ch) const { return std::isdigit(ch); }

double Model::StringToDouble(const std::string &str) const {
  return std::stod(str);
}

std::string Model::CalculateExpression(const std::string &inputString) {
  Reset();
  try {
    validator_.IsNotCorrect(inputString);
    Parser(inputString);
    PolishParser();
    Calculator();
    SetStrAnswer(answer_);
  } catch (const std::exception &e) {
    // std::cerr << e.what() << '\n';
    SetStrAnswer(e);
    SetError(true);
  }
  return GetStringAnswer();
}

void Model::Parser(const std::string &inputString) {
  for (size_t i = 0; i < inputString.length(); i++) {
    const char ch = inputString[i];
    if (IsDigit(ch) || ch == '.') {
      std::string numberStr;
      size_t j = i;
      while (IsDigit(inputString[j]) || inputString[j] == '.') {
        numberStr += inputString[j];
        if (inputString[j + 1] == 'e') {
          numberStr += 'e';
          j++;
        }
        if (inputString[j] == 'e' && inputString[j + 1] == '+') {
          numberStr += '+';
          j++;
        }
        if (inputString[j] == 'e' && inputString[j + 1] == '-') {
          numberStr += '-';
          j++;
        }
        j++;
      }
      const double numberValue = StringToDouble(numberStr);
      const token numberToken = {numberValue, numberOrX, numberType, numberStr};
      parsedExpression_.push_back(numberToken);
      i = j - 1;
    } else {
      ProcessOperator(ch);
      ProcessOtherOperators(ch, i, inputString);
    }
  }
}

void Model::ProcessOperator(const char ch) {
  if (ch == '+') {
    if (parsedExpression_.empty() || parsedExpression_.back().strValue == "(") {
      parsedExpression_.push_back(zeroToken);
    }
    parsedExpression_.push_back(addToken);
  } else if (ch == '-') {
    if (parsedExpression_.empty() || parsedExpression_.back().strValue == "(") {
      parsedExpression_.push_back(zeroToken);
    }
    parsedExpression_.push_back(subToken);
  } else if (ch == '*') {
    parsedExpression_.push_back(mulToken);
  } else if (ch == '/') {
    parsedExpression_.push_back(divToken);
  } else if (ch == '^') {
    parsedExpression_.push_back(powToken);
  } else if (ch == '(') {
    if (!parsedExpression_.empty() &&
        parsedExpression_.back().strValue == ")") {
      parsedExpression_.push_back(mulToken);
    }
    parsedExpression_.push_back(opbrToken);
  } else if (ch == ')') {
    parsedExpression_.push_back(clbrToken);
  }
}

void Model::ProcessOtherOperators(const char ch, size_t &i,
                                  const std::string &inputString) {
  const std::string str = inputString.substr(i);
  if (str.compare(0, 3, "mod") == 0) {
    parsedExpression_.push_back(modToken);
    i += 2;
  } else if (str.compare(0, 4, "asin") == 0) {
    parsedExpression_.push_back(asinToken);
    i += 3;
  } else if (str.compare(0, 4, "acos") == 0) {
    parsedExpression_.push_back(acosToken);
    i += 3;
  } else if (str.compare(0, 4, "atan") == 0) {
    parsedExpression_.push_back(atanToken);
    i += 3;
  } else if (str.compare(0, 3, "sin") == 0) {
    parsedExpression_.push_back(sinToken);
  } else if (str.compare(0, 3, "cos") == 0) {
    parsedExpression_.push_back(cosToken);
  } else if (str.compare(0, 3, "tan") == 0) {
    parsedExpression_.push_back(tanToken);
  } else if (str.compare(0, 3, "log") == 0) {
    parsedExpression_.push_back(logToken);
  } else if (str.compare(0, 2, "ln") == 0) {
    parsedExpression_.push_back(lnToken);
  } else if (str.compare(0, 4, "sqrt") == 0) {
    parsedExpression_.push_back(sqrtToken);
  } else if (ch == 'x' || ch == 'X') {
    parsedExpression_.push_back(xToken);
  }
}

void Model::PolishParser() {
  stack_type tempStack;
  for (auto it = parsedExpression_.begin(); it != parsedExpression_.end();
       it++) {
    if (IsNumber(*it)) {
      polishStack_.push_back(*it);
    } else if (IsOpenBracket(*it)) {
      tempStack.push(*it);
    } else if (IsCloseBracket(*it)) {
      if (!tempStack.empty()) {
        while (!IsOpenBracket(tempStack.top())) {
          if (!tempStack.empty()) {
            polishStack_.push_back(tempStack.top());
            tempStack.pop();
          } else {
            throw std::invalid_argument("Received pair of brackets");
          }
        }
      } else {
        throw std::invalid_argument("Received pair of brackets");
      }
      tempStack.pop();
    } else if (IsExpression(*it) || IsFunction(*it)) {
      while (!tempStack.empty()) {
        if ((tempStack.top().type != token_type::openBracket ||
             tempStack.top().type != token_type::closeBracket) &&
            ((it->priority < tempStack.top().priority) ||
             (it->priority == tempStack.top().priority &&
              it->type == token_type::power))) {
          polishStack_.push_back(tempStack.top());
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
        polishStack_.push_back(tempStack.top());
        tempStack.pop();
      }
    }
  }
}

void Model::Calculator() {
  list_type temp;
  try {
    while (!polishStack_.empty()) {
      token data = polishStack_.front();
      if (IsNumber(data)) {
        temp.push_back(data);
        polishStack_.pop_front();
      } else if (IsExpression(data)) {
        token operand1 = temp.back();
        temp.pop_back();
        token operand2 = temp.back();
        temp.pop_back();
        token result = DoExpression(operand2, operand1, data);
        temp.push_back(result);
        polishStack_.pop_front();
      } else if (IsFunction(data)) {
        token operand = temp.back();
        temp.pop_back();
        token result = DoFunction(operand, data);
        temp.push_back(result);
        polishStack_.pop_front();
      }
    }
    SetAnswer(temp.front());
  } catch (const std::exception &e) {
    throw std::invalid_argument("Invalid expression");
  }
}

bool Model::IsNumber(const token &token) const {
  return token.type == numberType;
}

bool Model::IsExpression(const token &token) const {
  return (token.type == addition || token.type == subtraction ||
          token.type == multiplication || token.type == division ||
          token.type == power || token.type == modulo);
}

bool Model::IsFunction(const token &token) const {
  return (token.type == naturalLogarithm || token.type == sinus ||
          token.type == cosinus || token.type == tangens ||
          token.type == decimalLogarithm || token.type == arcsin ||
          token.type == arccos || token.type == arctan ||
          token.type == squareRoot);
}

bool Model::IsOpenBracket(const token &token) const {
  return (token.type == openBracket);
}

bool Model::IsCloseBracket(const token &token) const {
  return (token.type == closeBracket);
}

void Model::Reset() {
  parsedExpression_.clear();
  polishStack_.clear();
  answer_ = {};
  error_ = false;
}

Model::list_type Model::GetParsedExpression() const {
  return parsedExpression_;
}

Model::list_type Model::GetPolishStack() const { return polishStack_; }

void Model::SetAnswer(token answer_) { this->answer_ = answer_.value; }

token Model::DoExpression(token operand1, token operand2, token expression) {
  double result = 0;
  token dresult;
  if (IsExpression(expression)) {
    if (expression.type == addition) {
      result = operand1.value + operand2.value;
    } else if (expression.type == subtraction) {
      result = operand1.value - operand2.value;
    } else if (expression.type == multiplication) {
      result = operand1.value * operand2.value;
    } else if (expression.type == division) {
      if (operand2.value == 0) {
        throw std::invalid_argument("Division by zero");
      } else {
        result = operand1.value / operand2.value;
      }
    } else if (expression.type == power) {
      result = pow(operand1.value, operand2.value);
    } else if (expression.type == modulo) {
      if (operand2.value == 0) {
        throw std::invalid_argument("Division by zero");
      } else {
        result = fmod(operand1.value, operand2.value);
      }
    }
  }
  dresult.value = result;
  dresult.priority = priority_type::numberOrX;
  dresult.type = token_type::numberType;
  return dresult;
}

token Model::DoFunction(token operand, token function) {
  double result = 0;
  token dresult;
  if (IsFunction(function)) {
    if (function.type == sinus) {
      result = sin(operand.value);
    } else if (function.type == cosinus) {
      result = cos(operand.value);
    } else if (function.type == tangens) {
      result = tan(operand.value);
    } else if (function.type == decimalLogarithm) {
      result = log10(operand.value);
    } else if (function.type == naturalLogarithm) {
      result = log(operand.value);
    } else if (function.type == arcsin) {
      result = asin(operand.value);
    } else if (function.type == arccos) {
      result = acos(operand.value);
    } else if (function.type == arctan) {
      result = atan(operand.value);
    } else if (function.type == squareRoot) {
      result = sqrt(operand.value);
    }
  }
  dresult.value = result;
  dresult.priority = priority_type::numberOrX;
  dresult.type = token_type::numberType;
  return dresult;
}

double Model::GetDoubleAnswer() const { return answer_; }

std::string Model::GetStringAnswer() const { return stringAnswer_; }

void Model::SetStrAnswer(const double answer_) {
  this->stringAnswer_ = std::to_string(answer_);
}

void Model::SetStrAnswer(const std::exception &exception) {
  this->stringAnswer_ = exception.what();
}

bool Model::GetError() const { return error_; }

std::pair<std::vector<double>, std::vector<double>> Model::GetGraph(
    const std::string &inputString, double xMin, double xMax) {
  std::vector<double> xVector;
  std::vector<double> yVector;
  const size_t numSamples = 1000;
  double step = (xMax - xMin) / numSamples;

  if (step <= 0) {
    SetError(true);
    throw std::invalid_argument("X values is wrong");
  }

  for (size_t i = 0; i < numSamples; i++) {
    Reset();
    std::string tmpString(inputString);
    double xValue = xMin + i * step;
    xVector.push_back(xValue);
    std::string numberString = std::to_string(xValue);

    size_t found = tmpString.find('x');
    while (found != std::string::npos) {
      tmpString.replace(found, 1, "(" + numberString + ")");
      found = tmpString.find('x', found + numberString.length());
    }

    validator_.IsNotCorrect(tmpString);
    Parser(tmpString);
    PolishParser();
    Calculator();
    yVector.push_back(GetDoubleAnswer());
  }

  return std::make_pair(xVector, yVector);
}

void Model::SetError(bool NewError) { error_ = NewError; }

}  // namespace s21
