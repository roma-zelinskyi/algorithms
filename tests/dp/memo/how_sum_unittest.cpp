/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/memo/how_sum.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

namespace {

TEST(DynamicProgrammingTests, HowSumTest)
{
    auto expected1 = std::vector{4, 4};
    EXPECT_EQ(expected1, zee::howSum(8, {4, 2, 8}));

    auto expected2 = std::vector{4, 3};
    EXPECT_EQ(expected2, zee::howSum(7, {5, 3, 4, 7}));

    EXPECT_EQ(std::vector<int>{}, zee::howSum(300, {7, 14}));
}

} // namespace


