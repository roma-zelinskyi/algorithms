/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <functional>

namespace cppgraph {

template<class _NodeDescriptor>
class Edge
{
public:
    constexpr explicit Edge(const _NodeDescriptor& src, const _NodeDescriptor& dest, const double w)
        : _src{src}
        , _dest{dest}
        , _weight{w}
    {
    }

    constexpr const _NodeDescriptor& from() const noexcept
    {
        return _src;
    }

    constexpr const _NodeDescriptor& to() const noexcept
    {
        return _dest;
    }

    constexpr double weight() const noexcept
    {
        return _weight;
    }

    bool operator==(const Edge<_NodeDescriptor>& rhs) const
    {
        return _src == rhs._src && _dest == rhs._dest;
    }

private:
    _NodeDescriptor _src;
    _NodeDescriptor _dest;
    double _weight;
};

} // namespace cppgraph
