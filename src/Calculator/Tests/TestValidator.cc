#include <gtest/gtest.h>
#include "../Model/Validator.h"

using namespace s21;
// Positive test case for EmptyCheck()
TEST(ValidatorTest, EmptyCheck_Positive) {
  Validator validator;
  std::string inputString = "";
  bool result = validator.EmptyCheck(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for EmptyCheck()
TEST(ValidatorTest, EmptyCheck_Negative) {
  Validator validator;
  std::string inputString = "123";
  bool result = validator.EmptyCheck(inputString);
  EXPECT_FALSE(result);
}

// Positive test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Positive) {
  Validator validator;
  std::string inputString = "(1+2)*3";
  bool result = validator.BracketCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Negative) {
  Validator validator;
  std::string inputString = "(1+2*3";
  bool result = validator.BracketCheck(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Negative_01) {
  Validator validator;
  std::string inputString = ")1+2*3(";
  bool result = validator.BracketCheck(inputString);
  EXPECT_TRUE(result);
}
//
// Negative test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Negative_02) {
  Validator validator;
  std::string inputString = "()1+2*3(";
  bool result = validator.BracketCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for PlusMinusCheck()
TEST(ValidatorTest, PlusMinusCheck_Positive) {
  Validator validator;
  std::string inputString = "1+-2";
  bool result = validator.PlusMinusCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for PlusMinusCheck()
TEST(ValidatorTest, PlusMinusCheck_Negative) {
  Validator validator;
  std::string inputString = "1+2-";
  bool result = validator.PlusMinusCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for NumCheck()
TEST(ValidatorTest, NumCheck_Positive) {
  Validator validator;
  std::string inputString = "1.23";
  bool result = validator.NumCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for NumCheck()
TEST(ValidatorTest, NumCheck_Negative) {
  Validator validator;
  std::string inputString = "1.2.3";
  bool result = validator.NumCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for TwiseOpCheck()
TEST(ValidatorTest, TwiseOpCheck_Positive) {
  Validator validator;
  std::string inputString = "1*2^3";
  bool result = validator.TwiseOpCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for TwiseOpCheck()
TEST(ValidatorTest, TwiseOpCheck_Negative) {
  Validator validator;
  std::string inputString = "1**2";
  bool result = validator.TwiseOpCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for BinaryOpCheck()
TEST(ValidatorTest, BinaryOpCheck_Positive) {
  Validator validator;
  std::string inputString = "1+2*3";
  bool result = validator.BinaryOpCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for BinaryOpCheck()
TEST(ValidatorTest, BinaryOpCheck_Negative) {
  Validator validator;
  std::string inputString = "*1+2";
  bool result = validator.BinaryOpCheck(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for BinaryOpCheck()
TEST(ValidatorTest, BinaryOpCheck_Negative_Second) {
  Validator validator;
  std::string inputString = "1+2*";
  bool result = validator.BinaryOpCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for FooCheck()
TEST(ValidatorTest, FooCheck_Positive) {
  Validator validator;
  std::string inputString = "asin(0.5)";
  bool result = validator.FooCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for FooCheck()
TEST(ValidatorTest, FooCheck_Negative) {
  Validator validator;
  std::string inputString = "asin0.5";
  bool result = validator.FooCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsDigitOrPm()
TEST(ValidatorTest, IsDigitOrPm_Positive) {
  Validator validator;
  char ch = '5';
  bool result = validator.IsDigitOrPm(ch);
  EXPECT_TRUE(result);
}

// Negative test case for IsDigitOrPm()
TEST(ValidatorTest, IsDigitOrPm_Negative) {
  Validator validator;
  char ch = '!';
  bool result = validator.IsDigitOrPm(ch);
  EXPECT_FALSE(result);
}

// Positive test case for BinaryLeft()
TEST(ValidatorTest, BinaryLeft_Positive) {
  Validator validator;
  char ch = '9';
  bool result = validator.BinaryLeft(ch);
  EXPECT_TRUE(result);
}

// Negative test case for BinaryLeft()
TEST(ValidatorTest, BinaryLeft_Negative) {
  Validator validator;
  char ch = '(';
  bool result = validator.BinaryLeft(ch);
  EXPECT_FALSE(result);
}

// Positive test case for IsCorrect()
TEST(ValidatorTest, IsCorrect_Positive) {
  Validator validator;
  std::string inputString = "1+2*3";
  EXPECT_NO_THROW(validator.IsNotCorrect(inputString));
}

// Negative test case for IsCorrect()
TEST(ValidatorTest, IsCorrect_Negative) {
  Validator validator;
  std::string inputString = "1+2*";
  EXPECT_ANY_THROW(validator.IsNotCorrect(inputString));
}
