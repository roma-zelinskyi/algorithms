/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "can_construct.hpp"

#include <unordered_map>

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

} // namespace dp

