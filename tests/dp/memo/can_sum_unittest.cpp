/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/memo/can_sum.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, CanSumTest)
{
    EXPECT_TRUE(dp::memo::canSum(7, {5, 3, 4, 7}));
    EXPECT_FALSE(dp::memo::canSum(7, {2, 4, 2}));
    EXPECT_FALSE(dp::memo::canSum(30000, {7, 14, 21}));
}

} // namespace


