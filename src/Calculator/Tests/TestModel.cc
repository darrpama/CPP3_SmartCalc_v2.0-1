#include <gtest/gtest.h>
#include "../Model/Model.h"

using namespace s21;
// Positive test case for IsDigit function
TEST(CalculationModelTest, IsDigit_Positive) {
  Model model;
  ASSERT_TRUE(model.IsDigit('5'));
  ASSERT_TRUE(model.IsDigit('0'));
  ASSERT_TRUE(model.IsDigit('9'));
}

// Negative test case for IsDigit function
TEST(CalculationModelTest, IsDigit_Negative) {
  Model model;
  ASSERT_FALSE(model.IsDigit('a'));
  ASSERT_FALSE(model.IsDigit('.'));
  ASSERT_FALSE(model.IsDigit('-'));
}

// Positive test case for IsDigit function
TEST(CalculationModelTest, IsDigitToken_Positive) {
  Model model;
  token five{5, numberOrX, s21::numberType, "5"};
  token four{4, numberOrX, s21::numberType, "4"};
  token three{4, numberOrX, s21::numberType, "4"};
  ASSERT_TRUE(model.IsNumber(five));
  ASSERT_TRUE(model.IsNumber(four));
  ASSERT_TRUE(model.IsNumber(three));
}

// Negative test case for IsDigit function
TEST(CalculationModelTest, IsDigitToken_Negative) {
  Model model;
  ASSERT_FALSE(model.IsNumber(token{0.0, addSub, s21::addition, "+"}));
  ASSERT_FALSE(model.IsNumber(token{0.0, addSub, s21::subtraction, "-"}));
  ASSERT_FALSE(model.IsNumber(token{0.0, addSub, s21::multiplication, "*"}));
}

// Positive test case for IsDigit function
TEST(CalculationModelTest, IsFunction_Positive) {
  Model model;
  ASSERT_TRUE(model.IsExpression(token{0.0, s21::addSub, s21::addition, "+"}));
  ASSERT_TRUE(model.IsExpression(token{0.0, s21::addSub, s21::subtraction, "-"}));
  ASSERT_TRUE(model.IsExpression(token{0.0, s21::mulDivMod, s21::multiplication, "*"}));
}

// Negative test case for IsDigit function
TEST(CalculationModelTest, IsFunction_Negative) {
  Model model;
  token five{5, s21::numberOrX, s21::numberType, "5"};
  token four{4, s21::numberOrX, s21::numberType, "4"};
  token three{4, s21::numberOrX, s21::numberType, "4"};
  ASSERT_FALSE(model.IsExpression(five));
  ASSERT_FALSE(model.IsExpression(four));
  ASSERT_FALSE(model.IsExpression(three));
}

// Positive test case for StringToDouble function
TEST(CalculationModelTest, StringToDouble_Positive) {
  Model model;
  double result = model.StringToDouble("3.14");
  ASSERT_DOUBLE_EQ(result, 3.14);
}

// Negative test case for StringToDouble function
TEST(CalculationModelTest, StringToDouble_Negative) {
  Model model;
  EXPECT_ANY_THROW(model.StringToDouble("abc"));
}

// Positive test case for Parser function
TEST(CalculationModelTest, Parser_Positive) {
  Model model;
  model.Parser("2+3*4");
  Model::list_type parsedList = model.GetParsedExpression();
  Model::list_type list;
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(addToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(mulToken);
  list.push_back(token{4, numberOrX, s21::numberType, "4"});

  EXPECT_TRUE(parsedList == list);
}

TEST(CalculationModelTest, Parser_Positive_Unary_Plus)
{
  Model model;
  std::string inputString = "+1+2*3";
  
  // Call the Parser function
  model.Parser(inputString);
  
  Model::list_type parsedList = model.GetParsedExpression();
  // Assert the expected parsed expression
  Model::list_type list;
  list.push_back(zeroToken);
  list.push_back(addToken);
  list.push_back(token{1, numberOrX, s21::numberType, "1"});
  list.push_back(addToken);
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(mulToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});

  EXPECT_TRUE(parsedList == list);
}

TEST(CalculationModelTest, Parser_Positive_Unary_Minus)
{
  Model model;
  std::string inputString = "-1+2*3";
  
  // Call the Parser function
  model.Parser(inputString);
  
  Model::list_type parsedList = model.GetParsedExpression();
  // Assert the expected parsed expression
  Model::list_type list;
  list.push_back(zeroToken);
  list.push_back(subToken);
  list.push_back(token{1, numberOrX, s21::numberType, "1"});
  list.push_back(addToken);
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(mulToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});

  EXPECT_TRUE(parsedList == list);
}

