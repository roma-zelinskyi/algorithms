/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <functional>

namespace cppgraph {

template<class _NodeDescriptor>
class DestinationEdge
{
public:
    constexpr explicit DestinationEdge(const _NodeDescriptor& to, const double w)
        : _to{to}
        , _weight{w}
    {
    }

    constexpr const _NodeDescriptor& to() const noexcept
    {
        return _to;
    }

    constexpr double weight() const noexcept
    {
        return _weight;
    }

protected:
    _NodeDescriptor _to;
    double _weight;
};

} // namespace cppgraph

