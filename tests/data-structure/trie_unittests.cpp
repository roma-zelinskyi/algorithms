/**
 *  Project Data Structure
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "data-structure/trie.hpp"

using namespace std::string_literals;

namespace {

TEST(TrieDataStructureTests, ContainsKeyTest)
{
    auto trie = zee::Trie<std::string, std::string>{};
    trie.insert("abc"s, "111");
    trie.insert("ab"s, "123556666");
    trie.insert("abd"s, "222");
    trie.insert("abe"s, "3");
    trie.insert("abed"s, "4");
    trie.insert("cdba"s, "4");

    EXPECT_TRUE(trie.contains("abe"));
    EXPECT_TRUE(trie.contains("ab"));
    EXPECT_TRUE(trie.contains("cdba"));
}

TEST(TrieDataStructureTests, GetValueByKeyTest)
{
    auto trie = zee::Trie<std::string, std::uint32_t>{};
    trie.insert("A", 1);
    trie.insert("ABD", 3);
    trie.insert("AB", 2);
    trie.insert("ABDCRT", 5);
    trie.insert("ABKW", 7);
    trie.insert("ABKC", 8);
    trie.insert("ABKCN", 10);
    trie.insert("ABKCW", 13);
    trie.insert("ABKCG", 16);
    trie.insert("ABKCGQ", 18);
    trie.insert("ABKCGQM", 20);
    trie.insert("ABKCGQL", 45);
    trie.insert("ABKCGQL", 123);
    trie.insert("AW", 33);
    trie.insert("AZ", 131);
    trie.insert("AX", 133);

    EXPECT_EQ(trie.at("AB"), 2);
    EXPECT_EQ(trie.at("ABKC"), 8);
    EXPECT_EQ(trie.at("AW"), 33);
    EXPECT_EQ(trie.at("ABKCGQ"), 18);
    EXPECT_EQ(trie.at("AX"), 133);
}

TEST(TrieDataStructureTests, EraseKeyTest)
{
    auto trie = zee::Trie<std::string, std::uint32_t>{};
    trie.insert("axf", 1);
    trie.insert("axg", 3);
    trie.insert("wjr", 3);
    trie.insert("wjry", 3);
    trie.insert("wjryf", 3);

    trie.erase("wjr");
    trie.erase("wjryf");

    EXPECT_TRUE(trie.contains("wjry"));
    EXPECT_FALSE(trie.contains("wjr"));
    EXPECT_FALSE(trie.contains("wjryf"));

    EXPECT_EQ(trie.at("wjry"), 3);
    EXPECT_ANY_THROW(trie.at("wjryf"));
}
} // namespace

