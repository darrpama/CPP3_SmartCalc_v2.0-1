#include "Model.h"

namespace s21 {

// Function to check if a character is a digit
bool CalculationModel::IsDigit(char ch) const
{
  return std::isdigit(ch);
}

// Function to convert a string to a double
double CalculationModel::StringToDouble(const std::string &str) const
{
  return std::stod(str);
}

// Main function to calculate expression
std::string CalculationModel::CaclulateExpression(const std::string &inputString)
{
  Reset();
  try
  {
    Parser(inputString);
    PolishParser();
    Calculator();
    SetStrAnswer(answer);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    SetStrAnswer(e);
    SetError(true);
  }
  return GetStringAnswer();
}

// Function to parse the input string and return the parsed expression
void CalculationModel::Parser(const std::string &inputString)
{
  for (size_t i = 0; i < inputString.length(); i++)
  {
    const char ch = inputString[i];

    if (IsDigit(ch) || ch == '.')
    {
      std::string numberStr;
      size_t j = i;

      while (IsDigit(inputString[j]) || inputString[j] == '.')
      {
        numberStr += inputString[j];
        j++;
      }

      const double numberValue = StringToDouble(numberStr);
      const token numberToken = {numberValue, numberOrX, numberType, numberStr};
      parsedExpression.push_back(numberToken);
      i = j - 1;
    }
    else
    {
      ProcessOperator(ch);
      ProcessOtherOperators(ch, i, inputString);
    }
  }
}

// Function to process operators and push them into the parsed expression
void CalculationModel::ProcessOperator(const char ch)
{
  if (ch == '+')
  {
    if (parsedExpression.empty() || parsedExpression.back().strValue == "(")
    {
      parsedExpression.push_back(zeroToken);
    }
    parsedExpression.push_back(addToken);
  }
  else if (ch == '-')
  {
    if (parsedExpression.empty() || parsedExpression.back().strValue == "(")
    {
      parsedExpression.push_back(zeroToken);
    }
    parsedExpression.push_back(subToken);
  }
  else if (ch == '*')
  {
    parsedExpression.push_back(mulToken);
  }
  else if (ch == '/')
  {
    parsedExpression.push_back(divToken);
  }
  else if (ch == '^')
  {
    parsedExpression.push_back(powToken);
  }
  else if (ch == '(')
  {
    if (!parsedExpression.empty() && parsedExpression.back().strValue == ")")
    {
      parsedExpression.push_back(mulToken);
    }
    parsedExpression.push_back(opbrToken);
  }
  else if (ch == ')')
  {
    parsedExpression.push_back(clbrToken);
  }
}

// Function to process other operators and push them into the parsed expression
void CalculationModel::ProcessOtherOperators(const char ch, size_t &i, const std::string &inputString)
{
  const std::string str = inputString.substr(i);
  if (str.compare(0, 3, "mod") == 0)
  {
    parsedExpression.push_back(modToken);
  }
  else if (str.compare(0, 4, "asin") == 0)
  {
    parsedExpression.push_back(asinToken);
    i += 3;
  }
  else if (str.compare(0, 4, "acos") == 0)
  {
    parsedExpression.push_back(acosToken);
    i += 3;
  }
  else if (str.compare(0, 4, "atan") == 0)
  {
    parsedExpression.push_back(atanToken);
    i += 3;
  }
  else if (str.compare(0, 3, "sin") == 0)
  {
    parsedExpression.push_back(sinToken);
  }
  else if (str.compare(0, 3, "cos") == 0)
  {
    parsedExpression.push_back(cosToken);
  }
  else if (str.compare(0, 3, "tan") == 0)
  {
    parsedExpression.push_back(tanToken);
  }
  else if (str.compare(0, 3, "log") == 0)
  {
    parsedExpression.push_back(logToken);
  }
  else if (str.compare(0, 2, "ln") == 0)
  {
    parsedExpression.push_back(lnToken);
  }
  else if (str.compare(0, 4, "sqrt") == 0)
  {
    parsedExpression.push_back(sqrtToken);
  }
  else if (ch == 'x' || ch == 'X')
  {
    parsedExpression.push_back(xToken);
  }
}

void CalculationModel::PolishParser()
{
  stack_type tempStack;
  for (auto it = parsedExpression.begin(); it != parsedExpression.end(); it++)
  {
    if (IsNumber(*it))
    {
      polishStack.push_back(*it);
    }
    else if (IsOpenBracket(*it))
    {
      tempStack.push(*it);
    }
    else if (IsCloseBracket(*it))
    {
      if (!tempStack.empty())
      {
        while (!IsOpenBracket(tempStack.top()))
        {
          if (!tempStack.empty())
          {
            polishStack.push_back(tempStack.top());
            tempStack.pop();
          }
          else
          {
            throw std::invalid_argument("Received pair of brackets");
            break;
          }
        }
      }
      else
      {
        throw std::invalid_argument("Received pair of brackets");
        break;
      }
      tempStack.pop();
    }
    else if (IsExpression(*it) || IsFunction(*it))
    {
      while (!tempStack.empty())
      {
        if (it->priority <= tempStack.top().priority)
        {
          polishStack.push_back(tempStack.top());
          tempStack.pop();
        }
        else
        {
          break;
        }
      }
      tempStack.push(*it);
    }
  }
  if (!tempStack.empty())
  {
    if (IsOpenBracket(tempStack.top()) || IsCloseBracket(tempStack.top()))
    {
      throw std::invalid_argument("There is extra bracket in expression");
    }
    else
    {
      while (!tempStack.empty())
      {
        polishStack.push_back(tempStack.top());
        tempStack.pop();
      }
    }
  }
}

void CalculationModel::Calculator()
{
  list_type temp;
  while (!polishStack.empty())
  {
    token data = polishStack.front();
    if (IsNumber(data))
    {
      temp.push_back(data);
      polishStack.pop_front();
    }
    else if (IsExpression(data))
    {
      token operand1 = temp.back();
      temp.pop_back();
      token operand2 = temp.back();
      temp.pop_back();
      token answer = DoExpression(operand1, operand2, data);
      temp.push_back(answer);
      polishStack.pop_front();
    }
    else if (IsFunction(data))
    {
      token operand = temp.back();
      temp.pop_back();
      token answer = DoFunction(operand, data);
      temp.push_back(answer);
      polishStack.pop_front();
    }
  }
  SetAnswer(temp.front());
}

bool CalculationModel::IsNumber(const token &token) const
{
  return token.type == numberType;
}

bool CalculationModel::IsExpression(const token &token) const
{
  return (token.type == addition ||
          token.type == subtraction ||
          token.type == multiplication ||
          token.type == division ||
          token.type == power ||
          token.type == modulo);
}

bool CalculationModel::IsFunction(const token &token) const
{
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

bool CalculationModel::IsOpenBracket(const token &token) const
{
  return (token.type == openBracket);
}

bool CalculationModel::IsCloseBracket(const token &token) const
{
  return (token.type == closeBracket);
}

void CalculationModel::Reset()
{
  parsedExpression.clear();
  polishStack.clear();
  answer = {};
  error = false;
}


CalculationModel::list_type CalculationModel::GetParsedExpression() const
{
  return parsedExpression;
}

CalculationModel::list_type CalculationModel::GetPolishStack() const
{
  return polishStack;
}

void CalculationModel::SetAnswer(token answer)
{
  this->answer = answer.value;
}

void CalculationModel::PrintParsedExpression() const
{
  for (auto it = parsedExpression.begin(); it != parsedExpression.end(); ++it)
  {
    std::cout << it->strValue;
  }
  std::cout << std::endl;
}

void CalculationModel::PrintPolishStack() const
{
  for (auto it = polishStack.begin(); it != polishStack.end(); ++it)
  {
    std::cout << it->strValue;
    std::cout << std::endl;
  }
}

token CalculationModel::DoExpression(token operand1, token operand2, token expression)
{
  double answer = 0;
  token danswer;
  if (IsExpression(expression))
  {
    if (expression.type == addition)
    {
      answer = operand1.value + operand2.value;
    }
    else if (expression.type == subtraction)
    {
      answer = operand1.value - operand2.value;
    }
    else if (expression.type == multiplication)
    {
      answer = operand1.value * operand2.value;
    }
    else if (expression.type == division)
    {
      if (operand2.value == 0)
      {
        throw std::invalid_argument("Division by zero");
      }
      else
      {
        answer = operand1.value / operand2.value;
      }
    }
    else if (expression.type == power)
    {
      answer = pow(operand1.value, operand2.value);
    }
    else if (expression.type == modulo)
    {
      if (operand2.value == 0)
      {
        throw std::invalid_argument("Division by zero");
      }
      else
      {
        answer = fmod(operand1.value, operand2.value);
      }
    }
  }
  danswer.value = answer;
  return danswer;
}

token CalculationModel::DoFunction(token operand, token function)
{
  double answer = 0;
  token danswer;
  if (IsFunction(function))
  {
    if (function.type == sinus)
    {
      answer = sin(operand.value);
    }
    else if (function.type == cosinus)
    {
      answer = cos(operand.value);
    }
    else if (function.type == tangens)
    {
      answer = tan(operand.value);
    }
    else if (function.type == decimalLogarithm)
    {
      answer = log10(operand.value);
    }
    else if (function.type == naturalLogarithm)
    {
      answer = log(operand.value);
    }
    else if (function.type == arcsin)
    {
      answer = asin(operand.value);
    }
    else if (function.type == arccos)
    {
      answer = acos(operand.value);
    }
    else if (function.type == arctan)
    {
      answer = atan(operand.value);
    }
    else if (function.type == squareRoot)
    {
      answer = sqrt(operand.value);
    }
  }
  danswer.value = answer;
  return danswer;
}

double CalculationModel::GetDoubleAnswer() const
{
  return answer;
}

std::string CalculationModel::GetStringAnswer() const
{
  return stringAnswer;
}

void s21::CalculationModel::SetStrAnswer(const std::string &answer)
{
  this->stringAnswer = answer;
}

void CalculationModel::SetStrAnswer(const double answer)
{
  this->stringAnswer = std::to_string(answer);
}

void CalculationModel::SetStrAnswer(const std::exception &exception)
{
  this->stringAnswer = exception.what();
}

bool CalculationModel::GetError()
{
  return error;
}

std::pair<std::vector<double>, std::vector<double>> CalculationModel::GetGraph(std::string stdInputString, double xMin, double xMax)
{
  std::pair<std::vector<double>, std::vector<double>> answer;
  answer.first[0] = 1.0;
  answer.first[1] = 2.0;
  answer.second[0] = 1.0;
  answer.second[1] = 2.0;
  return answer;
}

void CalculationModel::SetError(bool NewError)
{
  error = NewError;
}

}  // namespace s21
