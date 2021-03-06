/**
 *  Project Dynamic Programming
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <string>
#include <vector>

namespace dp {

bool canConstruct(const std::string& target, const std::vector<std::string>& wordBank);
bool canConstructTab(const std::string& target, const std::vector<std::string>& wordBank);

} // namespace dp

