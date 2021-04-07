/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "how_sum.hpp"

#include <optional>
#include <unordered_map>

namespace {

std::optional<std::vector<int>> howSumMemo(
    std::unordered_map<int, std::optional<std::vector<int>>>& memo,
    const int num,
    const std::vector<int>& arr)
{
    if (num == 0)
        return std::vector<int>{};

    if (num < 0)
        return std::nullopt;

    if (memo.count(num))
        return memo.at(num);

    auto maxArr = std::vector<int>{};
    for (const auto& it : arr) {
        const auto remainder = num - it;
        auto res = howSumMemo(memo, remainder, arr);
        if (res != std::nullopt) {
            res.value().push_back(it);
            memo[num] = res;
            return res;
        }
    }

    memo[num] = std::nullopt;

    return std::nullopt;
}

} // namespace

namespace dp::memo {

std::vector<int> howSum(const int num, const std::vector<int>& arr)
{
    auto memo = std::unordered_map<int, std::optional<std::vector<int>>>{};
    auto res = howSumMemo(memo, num, arr);

    return (res == std::nullopt ? std::vector<int>{} : res.value());
}

} // namespace dp::memo

