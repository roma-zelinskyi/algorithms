/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/tab/fib.hpp"

#include <gtest/gtest.h>

namespace {

TEST(DynamicProgrammingTests, FibTabTest)
{
    EXPECT_EQ(8, dp::tab::fib(6));
    EXPECT_EQ(13, dp::tab::fib(7));
    EXPECT_EQ(21, dp::tab::fib(8));
    EXPECT_EQ(6765, dp::tab::fib(20));
    EXPECT_EQ(832040, dp::tab::fib(30));
}

} // namespace

