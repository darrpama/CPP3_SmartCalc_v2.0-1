#include <gtest/gtest.h>

#include "../Model/DepositModel.h"

using namespace s21;

TEST(DepositCalculatorTestAnnuitet, DepositCalculatorAnnuitetPositive_1) {
  DepositModel depositCalculator;
  deposit_data result = depositCalculator.CalculateDeposit(
      1000000, 3, 20, s21::deposit_time_type::deposit_year,
      s21::capitalization::with_capitalization,
      s21::deposit_time_type::deposit_month);
  EXPECT_DOUBLE_EQ(result.total_sum, 1796414.3946309141);
  EXPECT_DOUBLE_EQ(result.profit, 796414.39463091327);
}

TEST(DepositCalculatorTestAnnuitet, DepositCalculatorAnnuitetPositive_2) {
  DepositModel depositCalculator;
  deposit_data result = depositCalculator.CalculateDeposit(
      1000000, 3, 20, s21::deposit_time_type::deposit_year,
      s21::capitalization::with_capitalization,
      s21::deposit_time_type::deposit_quartal);
  EXPECT_DOUBLE_EQ(result.total_sum, 1773809.4350964825);
  EXPECT_DOUBLE_EQ(result.profit, 773809.43509648286);
}

TEST(DepositCalculatorTestAnnuitet, DepositCalculatorAnnuitetPositive_3) {
  DepositModel depositCalculator;
  deposit_data result = depositCalculator.CalculateDeposit(
      1000000, 3, 20, s21::deposit_time_type::deposit_year,
      s21::capitalization::with_capitalization,
      s21::deposit_time_type::deposit_year);
  EXPECT_DOUBLE_EQ(result.total_sum, 1720055.5555555557);
  EXPECT_DOUBLE_EQ(result.profit, 720055.5555555562);
}

TEST(DepositCalculatorTestDifferential,
     DepositCalculatorDifferentialPositive_4) {
  DepositModel depositCalculator;
  deposit_data result = depositCalculator.CalculateDeposit(
      1000000, 3, 20, s21::deposit_time_type::deposit_year,
      s21::capitalization::without_capitalization,
      s21::deposit_time_type::deposit_month);
  EXPECT_DOUBLE_EQ(result.total_sum, 1600000);
  EXPECT_DOUBLE_EQ(result.profit, 600000);
}
