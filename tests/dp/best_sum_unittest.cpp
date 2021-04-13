/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/best_sum.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, BestSumTabTest)
{
    auto expected1 = std::vector{8u};
    EXPECT_EQ(expected1, dp::bestSumTab(8, {4, 2, 8}).value());

    auto expected2 = std::vector{2u, 5u, 5u};
    EXPECT_EQ(expected2, dp::bestSumTab(12, {5, 1, 3, 2, 15}).value());

    auto expected3 = std::vector{25u, 25u, 25u, 25u};
    EXPECT_EQ(expected3, dp::bestSumTab(100, {1, 2, 5, 25}).value());
}

} // namespace


