/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "grid_traveler.hpp"

#include <memory_resource>
#include <unordered_map>
#include <utility>
#include <vector>

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
    std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t>& memo,
    const std::uint32_t n,
    const std::uint32_t m)
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

namespace dp {

std::uint32_t gridTraveler(const std::uint32_t n, const std::uint32_t m)
{
    auto memo = std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t>{};

    return gridTravelerMemo(memo, n, m);
}

std::uint32_t gridTravelerTab(const std::uint32_t n, const std::uint32_t m)
{
    auto buf = std::array<std::byte, 409600>{};
    auto mbr = std::pmr::monotonic_buffer_resource{buf.data(), buf.size()};
    auto table = std::pmr::vector<std::pmr::vector<std::uint32_t>>(
        n + 2, std::pmr::vector<std::uint32_t>(m + 2, 0, &mbr), &mbr);

    table[1][1] = 1;

    for (auto i = 0u; i <= n; ++i) {
        for (auto j = 0u; j <= m; ++j) {
            table[i][j + 1] += table[i][j];
            table[i + 1][j] += table[i][j];
        }
    }

    auto res = table[n][m];
    mbr.release();
    return res;
}

} // namespace dp
