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
    ASSERT_EQ(3, zee::gridTraveler(2, 3));
    ASSERT_EQ(20, zee::gridTraveler(4, 4));
    ASSERT_EQ(2333606220, zee::gridTraveler(18, 18));
}

} // namespace

