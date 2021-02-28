/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "dfs.hpp"
#include "adjacency_list.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class DfsTopOrderIterator : private Dfs<_NodeDescriptor, TraversalOrder::Post>::Iterator
{
public:
    DfsTopOrderIterator(const AdjacencyList<_NodeDescriptor>& graph)
        : Dfs<_NodeDescriptor, TraversalOrder::Post>::Iterator{graph}
    {
    }

    std::vector<_NodeDescriptor> sort()
    {
        auto topOrder = std::vector<_NodeDescriptor>(this->_graph.data().size(), _NodeDescriptor{});
        auto index = this->_graph.data().size() - 1;
        auto itEnd = DfsTopOrderIterator{this->_graph};

        for (const auto& node : this->_graph.data()) {
            this->dfsRec(node.first);

            for (; this->operator!=(itEnd); this->operator++()) {
                topOrder[index] = this->operator*();
                --index;
            }
        }

        return topOrder;
    }
};

template<class _NodeDescriptor>
std::vector<_NodeDescriptor> topSort(const AdjacencyList<_NodeDescriptor>& graph)
{
    return DfsTopOrderIterator<_NodeDescriptor>{graph}.sort();
}

} // namespace cppgraph

