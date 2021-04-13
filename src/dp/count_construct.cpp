/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <unordered_map>

#include "can_construct.hpp"

namespace {

std::uint32_t countConstructMemo(
    std::unordered_map<std::string, std::uint32_t>& memo,
    const std::string& target,
    const std::vector<std::string>& wordBank)
{
    if (memo.count(target))
        return memo.at(target);

    if (target.empty())
        return 1;

    auto count = 0u;
    for (const auto& it : wordBank)
        if (target.starts_with(it))
            count += countConstructMemo(memo, target.substr(it.size()), wordBank);

    memo[target] = count;

    return count;
}

} // namespace

namespace dp {

std::uint32_t countConstruct(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto memo = std::unordered_map<std::string, std::uint32_t>{};
    return countConstructMemo(memo, target, wordBank);
}

std::uint32_t countConstructTab(const std::string& target, const std::vector<std::string>& wordBank)
{
    auto table = std::vector<std::uint32_t>(target.size() + 1, 0);
    table[0] = 1;

    for (auto i = 0u; i <= target.size(); ++i) {
        if (table[i] != 0) {
            auto subTarget = target.substr(i, target.size());
            for (const auto& word : wordBank) {
                if (subTarget.starts_with(word))
                    table[i + word.size()] += table[i];
            }
        }
    }

    return table[target.size()];
}

} // namespace dp

