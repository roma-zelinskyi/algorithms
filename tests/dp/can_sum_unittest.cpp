/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/can_sum.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, CanSumTest)
{
    EXPECT_TRUE(dp::canSum(7, {5, 3, 4, 7}));
    EXPECT_FALSE(dp::canSum(7, {2, 4, 2}));
    EXPECT_FALSE(dp::canSum(30000, {7, 14, 21}));
}

TEST(DynamicProgrammingTests, CanSumTabTest)
{
    EXPECT_TRUE(dp::canSum(7, {5, 3, 4, 7}));
    EXPECT_FALSE(dp::canSum(7, {2, 4, 2}));
    EXPECT_FALSE(dp::canSum(30000, {7, 14, 21}));
}

} // namespace


