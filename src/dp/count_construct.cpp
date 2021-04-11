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

} // namespace dp

