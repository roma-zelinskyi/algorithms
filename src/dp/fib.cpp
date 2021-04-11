/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "fib.hpp"

#include <unordered_map>
#include <vector>

namespace {

std::uint32_t
fibMemo(std::unordered_map<std::uint32_t, std::uint32_t>& memo, const std::uint32_t num)
{
    if (num <= 2)
        return 1;

    if (memo.count(num))
        return memo.at(num);

    memo[num] = fibMemo(memo, num - 1) + fibMemo(memo, num - 2);

    return memo[num];
}

} // namespace

namespace dp {

std::uint32_t fib(const std::uint32_t num)
{
    auto memo = std::unordered_map<std::uint32_t, std::uint32_t>{};

    auto f = fibMemo(memo, num);

    return f;
}

std::uint32_t fibTab(const std::uint32_t num)
{
    auto table = std::vector<std::uint32_t>(num + 2, 0);
    table[1] = 1;

    for (auto i = 0u; i <= num; ++i) {
        table[i + 1] += table[i];
        table[i + 2] += table[i];
    }

    return table[num];
}

} // namespace dp

