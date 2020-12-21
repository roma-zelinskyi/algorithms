/**
 *  Project  Graph
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

namespace cppgraph {

template<class _N>
class Graph
{
public:
    using BfsIterator = typename Bfs<_N>::Iterator;

    template<TraversalOrder Order>
    using DfsIterator = typename Dfs<_N, Order>::Iterator;

    Graph()
        : _adjList{}
    {
    }

    const std::unordered_map<_N, std::forward_list<Edge<_N>>>& adjList() const noexcept
    {
        return _adjList;
    }

    Bfs<_N> bfs(const std::optional<_N>& start = std::nullopt) const
    {
        if (start)
            return Bfs{*this, start.value()};

        return Bfs{*this, _adjList.begin()->first};
    }

    typename Bfs<_N>::Iterator bfsBegin(const std::optional<_N>& start = std::nullopt) const
    {
        return bfs(start).begin();
    }

    typename Bfs<_N>::Iterator bfsEnd() const
    {
        return bfs().end();
    }

    template<TraversalOrder _Order = TraversalOrder::Pre>
    Dfs<_N, _Order> dfs(const std::optional<_N>& start = std::nullopt) const
    {
        if (start)
            return Dfs<_N, _Order>{*this, start.value()};

        return Dfs<_N, _Order>{*this, _adjList.begin()->first};
    }

    template<TraversalOrder _Order = TraversalOrder::Pre>
    typename Dfs<_N, _Order>::Iterator dfsBegin(const std::optional<_N>& start = std::nullopt) const
    {
        return dfs<_Order>(start).begin();
    }

    template<TraversalOrder _Order = TraversalOrder::Pre>
    typename Dfs<_N, _Order>::Iterator dfsEnd() const
    {
        return dfs<_Order>().end();
    }

    void addNode(const _N& node)
    {
        if (_adjList.count(node))
            return;

        _adjList[node] = {};
    }

    void addEdge(const _N& src, const _N& dest, double weight = 0)
    {
        if (!_adjList.count(src) || !_adjList.count(dest))
            throw std::invalid_argument{"No such node exist in graph"};

        const auto& destNode = _adjList.find(dest)->first;
        auto& srcNode = _adjList.at(src);

        const auto res = std::find_if(srcNode.begin(), srcNode.end(), [&dest](const auto& edge) {
            return edge.node() == dest;
        });

        if (res == std::end(srcNode))
            srcNode.emplace_front(destNode, weight);
    }

private:
    std::unordered_map<_N, std::forward_list<Edge<_N>>> _adjList;
};

} // namespace cppgraph
