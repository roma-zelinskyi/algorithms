/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <functional>

namespace cppgraph {

template<class _N>
class Edge
{
public:
    constexpr explicit Edge(const _N& src, const _N& dest, const double w)
        : _src{std::cref(src)}
        , _dest{std::cref(dest)}
        , _weight{w}
    {
    }

    constexpr const _N& from() const noexcept
    {
        return _src.get();
    }

    constexpr const _N& to() const noexcept
    {
        return _dest.get();
    }

    constexpr double weight() const noexcept
    {
        return _weight;
    }

    bool operator==(const Edge<_N>& rhs) const
    {
        return _src.get() == rhs._src.get() && _dest.get() == rhs._dest.get();
    }

private:
    std::reference_wrapper<const _N> _src;
    std::reference_wrapper<const _N> _dest;
    double _weight;
};

} // namespace cppgraph
