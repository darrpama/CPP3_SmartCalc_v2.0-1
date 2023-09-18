#include <gtest/gtest.h>

#include "../Model/CreditModel.h"

using namespace s21;

TEST(CreditCalculatorTestAnnuitet, CreditCalculatorAnnuitetPositive) {
  CreditModel creditCalculator;
  credit_data result = creditCalculator.CalculateCredit(
      1000000, 3, 20, credit_time_type::credit_year, annuitet);
  EXPECT_DOUBLE_EQ(result.total_sum, 1337888.88);
  EXPECT_DOUBLE_EQ(result.overpay, 337888.88);
}

TEST(CreditCalculatorTestDifferential, CreditCalculatorDifferentialPositive) {
  CreditModel creditCalculator;
  credit_data result = creditCalculator.CalculateCredit(
      1000000, 3, 20, credit_time_type::credit_year, differential);
  EXPECT_DOUBLE_EQ(result.total_sum, 1308333.33);
  EXPECT_DOUBLE_EQ(result.overpay, 308333.33);
}
