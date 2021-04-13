/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "best_sum.hpp"

#include <array>
#include <memory_resource>
#include <vector>

namespace dp {

std::optional<std::vector<std::uint32_t>>
bestSumTab(const std::uint32_t num, const std::vector<std::uint32_t>& arr)
{
    auto buffer = std::array<std::byte, 409600>{};
    auto mbr = std::pmr::monotonic_buffer_resource{buffer.data(), buffer.size()};
    auto table =
        std::pmr::vector<std::optional<std::vector<std::uint32_t>>>(num + 1, std::nullopt, &mbr);

    table[0] = std::make_optional<std::vector<std::uint32_t>>();

    for (auto i = 0u; i <= num; ++i) {
        if (table.at(i)) {
            const auto curSize = table.at(i).value().size();
            for (const auto& it : arr) {
                const auto nextIndex = i + it;
                if (nextIndex <= num) {
                    if (table.at(nextIndex)) {
                        const auto nextSize = table.at(nextIndex).value().size();
                        if ((curSize + 1) < nextSize) {
                            table[nextIndex] = table.at(i);
                            table.at(nextIndex).value().push_back(it);
                        }
                    } else {
                        table[nextIndex] = table.at(i);
                        table.at(nextIndex).value().push_back(it);
                    }
                }
            }
        }
    }

    return table.at(num);
}

} // namespace dp


