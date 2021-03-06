/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "dp/all_construct.hpp"

#include <gtest/gtest.h>

#include <forward_list>
#include <string>
#include <vector>

namespace {

TEST(DynamicProgrammingTests, AllConstructTest)
{
    auto expected1 = std::forward_list<std::forward_list<std::string>>{
        {"abcd", "ef"}, {"abc", "def"}, {"ab", "cd", "ef"}, {"ab", "c", "def"}};
    EXPECT_EQ(expected1, dp::allConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd", "ef", "c"}));

    EXPECT_EQ(
        std::forward_list<std::forward_list<std::string>>{},
        dp::allConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));

    auto expected2 =
        std::forward_list<std::forward_list<std::string>>{{"p", "ur", "p", "le"}, {"purp", "le"}};

    EXPECT_EQ(expected2, dp::allConstruct("purple", {"purp", "p", "ur", "le", "purpl"}));
    EXPECT_EQ(
        std::forward_list<std::forward_list<std::string>>{},
        dp::allConstruct(
            "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
            {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}));
}

TEST(DynamicProgrammingTests, AllConstructTabTest)
{
    auto expected1 = std::vector<std::vector<std::string>>{
        {"abc", "def"}, {"ab", "c", "def"}, {"abcd", "ef"}, {"ab", "cd", "ef"}};
    EXPECT_EQ(
        expected1, dp::allConstructTab("abcdef", {"ab", "abc", "cd", "def", "abcd", "ef", "c"}));

    EXPECT_EQ(
        std::vector<std::vector<std::string>>{},
        dp::allConstructTab("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));

    auto expected2 = std::vector<std::vector<std::string>>{{"purp", "le"}, {"p", "ur", "p", "le"}};
    EXPECT_EQ(expected2, dp::allConstructTab("purple", {"purp", "p", "ur", "le", "purpl"}));
}

} // namespace



