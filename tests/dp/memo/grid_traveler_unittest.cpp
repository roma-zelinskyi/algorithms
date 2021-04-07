/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/memo/grid_traveler.hpp"

#include <gtest/gtest.h>

namespace {

TEST(DynamicProgrammingTests, GridTravelerTest)
{
    EXPECT_EQ(3, dp::memo::gridTraveler(2, 3));
    EXPECT_EQ(20, dp::memo::gridTraveler(4, 4));
    EXPECT_EQ(2333606220, dp::memo::gridTraveler(18, 18));
}

} // namespace

