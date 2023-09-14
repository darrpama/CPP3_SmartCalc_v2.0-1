#include <gtest/gtest.h>
#include "../Model/CreditModel.h"

using namespace s21;

TEST(CreditCalculatorTestAnnuitet, CreditCalculatorAnnuitetPositive) {
  CreditModel creditCalculator;
  creditCalculator.CalculateCredit(1000000, 3, 20, year, annuitet);
  credit_data result = creditCalculator.GetAnswer();
  EXPECT_DOUBLE_EQ(result.total_sum, 1337888.88);
  EXPECT_DOUBLE_EQ(result.overpay, 337888.88);
}

TEST(CreditCalculatorTestDifferential, CreditCalculatorDifferentialPositive) {
  CreditModel creditCalculator;
  creditCalculator.CalculateCredit(1000000, 3, 20, year, differential);
  credit_data result = creditCalculator.GetAnswer();
  EXPECT_DOUBLE_EQ(result.total_sum, 1308333.33);
  EXPECT_DOUBLE_EQ(result.overpay, 308333.33);
}
