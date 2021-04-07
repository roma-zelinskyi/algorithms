/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "all_construct.hpp"

#include <iostream>
#include <optional>
#include <unordered_map>

namespace {

std::forward_list<std::forward_list<std::string>> allConstructMemo(
    std::unordered_map<std::string, std::forward_list<std::forward_list<std::string>>>& memo,
    const std::string& target,
    const std::vector<std::string>& wordBank)
{
    if (memo.count(target))
        return memo.at(target);

    if (target.empty())
        return {{}};

    auto res = std::forward_list<std::forward_list<std::string>>{};

    for (auto& word : wordBank) {
        if (target.starts_with(word)) {
            auto ways = allConstructMemo(memo, target.substr(word.size()), wordBank);
            for (auto& suffixWay : ways)
                suffixWay.push_front(word);

            for (const auto& targetWay : ways)
                res.push_front(targetWay);
        }
    }

    memo[target] = res;
    return res;
}

} // namespace

namespace dp::memo {

std::forward_list<std::forward_list<std::string>>
allConstruct(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto memo =
        std::unordered_map<std::string, std::forward_list<std::forward_list<std::string>>>{};

    return allConstructMemo(memo, target, wordBank);
}

} // namespace dp::memo



