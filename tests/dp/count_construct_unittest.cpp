/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/count_construct.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DynamicProgrammingTests, CountConstructTest)
{
    EXPECT_EQ(1, dp::countConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_EQ(0, dp::countConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_EQ(4, dp::countConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_EQ(2, dp::countConstruct("purple", {"purp", "p", "ur", "le", "purpl"}));
    EXPECT_EQ(
        0,
        dp::countConstruct(
            "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
            {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

TEST(DynamicProgrammingTests, CountConstructTabTest)
{
    EXPECT_EQ(1, dp::countConstructTab("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_EQ(
        0, dp::countConstructTab("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_EQ(
        4, dp::countConstructTab("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_EQ(2, dp::countConstructTab("purple", {"purp", "p", "ur", "le", "purpl"}));
    EXPECT_EQ(
        0,
        dp::countConstructTab(
            "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
            {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

} // namespace