TEST(CalculationModelTest, Parser_Positive_Other_Operators)
{
  Model model;
  std::string inputString = "(1/2^3)(3mod4)";
  
  // Call the Parser function
  model.Parser(inputString);
  
  Model::list_type parsedList = model.GetParsedExpression();
  // Assert the expected parsed expression
  Model::list_type list;
  list.push_back(opbrToken);
  list.push_back(token{1, numberOrX, s21::numberType, "1"});
  list.push_back(divToken);
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(powToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(clbrToken);
  list.push_back(mulToken);
  list.push_back(opbrToken);
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(modToken);
  list.push_back(token{4, numberOrX, s21::numberType, "4"});
  list.push_back(clbrToken);

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
  Model model;
  model.Parser("2+3*4");
  model.PolishParser();
  Model::list_type result = model.GetPolishStack();
  Model::list_type trueResult;
  trueResult.push_front(addToken);
  trueResult.push_front(mulToken);
  trueResult.push_front(token{4, numberOrX, s21::numberType, "4"});
  trueResult.push_front(token{3, numberOrX, s21::numberType, "3"});
  trueResult.push_front(token{2, numberOrX, s21::numberType, "2"});
  EXPECT_TRUE(trueResult == result);
}

// Positive test case for Calculator function
TEST(CalculationModelTest, Calculator_Positive) {
  Model model;
  Model::list_type list;
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
  Model model;
  std::string inputString = "2+3*4";
  std::string expectedOutput = "14.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_2)
{
  Model model;
  std::string inputString = "2+3*4e1";
  std::string expectedOutput = "122.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Negative test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_NegativeTest_2)
{
  Model model;
  std::string inputString = "2+3*4e.1";  // Invalid expression
  std::string expectedOutput = "Validation error";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_TRUE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_3)
{
  Model model;
  std::string inputString = "2+3*40e-1";
  std::string expectedOutput = "14.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_4)
{
  Model model;
  std::string inputString = "2+3*40e+1";
  std::string expectedOutput = "1202.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_5)
{
  Model model;
  std::string inputString = "2+asin(0)";
  std::string expectedOutput = "2.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_6)
{
  Model model;
  std::string inputString = "asin(0)+acos(1)";
  std::string expectedOutput = "0.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_7)
{
  Model model;
  std::string inputString = "atan(0)+log(1)";
  std::string expectedOutput = "0.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_8)
{
  Model model;
  std::string inputString = "sin(0)+cos(0)";
  std::string expectedOutput = "1.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_9)
{
  Model model;
  std::string inputString = "tan(0)+ln(1)+sqrt(4)";
  std::string expectedOutput = "2.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_10)
{
  Model model;
  std::string inputString = "((4/2))^4";
  std::string expectedOutput = "16.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_PositiveTest_11)
{
  Model model;
  std::string inputString = "((4/2))mod4";
  std::string expectedOutput = "2.000000";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_FALSE(model.GetError());
}

// Positive test case for CalculateExpression
TEST(CalculationModelTest, CalculateExpression_NegativeTest_11)
{
  Model model;
  std::string inputString = "(4/0)";
  std::string expectedOutput = "Invalid expression";

  std::string actualOutput = model.CalculateExpression(inputString);

  EXPECT_EQ(actualOutput, expectedOutput);
  EXPECT_TRUE(model.GetError());
}

TEST(ModelTest, PositiveTest) { 
  Model model; 
  std::string inputString = "x"; 
  double xMin = -5.0; 
  double xMax = 5.0; 
  std::pair<std::vector<double>, std::vector<double>> result = model.GetGraph(inputString, xMin, xMax); 
 
  EXPECT_EQ(result.first.size(), 1000); 
  EXPECT_EQ(result.second.size(), 1000); 
 
  EXPECT_NEAR(result.first[0], -5.0, 0.001); 
  EXPECT_NEAR(result.first[999], 4.99, 0.001); 
  EXPECT_NEAR(result.first[500], 0.0, 0.001); 
 
  EXPECT_NEAR(result.second[0], -5.0, 0.001); 
  EXPECT_NEAR(result.second[999], 4.99, 0.001); 
  EXPECT_NEAR(result.second[500], 0.0, 0.001); 
} 
 
TEST(ModelTest, NegativeTest) { 
  Model model; 
  std::string inputString = "-x-"; 
  EXPECT_ANY_THROW(model.GetGraph("-x-", 5.0, 0.0)); 
  EXPECT_ANY_THROW(model.GetGraph("-x-", -5.0, -5.0)); 
}  