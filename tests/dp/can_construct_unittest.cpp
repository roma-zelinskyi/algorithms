/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/can_construct.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, CanConstructTest)
{
    EXPECT_TRUE(dp::canConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_FALSE(dp::canConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_TRUE(dp::canConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_FALSE(dp::canConstruct(
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
        {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

} // namespace



