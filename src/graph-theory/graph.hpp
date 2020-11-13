/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <deque>
#include <functional>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "edge.hpp"
#include "node.hpp"

namespace cppgraph {

template<class _N>
class Graph
{
    using ProcessNodeDfs = std::function<void(const _N& node)>;
    using ProcessNodeBfs = std::function<void(const _N& parent, const _N& child)>;

    friend std::ostream& operator<<(std::ostream& out, const Graph& graph);

public:
    Graph()
        : _nodeLookup{}
    {
    }

    void addNode(const _N& node)
    {
        auto id = static_cast<std::uint32_t>(std::hash<_N>{}(node));
        if (_nodeLookup.count(id))
            throw std::invalid_argument{"The node already exist"};

        _nodeLookup.emplace(id, node);
    }

    void addEdge(const _N& src, const _N& dest, double weight = 0)
    {
        auto srcId = static_cast<std::uint32_t>(std::hash<_N>{}(src));
        auto destId = static_cast<std::uint32_t>(std::hash<_N>{}(dest));

        if (!_nodeLookup.count(srcId) || !_nodeLookup.count(destId))
            throw std::invalid_argument{"No such node exist in graph"};

        auto& srcNode = _nodeLookup.at(srcId);
        srcNode.addEdge({destId, weight});
    }

    void dfs(const _N& statrt, const ProcessNodeDfs& callback)
    {
        auto visited = std::unordered_set<std::uint32_t>{};
        auto id = static_cast<std::uint32_t>(std::hash<_N>{}(statrt));
        dfs(id, visited, callback);
    }

    void bfs(const _N& statrt, const ProcessNodeBfs& callback)
    {
        const auto id = static_cast<std::uint32_t>(std::hash<_N>{}(statrt));
        auto visited = std::unordered_set<std::uint32_t>{};
        auto que = std::deque<std::uint32_t>{};

        visited.insert(id);
        que.push_back(id);
        callback(_nodeLookup.at(id).value(), _nodeLookup.at(id).value());

        while (!que.empty()) {
            const auto nodeId = que.front();
            que.pop_front();
            for (const auto& adj : _nodeLookup.at(nodeId).adjacent()) {
                if (visited.count(adj.id()))
                    continue;

                visited.insert(adj.id());
                que.push_back(adj.id());
                callback(_nodeLookup.at(nodeId).value(), _nodeLookup.at(adj.id()).value());
            }
        }
    }

    void print()
    {
        for (const auto& it : _nodeLookup) {
            std::cout << it.second.value() << "-> ";
            for (const auto& adj : it.second.adjacent())
                std::cout << '[' << _nodeLookup.at(adj.id()).value() << ',' << adj.weight() << ']'
                          << ' ';

            std::cout << '\n';
        }
    }

private:
    void
    dfs(std::uint32_t id,
        std::unordered_set<std::uint32_t>& visited,
        const ProcessNodeDfs& callback)
    {
        if (visited.count(id))
            return;

        visited.insert(id);

        for (const auto& adj : _nodeLookup.at(id).adjacent()) {
            const auto& nextNode = _nodeLookup.at(adj.id());
            auto nextNodeId = static_cast<std::uint32_t>(std::hash<_N>{}(nextNode.value()));
            dfs(nextNodeId, visited, callback);
        }

        callback(_nodeLookup.at(id).value());
    }

private:
    std::unordered_map<std::uint32_t, Node<_N>> _nodeLookup;
};

} // namespace cppgraph
