#include <gtest/gtest.h>
#include "Model.h"

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
  // model.PrintParsedExpression();
  CalculationModel::list_type list;
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(token{NAN, addSub, s21::addition,"+"});
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(token{NAN, mulDivMod, s21::multiplication, "*"});
  list.push_back(token{4, numberOrX, s21::numberType, "4"});
  EXPECT_TRUE(parsedList == list);
}

// Positive test case for PolishParser function
TEST(CalculationModelTest, PolishParser_Positive) {
  CalculationModel model;
  CalculationModel::list_type list;
  list.push_back(token{2, numberOrX, s21::numberType, "2"});
  list.push_back(token{NAN, addSub, s21::addition,"+"});
  list.push_back(token{3, numberOrX, s21::numberType, "3"});
  list.push_back(token{NAN, mulDivMod, s21::multiplication, "*"});
  list.push_back(token{4, numberOrX, s21::numberType, "4"});
  CalculationModel::stack_type result = model.PolishParser(list);
  model.PrintPolishStack();
  EXPECT_TRUE(true);
}

// // Positive test case for Calculator function
// TEST(CalculationModelTest, Calculator_Positive) {
//   CalculationModel model;
//   CalculationModel::stack_type polishStack = { {1, CalculationModel::numberOrX, "1"}, {2, CalculationModel::numberOrX, "2"}, {3, CalculationModel::numberOrX, "3"} };
//   model.Calculator(polishStack);
//   // TODO: Add assertions to validate the answer
// }

// // Positive test case for Reset function
// TEST(CalculationModelTest, Reset_Positive) {
//   CalculationModel model;
//   // TODO: Add assertions to validate the reset functionality
// }

// // Positive test case for GetData function
// TEST(CalculationModelTest, GetData_Positive) {
//   CalculationModel model;
//   double result = model.GetData();
//   // TODO: Add assertions to validate the result
// }

// // Positive test case for PrintParsedExpression function
// TEST(CalculationModelTest, PrintParsedExpression_Positive) {
//   CalculationModel model;
//   // TODO: Add assertions to validate the printed parsed expression
// }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
