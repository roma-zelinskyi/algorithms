/**
 *  Project  Algorithms
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <functional>

namespace cppgraph {

inline void hashCombine([[maybe_unused]] std::size_t& seed)
{
}

template<typename _T, typename... _Args>
inline void hashCombine(std::size_t& seed, const _T& v, _Args... args)
{
    std::hash<_T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hashCombine(seed, args...);
}

} // namespace cppgraph
