/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/memo/fib.hpp"

#include <gtest/gtest.h>

namespace {

TEST(DynamicProgrammingTests, FibTest)
{
    EXPECT_EQ(5, dp::memo::fib(5));
    EXPECT_EQ(13, dp::memo::fib(7));
    EXPECT_EQ(6765, dp::memo::fib(20));
    EXPECT_EQ(17711, dp::memo::fib(22));
}

} // namespace

