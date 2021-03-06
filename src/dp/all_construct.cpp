/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "all_construct.hpp"

#include <array>
#include <iostream>
#include <memory_resource>
#include <optional>
#include <unordered_map>
#include <vector>

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

namespace dp {

std::forward_list<std::forward_list<std::string>>
allConstruct(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto memo =
        std::unordered_map<std::string, std::forward_list<std::forward_list<std::string>>>{};

    return allConstructMemo(memo, target, wordBank);
}

std::vector<std::vector<std::string>>
allConstructTab(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto table = std::vector<std::vector<std::vector<std::string>>>(
        target.size() + 1, std::vector<std::vector<std::string>>{});
    table[0] = {{}};

    for (auto i = 0u; i <= target.size(); ++i) {
        if (!table.at(i).empty()) {
            auto subTarget = target.substr(i, target.size());
            for (const auto& word : wordBank) {
                if (subTarget.starts_with(word)) {
                    for (const auto& it : table.at(i)) {
                        auto& next = table.at(i + word.size());
                        next.push_back(it);
                        auto nextEndIt = next.end();
                        --nextEndIt;
                        nextEndIt->push_back(word);
                    }
                }
            }
        }
    }

    return table[target.size()];
}

} // namespace dp

