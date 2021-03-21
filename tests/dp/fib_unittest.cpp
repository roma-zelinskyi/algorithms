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
    EXPECT_EQ(5, zee::fib(5));
    EXPECT_EQ(13, zee::fib(7));
    EXPECT_EQ(6765, zee::fib(20));
    EXPECT_EQ(17711, zee::fib(22));
}

} // namespace

