/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/memo/count_construct.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, CountConstructTest)
{
    EXPECT_EQ(1, dp::memo::countConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_EQ(0, dp::memo::countConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_EQ(
        4, dp::memo::countConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_EQ(2, dp::memo::countConstruct("purple", {"purp", "p", "ur", "le", "purpl"}));
    EXPECT_EQ(
        0,
        dp::memo::countConstruct(
            "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
            {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

} // namespace



