/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "can_sum.hpp"

#include <unordered_map>

namespace {
bool canSumMemo(std::unordered_map<int, bool>& memo, const int num, const std::vector<int>& arr)
{
    if (num == 0)
        return true;

    if (num < 0)
        return false;

    if (memo.count(num))
        return memo.at(num);

    auto flag = false;
    for (const auto& it : arr) {
        flag |= canSumMemo(memo, num - it, arr);

        memo[num] = flag;
    }

    return memo.at(num);
}

} // namespace

namespace zee {

bool canSum(const int num, const std::vector<int>& arr)
{
    auto memo = std::unordered_map<int, bool>{};
    return canSumMemo(memo, num, arr);
}

} // namespace zee

