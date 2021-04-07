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
    EXPECT_EQ(1, zee::countConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}));
    EXPECT_EQ(0, zee::countConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    EXPECT_EQ(
        4, zee::countConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
    EXPECT_EQ(2, zee::countConstruct("purple", {"purp", "p", "ur", "le", "purpl"}));
    EXPECT_EQ(
        0,
        zee::countConstruct(
            "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
            {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

} // namespace



