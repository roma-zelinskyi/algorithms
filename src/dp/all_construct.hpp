/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <forward_list>
#include <string>
#include <vector>

namespace zee {

std::forward_list<std::forward_list<std::string>>
allConstruct(const std::string& target, const std::vector<std::string>& wordBank);

} // namespace zee



