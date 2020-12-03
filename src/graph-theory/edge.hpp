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
    Edge(const _N& node, double w)
        : _node{std::cref(node)}
        , _weight{w}
    {
    }

    const _N& node() const noexcept
    {
        return _node.get();
    }

    double weight() const noexcept
    {
        return _weight;
    }

private:
    std::reference_wrapper<const _N> _node;
    double _weight;
};

} // namespace cppgraph
