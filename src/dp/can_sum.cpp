/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "can_sum.hpp"

#include <array>
#include <memory_resource>
#include <unordered_map>
#include <vector>

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

namespace dp {

bool canSum(const int num, const std::vector<int>& arr)
{
    auto memo = std::unordered_map<int, bool>{};
    return canSumMemo(memo, num, arr);
}

bool canSumTab(const std::uint32_t num, const std::vector<std::uint32_t>& arr)
{
    auto buffer = std::array<std::byte, 409600>{};
    auto mr = std::pmr::monotonic_buffer_resource{buffer.data(), buffer.size()};
    auto table = std::pmr::vector<bool>(num + 1, false, &mr);
    table[0] = true;

    for (auto i = 0u; i <= num; ++i) {
        if (table[i]) {
            for (const auto& it : arr)
                if (it + i <= num)
                    table[it + i] = true;
        }
    }

    return table.at(num);
}

} // namespace dp

