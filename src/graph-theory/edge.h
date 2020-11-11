/**
 *  Project  Graph
 *
 *  This file contains an implementation of the graph edge.
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <functional>

namespace cppgraph {

template<class Node>
class Edge
{
public:
    Edge(const Node& node, double w)
        : _destNode{std::cref(node)}
        , _weight{w}
    {
    }

    const Node& destNode() const noexcept
    {
        return _destNode.get();
    }

    double weight() const noexcept
    {
        return _weight;
    }

private:
    std::reference_wrapper<const Node> _destNode;
    double _weight;
};

} // namespace cppgraph
