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
#include "edge.hpp"

namespace cppgraph {

template<class _N>
class Graph
{
    using ProcessNodeDfs = std::function<void(const _N& node)>;

    template<class _T>
    friend std::ostream& operator<<(std::ostream& out, const Graph<_T>& graph);

public:
    Graph()
        : _adjList{}
    {
    }

    const std::unordered_map<_N, std::forward_list<Edge<_N>>>& adjList() const noexcept
    {
        return _adjList;
    }

    Bfs<_N> bfs(const std::optional<_N>& start = std::nullopt)
    {
        if (start)
            return Bfs{*this, start.value()};

        return Bfs{*this, _adjList.begin()->first};
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

    void dfs(const _N& statrt, const ProcessNodeDfs& callback)
    {
        auto visited = std::unordered_set<_N>{};
        dfs(statrt, visited, callback);
    }

private:
    void dfs(const _N& node, std::unordered_set<_N>& visited, const ProcessNodeDfs& callback)
    {
        if (visited.count(node))
            return;

        visited.insert(node);

        for (const auto& adj : _adjList.at(node))
            dfs(adj.node(), visited, callback);

        callback(node);
    }

private:
    std::unordered_map<_N, std::forward_list<Edge<_N>>> _adjList;
};

} // namespace cppgraph
