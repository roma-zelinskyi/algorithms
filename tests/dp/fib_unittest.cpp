/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/fib.hpp"

#include <gtest/gtest.h>

namespace {

TEST(DynamicProgrammingTests, FibTest)
{
    EXPECT_EQ(5, dp::fib(5));
    EXPECT_EQ(13, dp::fib(7));
    EXPECT_EQ(6765, dp::fib(20));
    EXPECT_EQ(17711, dp::fib(22));
}

TEST(DynamicProgrammingTests, FibTabTest)
{
    EXPECT_EQ(8, dp::fib(6));
    EXPECT_EQ(13, dp::fib(7));
    EXPECT_EQ(21, dp::fib(8));
    EXPECT_EQ(6765, dp::fib(20));
    EXPECT_EQ(832040, dp::fib(30));
}

} // namespace

