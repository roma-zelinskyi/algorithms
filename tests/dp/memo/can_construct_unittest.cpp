/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/memo/can_construct.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, CanConstructTest)
{
    EXPECT_TRUE(dp::memo::canConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_FALSE(dp::memo::canConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_TRUE(dp::memo::canConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_FALSE(dp::memo::canConstruct(
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
        {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

} // namespace



