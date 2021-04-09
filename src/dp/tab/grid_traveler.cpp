/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "grid_traveler.hpp"

#include <array>
#include <memory_resource>
#include <vector>

namespace dp::tab {

std::uint32_t gridTraveler(const std::uint32_t n, const std::uint32_t m)
{
    auto buf = std::array<std::uint32_t, 4096>{};
    auto mbr = std::pmr::monotonic_buffer_resource{buf.data(), 4096};
    auto table = std::pmr::vector<std::pmr::vector<std::uint32_t>>(
        n + 2, std::pmr::vector<std::uint32_t>(m + 2, 0, &mbr), &mbr);

    table[1][1] = 1;

    for (auto i = 0u; i <= n; ++i) {
        for (auto j = 0u; j <= m; ++j) {
            table[i][j + 1] += table[i][j];
            table[i + 1][j] += table[i][j];
        }
    }

    return table[n][m];
}

} // namespace dp::tab

