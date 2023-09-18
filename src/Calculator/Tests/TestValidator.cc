#include <gtest/gtest.h>

#include "../Model/Validator.h"

using namespace s21;
// Positive test case for EmptyCheck()
TEST(ValidatorTest, EmptyCheck_Positive) {
  Validator validator;
  std::string inputString = "";
  bool result = validator.IsEmpty(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for EmptyCheck()
TEST(ValidatorTest, EmptyCheck_Negative) {
  Validator validator;
  std::string inputString = "123";
  bool result = validator.IsEmpty(inputString);
  EXPECT_FALSE(result);
}

// Positive test case for IsBracketNotCorrect()
TEST(ValidatorTest, BracketCheck_Positive) {
  Validator validator;
  std::string inputString = "(1+2)*3";
  bool result = validator.IsBracketNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsBracketNotCorrect()
TEST(ValidatorTest, BracketCheck_Negative) {
  Validator validator;
  std::string inputString = "(1+2*3";
  bool result = validator.IsBracketNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for IsBracketNotCorrect()
TEST(ValidatorTest, BracketCheck_Negative_01) {
  Validator validator;
  std::string inputString = ")1+2*3(";
  bool result = validator.IsBracketNotCorrect(inputString);
  EXPECT_TRUE(result);
}
//
// Negative test case for IsBracketNotCorrect()
TEST(ValidatorTest, BracketCheck_Negative_02) {
  Validator validator;
  std::string inputString = "()1+2*3(";
  bool result = validator.IsBracketNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsPlusMinusNotCorrect()
TEST(ValidatorTest, PlusMinusCheck_Positive) {
  Validator validator;
  std::string inputString = "1+(-2)";
  bool result = validator.IsPlusMinusNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsPlusMinusNotCorrect()
TEST(ValidatorTest, PlusMinusCheck_Negative) {
  Validator validator;
  std::string inputString = "1+2-";
  bool result = validator.IsPlusMinusNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsNumNotCorrect()
TEST(ValidatorTest, NumCheck_Positive) {
  Validator validator;
  std::string inputString = "1.23";
  bool result = validator.IsNumNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Positive test case for IsNumNotCorrect()
TEST(ValidatorTest, NumCheck_Positive_2) {
  Validator validator;
  std::string inputString = "cos((-10.000000))-sin((-10.000000))";
  bool result = validator.IsNumNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsNumNotCorrect()
TEST(ValidatorTest, NumCheck_Negative) {
  Validator validator;
  std::string inputString = "1.2.3";
  bool result = validator.IsNumNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsTwiseOpNotCorrect()
TEST(ValidatorTest, TwiseOpCheck_Positive) {
  Validator validator;
  std::string inputString = "1*2^3";
  bool result = validator.IsTwiseOpNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsTwiseOpNotCorrect()
TEST(ValidatorTest, TwiseOpCheck_Negative) {
  Validator validator;
  std::string inputString = "1**2";
  bool result = validator.IsTwiseOpNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsBinaryOpNotCorrect()
TEST(ValidatorTest, BinaryOpCheck_Positive) {
  Validator validator;
  std::string inputString = "1+2*3";
  bool result = validator.IsBinaryOpNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsBinaryOpNotCorrect()
TEST(ValidatorTest, BinaryOpCheck_Negative) {
  Validator validator;
  std::string inputString = "*1+2";
  bool result = validator.IsBinaryOpNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for IsBinaryOpNotCorrect()
TEST(ValidatorTest, BinaryOpCheck_Negative_Second) {
  Validator validator;
  std::string inputString = "1+2*";
  bool result = validator.IsBinaryOpNotCorrect(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsFooNotCorrect()
TEST(ValidatorTest, FooCheck_Positive) {
  Validator validator;
  std::string inputString = "asin(0.5)";
  bool result = validator.IsFooNotCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsFooNotCorrect()
TEST(ValidatorTest, FooCheck_Negative) {
  Validator validator;
  std::string inputString = "asin0.5";
  bool result = validator.IsFooNotCorrect(inputString);
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

// Positive test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Positive) {
  Validator validator;
  std::string inputString = "1+2*3";
  EXPECT_NO_THROW(validator.IsNotCorrect(inputString));
}

// Negative test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Negative) {
  Validator validator;
  std::string inputString = "1+2*";
  EXPECT_ANY_THROW(validator.IsNotCorrect(inputString));
}

// Negative test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Negative_02) {
  Validator validator;
  std::string inputString = "-10.000000-";
  EXPECT_ANY_THROW(validator.IsNotCorrect(inputString));
}

// Negative test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Negative_03) {
  Validator validator;
  std::string inputString = "mod9";
  EXPECT_ANY_THROW(validator.IsNotCorrect(inputString));
}

// Positive test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Positive_2) {
  Validator validator;
  std::string inputString = "1+2e-3*3";
  EXPECT_NO_THROW(validator.IsNotCorrect(inputString));
}

// Positive test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Negative_2) {
  Validator validator;
  std::string inputString = "1+2*1e3";
  EXPECT_NO_THROW(validator.IsNotCorrect(inputString));
}

// Positive test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Negative_3) {
  Validator validator;
  std::string inputString = "1+2*1e+3";
  EXPECT_NO_THROW(validator.IsNotCorrect(inputString));
}

// Positive test case for IsNotCorrect()
TEST(ValidatorTest, IsNotCorrect_Negative_4) {
  Validator validator;
  std::string inputString = "cos-10.000000";
  EXPECT_ANY_THROW(validator.IsNotCorrect(inputString));
}

// Positive test case for IsExponentNotCorrect()
TEST(ValidatorTest, ExponentCheck_positive) {
  Validator v = Validator();
  EXPECT_NO_THROW(v.IsNotCorrect("3.14e3"));
  EXPECT_NO_THROW(v.IsNotCorrect("(3.14+3)e3"));
  EXPECT_NO_THROW(v.IsNotCorrect("(3.14+3)e-3"));
  EXPECT_NO_THROW(v.IsNotCorrect("3.14e3"));
}

// Negative test case for IsCorrect()
TEST(ValidatorTest, ExponentCheck_negative) {
  Validator v = Validator();
  EXPECT_ANY_THROW(v.IsNotCorrect("1.23-e3"));
  EXPECT_ANY_THROW(v.IsNotCorrect("1.23.e3"));
  EXPECT_ANY_THROW(v.IsNotCorrect("1.23e."));
  EXPECT_ANY_THROW(v.IsNotCorrect("1.23e.3"));
  EXPECT_ANY_THROW(v.IsNotCorrect("1.23ee3"));
}