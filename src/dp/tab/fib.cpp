/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "fib.hpp"

#include <vector>

namespace dp::tab {

std::uint32_t fib(const std::uint32_t num)
{
    auto table = std::vector<std::uint32_t>(num + 2, 0);
    table[1] = 1;

    for (auto i = 0u; i <= num; ++i) {
        table[i + 1] += table[i];
        table[i + 2] += table[i];
    }

    return table[num];
}

} // namespace dp::tab

