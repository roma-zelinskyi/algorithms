/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <forward_list>
#include <stdexcept>
#include <unordered_map>

#include "edge.h"

namespace cppgraph {

template<class Node>
class Graph
{
public:
    Graph()
        : _adjList{}
    {
    }

    void addNode(const Node& node)
    {
        if (_adjList.count(node))
            throw std::invalid_argument{"The node already exist"};

        _adjList[node] = {};
    }

    void addEdge(const Node& src, const Node& dest, double weight = 0)
    {
        if (!_adjList.count(src) || !_adjList.count(dest))
            throw std::invalid_argument{"No such node exist in graph"};

        auto& srcNode = _adjList.at(src);
        const auto& destNode = _adjList.find(dest)->first;
        srcNode.push_front({destNode, weight});
    }

    void print()
    {
        for (const auto& it : _adjList) {
            std::cout << it.first << "-> ";
            for (const auto& adjecent : it.second)
                std::cout << '[' << adjecent.destNode() << ',' << adjecent.weight() << ']' << ' ';

            std::cout << '\n';
        }
    }

private:
    std::unordered_map<Node, std::forward_list<Edge<Node>>> _adjList;
};

} // namespace cppgraph
