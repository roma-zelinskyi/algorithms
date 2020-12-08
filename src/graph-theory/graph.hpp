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
#include <unordered_set>

#include "bfs.hpp"
#include "dfs.hpp"
#include "edge.hpp"

namespace cppgraph {

template<class _N>
class Graph
{
    template<class _T>
    friend std::ostream& operator<<(std::ostream& out, const Graph<_T>& graph);

    friend class Bfs<_N>::iterator;
    friend class Dfs<_N>::iterator;

public:
    using BfsIterator = typename Bfs<_N>::iterator;
    using DfsIterator = typename Dfs<_N>::iterator;

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

    typename Bfs<_N>::iterator bfsBegin(const std::optional<_N>& start = std::nullopt) noexcept
    {
        return bfs(start).begin();
    }

    typename Bfs<_N>::iterator bfsEnd() noexcept
    {
        return bfs().end();
    }

    Dfs<_N> dfs(const std::optional<_N>& start = std::nullopt)
    {
        if (start)
            return Dfs{*this, start.value()};

        return Dfs{*this, _adjList.begin()->first};
    }

    typename Dfs<_N>::iterator dfsBegin(const std::optional<_N>& start = std::nullopt) noexcept
    {
        return dfs(start).begin();
    }

    typename Dfs<_N>::iterator dfsEnd() noexcept
    {
        return dfs().end();
    }

    void addNode(const _N& node)
    {
        if (_adjList.count(node))
            throw std::invalid_argument{"The node already exist"};

        _adjList[node] = {};
    }

    void addEdge(const _N& src, const _N& dest, double weight = 0)
    {
        if (!_adjList.count(src) || !_adjList.count(dest))
            throw std::invalid_argument{"No such node exist in graph"};

        const auto& destNode = _adjList.find(dest)->first;
        auto& srcNode = _adjList.at(src);
        srcNode.emplace_front(destNode, weight);
    }

private:
    std::unordered_map<_N, std::forward_list<Edge<_N>>> _adjList;
};

} // namespace cppgraph
