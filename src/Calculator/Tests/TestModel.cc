#include <gtest/gtest.h>
#include "../Model/Model.h"

using namespace s21;
// Positive test case for IsDigit function
TEST(CalculationModelTest, IsDigit_Positive) {
  CalculationModel model;
  ASSERT_TRUE(model.IsDigit('5'));
  ASSERT_TRUE(model.IsDigit('0'));
  ASSERT_TRUE(model.IsDigit('9'));
}

// Negative test case for IsDigit function
TEST(CalculationModelTest, IsDigit_Negative) {
  CalculationModel model;
  ASSERT_FALSE(model.IsDigit('a'));
  ASSERT_FALSE(model.IsDigit('.'));
  ASSERT_FALSE(model.IsDigit('-'));
}

// Positive test case for IsDigit function
TEST(CalculationModelTest, IsDigitToken_Positive) {
  CalculationModel model;
  token five{5, numberOrX, s21::numberType, "5"};
  token four{4, numberOrX, s21::numberType, "4"};
  token three{4, numberOrX, s21::numberType, "4"};
  ASSERT_TRUE(model.IsNumber(five));
  ASSERT_TRUE(model.IsNumber(four));
  ASSERT_TRUE(model.IsNumber(three));
}

// Negative test case for IsDigit function
TEST(CalculationModelTest, IsDigitToken_Negative) {
  CalculationModel model;
  ASSERT_FALSE(model.IsNumber(token{0.0, addSub, s21::addition, "+"}));
  ASSERT_FALSE(model.IsNumber(token{0.0, addSub, s21::subtraction, "-"}));
  ASSERT_FALSE(model.IsNumber(token{0.0, addSub, s21::multiplication, "*"}));
}

// Positive test case for IsDigit function
TEST(CalculationModelTest, IsFunction_Positive) {
  CalculationModel model;
  ASSERT_TRUE(model.IsExpression(token{0.0, s21::addSub, s21::addition, "+"}));
  ASSERT_TRUE(model.IsExpression(token{0.0, s21::addSub, s21::subtraction, "-"}));
  ASSERT_TRUE(model.IsExpression(token{0.0, s21::mulDivMod, s21::multiplication, "*"}));
}

// Negative test case for IsDigit function
TEST(CalculationModelTest, IsFunction_Negative) {
  CalculationModel model;
  token five{5, s21::numberOrX, s21::numberType, "5"};
  token four{4, s21::numberOrX, s21::numberType, "4"};
  token three{4, s21::numberOrX, s21::numberType, "4"};
  ASSERT_FALSE(model.IsExpression(five));
  ASSERT_FALSE(model.IsExpression(four));
  ASSERT_FALSE(model.IsExpression(three));
}

// Positive test case for StringToDouble function
TEST(CalculationModelTest, StringToDouble_Positive) {
  CalculationModel model;
  double result = model.StringToDouble("3.14");
  ASSERT_DOUBLE_EQ(result, 3.14);
}

// Negative test case for StringToDouble function
TEST(CalculationModelTest, StringToDouble_Negative) {
  CalculationModel model;
  EXPECT_ANY_THROW(model.StringToDouble("abc"));
}

// Positive test case for Parser function
TEST(CalculationModelTest, Parser_Positive) {
  CalculationModel model;
  model.Parser("2+3*4");
  CalculationModel::list_type parsedList = model.GetParsedExpression();
  CalculationModel::list_type list;
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(model.addToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(model.mulToken);
  list.push_back(token{4, numberOrX, s21::numberType, "4"});

  EXPECT_TRUE(parsedList == list);
}

TEST(CalculationModelTest, Parser_Positive_Unary_Plus)
{
  CalculationModel model;
  std::string inputString = "+1+2*3";
  
  // Call the Parser function
  model.Parser(inputString);
  
  CalculationModel::list_type parsedList = model.GetParsedExpression();
  // Assert the expected parsed expression
  CalculationModel::list_type list;
  list.push_back(model.zeroToken);
  list.push_back(model.addToken);
  list.push_back(token{1, numberOrX, s21::numberType, "1"});
  list.push_back(model.addToken);
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(model.mulToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});

  EXPECT_TRUE(parsedList == list);
}

TEST(CalculationModelTest, Parser_Positive_Unary_Minus)
{
  CalculationModel model;
  std::string inputString = "-1+2*3";
  
  // Call the Parser function
  model.Parser(inputString);
  
  CalculationModel::list_type parsedList = model.GetParsedExpression();
  // Assert the expected parsed expression
  CalculationModel::list_type list;
  list.push_back(model.zeroToken);
  list.push_back(model.subToken);
  list.push_back(token{1, numberOrX, s21::numberType, "1"});
  list.push_back(model.addToken);
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(model.mulToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});

  EXPECT_TRUE(parsedList == list);
}

TEST(CalculationModelTest, Parser_Positive_Other_Operators)
{
  CalculationModel model;
  std::string inputString = "(1/2^3)(3mod4)";
  
  // Call the Parser function
  model.Parser(inputString);
  
  CalculationModel::list_type parsedList = model.GetParsedExpression();
  // Assert the expected parsed expression
  CalculationModel::list_type list;
  list.push_back(model.opbrToken);
  list.push_back(token{1, numberOrX, s21::numberType, "1"});
  list.push_back(model.divToken);
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(model.powToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(model.clbrToken);
  list.push_back(model.mulToken);
  list.push_back(model.opbrToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(model.modToken);
  list.push_back(token{4, numberOrX, s21::numberType, "4"});
  list.push_back(model.clbrToken);

  std::cout << "list" << std::endl;
  for (const auto& element : list)
  {
    std::cout << element.strValue << " ";
  }
  std::cout << std::endl;

  std::cout << "parsed list" << std::endl;
  for (const auto& element : parsedList)
  {
    std::cout << element.strValue << " ";
  }
  std::cout << std::endl;

  EXPECT_TRUE(parsedList == list);
}

// Positive test case for PolishParser function
TEST(CalculationModelTest, PolishParser_Positive) {
  CalculationModel model;
  model.Parser("2+3*4");
  model.PolishParser();
  CalculationModel::list_type result = model.GetPolishStack();
  CalculationModel::list_type trueResult;
  trueResult.push_front(model.addToken);
  trueResult.push_front(model.mulToken);
  trueResult.push_front(token{4, numberOrX, s21::numberType, "4"});
  trueResult.push_front(token{3, numberOrX, s21::numberType, "3"});
  trueResult.push_front(token{2, numberOrX, s21::numberType, "2"});
  EXPECT_TRUE(trueResult == result);
}

// Positive test case for Calculator function
TEST(CalculationModelTest, Calculator_Positive) {
  CalculationModel model;
  CalculationModel::list_type list;
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(token{NAN, addSub, s21::addition,"+"});
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(token{NAN, mulDivMod, s21::multiplication, "*"});
  list.push_back(token{4, numberOrX, s21::numberType, "4"});
  model.Parser("2+3*4");
  model.PolishParser();
  model.Calculator();
  double result = model.GetDoubleAnswer();
  EXPECT_DOUBLE_EQ(result, 14.0);
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest)
{
  CalculationModel model;
  std::string inputString = "2+3*4";
  std::string expectedOutput = "14.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Negative test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_NegativeTest)
{
  CalculationModel model;
  std::string inputString = "2+3*";  // Invalid expression
  std::string expectedOutput = "Validation error";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_TRUE(model.GetError());
}
