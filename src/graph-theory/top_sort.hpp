/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "dfs.hpp"
#include "graph.hpp"

namespace cppgraph {

template<class _N>
class DfsTopOrderIterator : private Dfs<_N, TraversalOrder::Post>::Iterator
{
public:
    DfsTopOrderIterator(const Graph<_N>& graph)
        : Dfs<_N, TraversalOrder::Post>::Iterator{graph}
    {
    }

    std::vector<_N> sort()
    {
        auto topOrder = std::vector<_N>(this->_graph.adjList().size(), _N{});
        auto index = this->_graph.adjList().size() - 1;
        auto itEnd = DfsTopOrderIterator{this->_graph};

        for (const auto& node : this->_graph.adjList()) {
            this->dfsRec(node.first);

            for (; this->operator!=(itEnd); this->operator++()) {
                topOrder[index] = this->operator*();
                --index;
            }
        }

        return topOrder;
    }
};

template<class _N>
std::vector<_N> topSort(const Graph<_N>& graph)
{
    return DfsTopOrderIterator<_N>{graph}.sort();
}

} // namespace cppgraph

