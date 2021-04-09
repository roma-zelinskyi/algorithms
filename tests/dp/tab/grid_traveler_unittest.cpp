/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/tab/grid_traveler.hpp"

#include <gtest/gtest.h>

namespace {

TEST(DynamicProgrammingTests, GridTravelerTabTest)
{
    EXPECT_EQ(3, dp::tab::gridTraveler(2, 3));
    EXPECT_EQ(6, dp::tab::gridTraveler(3, 3));
    EXPECT_EQ(20, dp::tab::gridTraveler(4, 4));
    EXPECT_EQ(40116600, dp::tab::gridTraveler(15, 15));
    EXPECT_EQ(2333606220, dp::tab::gridTraveler(18, 18));
}

} // namespace

