/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <functional>

#include "destination_edge.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class Edge : public DestinationEdge<_NodeDescriptor>
{
public:
    constexpr explicit Edge(
        const _NodeDescriptor& from, const _NodeDescriptor& to, const double w = 0)
        : DestinationEdge<_NodeDescriptor>{to, w}
        , _from{from}
    {
    }

    constexpr const _NodeDescriptor& from() const noexcept
    {
        return _from;
    }

    bool operator==(const Edge<_NodeDescriptor>& rhs) const
    {
        return _from == rhs._from && this->_to == rhs._to;
    }

private:
    _NodeDescriptor _from;
};

} // namespace cppgraph
