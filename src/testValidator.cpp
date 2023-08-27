#include <gtest/gtest.h>
#include "Validator.h"

// Positive test case for EmptyCheck()
TEST(ValidatorTest, EmptyCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "";
  bool result = validator.EmptyCheck(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for EmptyCheck()
TEST(ValidatorTest, EmptyCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "123";
  bool result = validator.EmptyCheck(inputString);
  EXPECT_FALSE(result);
}

// Positive test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "(1+2)*3";
  bool result = validator.BracketCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "(1+2*3";
  bool result = validator.BracketCheck(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Negative_01) {
  s21::Validator validator;
  std::string inputString = ")1+2*3(";
  bool result = validator.BracketCheck(inputString);
  EXPECT_TRUE(result);
}
//
// Negative test case for BracketCheck()
TEST(ValidatorTest, BracketCheck_Negative_02) {
  s21::Validator validator;
  std::string inputString = "()1+2*3(";
  bool result = validator.BracketCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for PlusMinusCheck()
TEST(ValidatorTest, PlusMinusCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "1+-2";
  bool result = validator.PlusMinusCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for PlusMinusCheck()
TEST(ValidatorTest, PlusMinusCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "1+2-";
  bool result = validator.PlusMinusCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for NumCheck()
TEST(ValidatorTest, NumCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "1.23";
  bool result = validator.NumCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for NumCheck()
TEST(ValidatorTest, NumCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "1.2.3";
  bool result = validator.NumCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for TwiseOpCheck()
TEST(ValidatorTest, TwiseOpCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "1*2^3";
  bool result = validator.TwiseOpCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for TwiseOpCheck()
TEST(ValidatorTest, TwiseOpCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "1**2";
  bool result = validator.TwiseOpCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for BinaryOpCheck()
TEST(ValidatorTest, BinaryOpCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "1+2*3";
  bool result = validator.BinaryOpCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for BinaryOpCheck()
TEST(ValidatorTest, BinaryOpCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "*1+2";
  bool result = validator.BinaryOpCheck(inputString);
  EXPECT_TRUE(result);
}

// Negative test case for BinaryOpCheck()
TEST(ValidatorTest, BinaryOpCheck_Negative_Second) {
  s21::Validator validator;
  std::string inputString = "1+2*";
  bool result = validator.BinaryOpCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for FooCheck()
TEST(ValidatorTest, FooCheck_Positive) {
  s21::Validator validator;
  std::string inputString = "asin(0.5)";
  bool result = validator.FooCheck(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for FooCheck()
TEST(ValidatorTest, FooCheck_Negative) {
  s21::Validator validator;
  std::string inputString = "asin0.5";
  bool result = validator.FooCheck(inputString);
  EXPECT_TRUE(result);
}

// Positive test case for IsDigitOrPm()
TEST(ValidatorTest, IsDigitOrPm_Positive) {
  s21::Validator validator;
  char ch = '5';
  bool result = validator.IsDigitOrPm(ch);
  EXPECT_TRUE(result);
}

// Negative test case for IsDigitOrPm()
TEST(ValidatorTest, IsDigitOrPm_Negative) {
  s21::Validator validator;
  char ch = '!';
  bool result = validator.IsDigitOrPm(ch);
  EXPECT_FALSE(result);
}

// Positive test case for BinaryLeft()
TEST(ValidatorTest, BinaryLeft_Positive) {
  s21::Validator validator;
  char ch = '9';
  bool result = validator.BinaryLeft(ch);
  EXPECT_TRUE(result);
}

// Negative test case for BinaryLeft()
TEST(ValidatorTest, BinaryLeft_Negative) {
  s21::Validator validator;
  char ch = '(';
  bool result = validator.BinaryLeft(ch);
  EXPECT_FALSE(result);
}

// Positive test case for IsCorrect()
TEST(ValidatorTest, IsCorrect_Positive) {
  s21::Validator validator;
  std::string inputString = "1+2*3";
  bool result = validator.IsCorrect(inputString);
  EXPECT_FALSE(result);
}

// Negative test case for IsCorrect()
TEST(ValidatorTest, IsCorrect_Negative) {
  s21::Validator validator;
  std::string inputString = "1+2*";
  bool result = validator.IsCorrect(inputString);
  EXPECT_TRUE(result);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
