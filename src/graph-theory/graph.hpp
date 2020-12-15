/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <deque>
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
    template<class _T>
    friend std::ostream& operator<<(std::ostream& out, const Graph<_T>& graph);

    friend class Bfs<_N>::Iterator;
    friend class Dfs<_N>::Iterator;

public:
    using BfsIterator = typename Bfs<_N>::Iterator;
    using DfsIterator = typename Dfs<_N>::Iterator;

    Graph()
        : _adjList{}
    {
    }

    Bfs<_N> bfs(const std::optional<_N>& start = std::nullopt)
    {
        if (start)
            return Bfs{*this, start.value()};

        return Bfs{*this, _adjList.begin()->first};
    }

    typename Bfs<_N>::Iterator bfsBegin(const std::optional<_N>& start = std::nullopt) noexcept
    {
        return bfs(start).begin();
    }

    typename Bfs<_N>::Iterator bfsEnd() noexcept
    {
        return bfs().end();
    }

    Dfs<_N> dfs(const std::optional<_N>& start = std::nullopt)
    {
        if (start)
            return Dfs{*this, start.value()};

        return Dfs{*this, _adjList.begin()->first};
    }

    typename Dfs<_N>::Iterator dfsBegin(const std::optional<_N>& start = std::nullopt) noexcept
    {
        return dfs(start).begin();
    }

    typename Dfs<_N>::Iterator dfsEnd() noexcept
    {
        return dfs().end();
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
