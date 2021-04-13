/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "can_construct.hpp"

#include <unordered_map>
#include <vector>

namespace {

bool canConstructMemo(
    std::unordered_map<std::string, bool>& memo,
    const std::string& target,
    const std::vector<std::string>& wordBank)
{
    if (memo.count(target))
        return memo.at(target);

    if (target.empty())
        return true;

    for (const auto& it : wordBank) {
        if (target.starts_with(it))
            if (canConstructMemo(memo, target.substr(it.size()), wordBank)) {
                memo[target] = true;
                return true;
            }
    }

    memo[target] = false;

    return false;
}

} // namespace

namespace dp {

bool canConstruct(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto memo = std::unordered_map<std::string, bool>{};
    return canConstructMemo(memo, target, wordBank);
}

bool canConstructTab(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto table = std::vector<bool>(target.size() + 1, false);
    table[0] = true;

    for (auto i = 0u; i <= target.size(); ++i) {
        if (table[i]) {
            auto subStr = target.substr(i, target.size());
            for (const auto& word : wordBank) {
                if (subStr.starts_with(word))
                    table[i + word.size()] = true;
            }
        }
    }

    return table[target.size()];
}

} // namespace dp

