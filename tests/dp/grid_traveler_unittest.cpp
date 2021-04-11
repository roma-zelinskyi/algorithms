/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/grid_traveler.hpp"

#include <gtest/gtest.h>

namespace {

TEST(DynamicProgrammingTests, GridTravelerTest)
{
    EXPECT_EQ(3, dp::gridTraveler(2, 3));
    EXPECT_EQ(20, dp::gridTraveler(4, 4));
    EXPECT_EQ(2333606220, dp::gridTraveler(18, 18));
}

TEST(DynamicProgrammingTests, GridTravelerTabTest)
{
    EXPECT_EQ(3, dp::gridTraveler(2, 3));
    EXPECT_EQ(6, dp::gridTraveler(3, 3));
    EXPECT_EQ(20, dp::gridTraveler(4, 4));
    EXPECT_EQ(40116600, dp::gridTraveler(15, 15));
    EXPECT_EQ(2333606220, dp::gridTraveler(18, 18));
}

} // namespace

