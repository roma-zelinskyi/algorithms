/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dp::memo {

std::uint32_t countConstruct(const std::string& target, const std::vector<std::string>& wordBank);

} // namespace dp::memo



