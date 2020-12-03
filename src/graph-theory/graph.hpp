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

#include "edge.hpp"

namespace cppgraph {

template<class _N>
class Graph
{
    using ProcessNodeDfs = std::function<void(const _N& node)>;
    using ProcessNodeBfs = std::function<void(const std::optional<_N>& parent, const _N& child)>;

    template<class _T>
    friend std::ostream& operator<<(std::ostream& out, const Graph<_T>& graph);

public:
    Graph()
        : _adjList{}
    {
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

    void bfs(const _N& start, const ProcessNodeBfs& callback)
    {
        auto visited = std::unordered_set<_N>{};
        auto que = std::deque<std::reference_wrapper<const _N>>{};

        visited.insert(start);
        que.emplace_back(start);
        callback(std::nullopt, start);

        while (!que.empty()) {
            const auto& node = que.front().get();
            que.pop_front();
            for (const auto& adj : _adjList.at(node)) {
                if (visited.count(adj.node()))
                    continue;

                visited.insert(adj.node());
                que.emplace_back(adj.node());
                callback(node, adj.node());
            }
        }
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
