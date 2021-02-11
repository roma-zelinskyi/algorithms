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
        : _src{src}
        , _dest{dest}
        , _weight{w}
    {
    }

    constexpr const _N& from() const noexcept
    {
        return _src;
    }

    constexpr const _N& to() const noexcept
    {
        return _dest;
    }

    constexpr double weight() const noexcept
    {
        return _weight;
    }

    bool operator==(const Edge<_N>& rhs) const
    {
        return _src == rhs._src && _dest == rhs._dest;
    }

private:
    _N _src;
    _N _dest;
    double _weight;
};

} // namespace cppgraph
