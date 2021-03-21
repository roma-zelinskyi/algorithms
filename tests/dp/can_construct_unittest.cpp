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
    EXPECT_TRUE(zee::canConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_FALSE(zee::canConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_TRUE(zee::canConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_FALSE(zee::canConstruct(
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
        {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

} // namespace



