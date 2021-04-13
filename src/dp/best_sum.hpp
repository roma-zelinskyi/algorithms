/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace dp {

std::optional<std::vector<std::uint32_t>>
bestSumTab(std::uint32_t num, const std::vector<std::uint32_t>& arr);

} // namespace dp


