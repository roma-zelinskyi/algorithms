/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <vector>

namespace dp {

bool canSum(int num, const std::vector<int>& arr);
bool canSumTab(std::uint32_t num, const std::vector<std::uint32_t>& arr);

} // namespace dp

