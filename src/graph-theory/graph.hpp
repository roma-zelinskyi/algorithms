/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <stdexcept>
#include <unordered_map>

#include "edge.hpp"
#include "node.hpp"

namespace cppgraph {

template<class _N>
class Graph
{
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
    std::unordered_map<std::uint32_t, Node<_N>> _nodeLookup;
};

} // namespace cppgraph
