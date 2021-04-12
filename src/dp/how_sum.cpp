/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "how_sum.hpp"

#include <array>
#include <memory_resource>
#include <unordered_map>
#include <vector>

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

namespace dp {

std::vector<int> howSum(const int num, const std::vector<int>& arr)
{
    auto memo = std::unordered_map<int, std::optional<std::vector<int>>>{};
    auto res = howSumMemo(memo, num, arr);

    return (res == std::nullopt ? std::vector<int>{} : res.value());
}

std::optional<std::vector<std::uint32_t>>
howSumTab(const std::uint32_t num, const std::vector<std::uint32_t>& arr)
{
    auto buffer = std::array<std::byte, 40960>{};
    auto mr = std::pmr::monotonic_buffer_resource{buffer.data(), buffer.size()};
    auto table =
        std::pmr::vector<std::optional<std::vector<std::uint32_t>>>(num + 1, std::nullopt, &mr);
    table[0] = std::make_optional<std::vector<std::uint32_t>>();

    for (auto i = 0u; i <= num; ++i) {
        if (table.at(i)) {
            for (const auto& it : arr) {
                if (i + it <= num) {
                    table[i + it] = table.at(i);
                    table.at(i + it).value().push_back(it);
                }

                if (i + it == num)
                    return table.at(i + it);
            }
        }
    }

    return table[num];
}

} // namespace dp

