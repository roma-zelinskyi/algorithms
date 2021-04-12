/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/how_sum.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, HowSumTest)
{
    auto expected1 = std::vector{4, 4};
    EXPECT_EQ(expected1, dp::howSum(8, {4, 2, 8}));

    auto expected2 = std::vector{4, 3};
    EXPECT_EQ(expected2, dp::howSum(7, {5, 3, 4, 7}));

    EXPECT_EQ(std::vector<int>{}, dp::howSum(300, {7, 14}));
}

TEST(DynamicProgrammingTests, HowSumTabTest)
{
    auto expected1 = std::vector{2u, 2u, 4u};
    EXPECT_EQ(expected1, dp::howSumTab(8, {2, 4}).value());

    auto expected2 = std::vector{3u, 4u};
    EXPECT_EQ(expected2, dp::howSumTab(7, {5, 3, 4}).value());

    EXPECT_EQ(std::nullopt, dp::howSumTab(300, {7, 14}));
}

} // namespace


