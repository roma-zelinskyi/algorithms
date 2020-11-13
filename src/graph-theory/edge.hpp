/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <functional>

#include "utils/hash_combine.hpp"

namespace cppgraph {

class Edge
{
public:
    Edge()
        : _nodeId{}
        , _weight{}
    {
    }

    Edge(std::uint32_t nodeId, double w)
        : _nodeId{nodeId}
        , _weight{w}
    {
    }

    std::uint32_t id() const noexcept
    {
        return _nodeId;
    }

    double weight() const noexcept
    {
        return _weight;
    }

    bool operator==(const Edge& rhs) const
    {
        return _nodeId == rhs._nodeId;
    }

private : std::uint32_t _nodeId;
    double _weight;
};

} // namespace cppgraph

namespace std {
template<>
struct hash<cppgraph::Edge>
{
    std::size_t operator()(cppgraph::Edge const& edge) const noexcept
    {
        auto h = std::size_t{0};
        cppgraph::hashCombine(h, edge.id(), edge.weight());
        return h;
    }
};
} // namespace std
