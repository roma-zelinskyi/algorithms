/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "fib.hpp"

#include <iostream>
#include <unordered_map>

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

namespace zee {

std::uint32_t fib(const std::uint32_t num)
{
    auto memo = std::unordered_map<std::uint32_t, std::uint32_t>{};

    auto f = fibMemo(memo, num);

    return f;
}

} // namespace zee

