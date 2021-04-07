/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "grid_traveler.hpp"

#include <unordered_map>
#include <utility>

template<class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
template<typename S, typename T>
struct hash<pair<S, T>>
{
    inline size_t operator()(const pair<S, T>& v) const
    {
        size_t seed = 0;
        ::hash_combine(seed, v.first);
        ::hash_combine(seed, v.second);
        return seed;
    }
};
} // namespace std

namespace {

std::uint32_t gridTravelerMemo(
    [[maybe_unused]] std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t>&
        memo,
    [[maybe_unused]] const std::uint32_t n,
    [[maybe_unused]] const std::uint32_t m)
{
    if (n == 0 || m == 0)
        return 0;

    if (n == 1 && m == 1)
        return 1;

    if (memo.count({n, m}))
        return memo.at({n, m});

    if (memo.count({m, n}))
        return memo.at({m, n});

    memo[{n, m}] = gridTravelerMemo(memo, n - 1, m) + gridTravelerMemo(memo, n, m - 1);

    return memo.at({n, m});
}

} // namespace

namespace dp::memo {

std::uint32_t gridTraveler(const std::uint32_t n, const std::uint32_t m)
{
    auto memo = std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t>{};

    return gridTravelerMemo(memo, n, m);
}

} // namespace dp::memo


