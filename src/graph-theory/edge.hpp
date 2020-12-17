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
    constexpr explicit Edge(const _N& node, const double w)
        : _node{std::cref(node)}
        , _weight{w}
    {
    }

    constexpr const _N& node() const noexcept
    {
        return _node.get();
    }

    constexpr double weight() const noexcept
    {
        return _weight;
    }

private:
    std::reference_wrapper<const _N> _node;
    double _weight;
};

} // namespace cppgraph
