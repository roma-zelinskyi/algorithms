/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <forward_list>
#include <functional>
#include <optional>
#include <stdexcept>
#include <unordered_map>

#include "bfs.hpp"
#include "dfs.hpp"
#include "edge.hpp"
#include "edge_iterator.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class AdjacencyList
{
public:
    using BfsIterator = typename Bfs<_NodeDescriptor>::Iterator;

    template<TraversalOrder Order>
    using DfsIterator = typename Dfs<_NodeDescriptor, Order>::Iterator;

    const std::unordered_map<_NodeDescriptor, std::forward_list<Edge<_NodeDescriptor>>>& data() const noexcept
    {
        return _data;
    }

    const std::forward_list<Edge<_NodeDescriptor>>& adjacent(const _NodeDescriptor& node) const noexcept
    {
        return _data.at(node);
    }

    Bfs<_NodeDescriptor> bfs(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        if (start)
            return Bfs{*this, _data.find(start.value())->first};

        return Bfs{*this, _data.begin()->first};
    }

    typename Bfs<_NodeDescriptor>::Iterator bfsBegin(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        return bfs(start).begin();
    }

    typename Bfs<_NodeDescriptor>::Iterator bfsEnd() const
    {
        return bfs().end();
    }

    template<TraversalOrder _Order = TraversalOrder::Pre>
    Dfs<_NodeDescriptor, _Order> dfs(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        if (start)
            return Dfs<_NodeDescriptor, _Order>{*this, _data.find(start.value())->first};

        return Dfs<_NodeDescriptor, _Order>{*this, _data.begin()->first};
    }

    template<TraversalOrder _Order = TraversalOrder::Pre>
    typename Dfs<_NodeDescriptor, _Order>::Iterator dfsBegin(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        return dfs<_Order>(start).begin();
    }

    template<TraversalOrder _Order = TraversalOrder::Pre>
    typename Dfs<_NodeDescriptor, _Order>::Iterator dfsEnd() const
    {
        return dfs<_Order>().end();
    }

    EdgeIterator<_NodeDescriptor> edges() const
    {
        return EdgeIterator<_NodeDescriptor>(*this);
    }

    typename EdgeIterator<_NodeDescriptor>::Iterator edgeBegin() const
    {
        return edges().begin();
    }

    typename EdgeIterator<_NodeDescriptor>::Iterator edgeEnd() const
    {
        return edges().end();
    }

    std::size_t vSize() const noexcept
    {
        return _data.size();
    }

    void addNode(const _NodeDescriptor& node)
    {
        if (_data.count(node))
            return;

        _data[node] = {};
    }

    void addEdge(const Edge<_NodeDescriptor>& edge)
    {
        addEdge(edge.from(), edge.to(), edge.weight());
    }

    void addEdge(const _NodeDescriptor& src, const _NodeDescriptor& dest, double weight = 0)
    {
        if (!_data.count(src) || !_data.count(dest))
            throw std::invalid_argument{"No such node exist in graph"};

        const auto& from = _data.find(src)->first;
        const auto& to = _data.find(dest)->first;
        auto& srcAdjacent = _data.at(src);

        const auto res =
            std::find_if(srcAdjacent.begin(), srcAdjacent.end(), [&dest](const auto& edge) {
                return edge.to() == dest;
            });

        if (res == std::end(srcAdjacent))
            srcAdjacent.emplace_front(from, to, weight);
    }

private:
    std::unordered_map<_NodeDescriptor, std::forward_list<Edge<_NodeDescriptor>>> _data;
};

} // namespace cppgraph
